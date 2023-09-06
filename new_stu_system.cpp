#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_ACCOUNT_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_NAME_LEN 50
#define MAX_WORKID_LEN 20
const int MAX=110;
int course_num=0;   //课程数量
char id[MAX_ACCOUNT_LEN];//用户账号
char key[MAX_PASSWORD_LEN];//登录密码

//同一个班级里的学生
typedef struct class_stu{
	int teacher_id;
	int student_id;
	char student_name[20];
	int student_score;
	class_stu* next;
	
}class_stu;
typedef struct Student{
	int student_id;
	char student_name[20];
	char student_tel[20];
	struct Stu_self_course* stu_course;//学生所选的课程
	Student* next;
}Student;

typedef struct Stu_self_course{  //学生选择的课程信息
	char student_name[20];
	char course_name[20];
	int course_id;     //课程号
	char course_teacher[20];//任课老师
	int teacher_id;    //任课老师工号
	int score;              //学生课程成绩
	int status;            //课程状态--是否被删除,默认为false
	struct Stu_self_course* next;    //指向下一个课程
}Stu_self_course;
typedef struct {
	char name[MAX_NAME_LEN];
	char account[MAX_ACCOUNT_LEN];
	char password[MAX_PASSWORD_LEN];
	char work_id[MAX_WORKID_LEN];
	char role[MAX_NAME_LEN];
} Account;
typedef struct Teacher{
	char teacher_name[20];
	int teacher_id;
	char course_name[20];
	int course_id;          //课程号
	int course_credit;      //学分
	int course_capacity;    //总人数容量
	int course_selected;    //当前选课人数
	int course_remain;      //剩余容量
	char course_time[20];   //上课时间
	char course_place[20];  //上课地点
	int status;            //课程状态--是否被删除,默认为false
	class_stu* class_stu_list;   //指向班级学生的指针
	Teacher* left;
	Teacher* right;
}Teacher;
Teacher* root=NULL;
Student* studentList=NULL;      //学生系统的学生链表 
Student* student_now=NULL;      //正在使用系统的学生
Teacher* teacher_now=NULL;      //正在使用系统的老师
void log_in_fun();
void log_in();
void login_menu();
void deleteCourse(Student* student,int course_id);
//
Teacher* createNewTeacher(char teacher_name[20],int teacher_id,char course_name[20],int course_id,int course_credit,int course_capacity,char course_time[20],char course_place[20],int course_status){
	Teacher* new_teacher=(Teacher*)malloc(sizeof(Teacher));
	strcpy(new_teacher->teacher_name,teacher_name);
	new_teacher->teacher_id=teacher_id;
	strcpy(new_teacher->course_name,course_name);
	new_teacher->course_id=course_id;
	new_teacher->course_credit=course_credit;
	new_teacher->course_capacity=course_capacity;
	new_teacher->course_selected=0;
	new_teacher->course_remain=course_capacity;
	strcpy(new_teacher->course_place,course_place);
	strcpy(new_teacher->course_time,course_time);
	new_teacher->status=course_status;
	new_teacher->left=NULL;
	new_teacher->right=NULL;
	new_teacher->class_stu_list=NULL;
	return new_teacher;
}
// 插入老师结点
Teacher* insert_teacher_node(Teacher* root,Teacher* new_teacher){
	if(root==NULL){
		root=new_teacher;
		return root;
	}
	if(new_teacher->teacher_id<root->teacher_id){
		root->left=insert_teacher_node(root->left,new_teacher);
	}
	else if(new_teacher->teacher_id>root->teacher_id){
		root->right=insert_teacher_node(root->right,new_teacher);
	}
	return root;
}
// 查找老师结点，若找到则返回该结点，否则返回NULL
Teacher* search_teacher_node(Teacher* root,int teacher_id){
	if(root==NULL||root->teacher_id==teacher_id){
		return root;
	}
	
	else if(root->teacher_id>teacher_id){
		return search_teacher_node(root->left,teacher_id);
	}
	else{
		return search_teacher_node(root->right,teacher_id);
	}
}
//中序遍历以老师工号为关键字的二叉树
Teacher* inorder_Teacher_Node(Teacher* root){
	if(root!=NULL){
		inorder_Teacher_Node(root->left);
		if(root->status==1){
			printf("\t\t课程:%s\t课程号:%d\t任课老师:%s\t工号:%d\n",root->course_name,root->course_id,root->teacher_name,root->teacher_id);
		}
		inorder_Teacher_Node(root->right);
	}
	return root;
}
bool delete_node(Teacher *&p){
	Teacher *q,*s;
	if(p->left==NULL&&p->right==NULL){ //左右子树都为空
		p=NULL;
	}else if(p->left==NULL){ //左子树为空
		q=p;
		p=p->right;
		free(q);
	}else if(p->right==NULL){
		q=p;
		s=p->left;
		free(q);
	}else{
		q=p;
		s=p->right;
		while(s->left!=NULL){
			q=s;
			s=s->left;
		}
		p->teacher_id=s->teacher_id;
		strcpy(p->teacher_name,s->teacher_name);
		p->class_stu_list=s->class_stu_list;
		p->course_capacity=s->course_capacity;
		p->course_credit=s->course_credit;
		p->course_id=s->course_id;
		p->status=s->status;
		strcpy(p->course_name,s->course_name);
		strcpy(p->course_place,s->course_place);
		strcpy(p->course_time,s->course_time);
		p->course_remain=s->course_remain;
		p->course_selected=s->course_selected;
		if(q!=p){
			q->left=s->right;
		}else{
			q->right=s->right;
		}
		free(s);

	}
		 
	return true;
}
bool delete_Teacher_Node(Teacher* root,int teacher_id){
	if(root==NULL){
		return false;
	}else{
		if(root->teacher_id==teacher_id){
			return delete_node(root);
		}else if(root->teacher_id>teacher_id){
			return delete_Teacher_Node(root->left,teacher_id);
		}else{
			return delete_Teacher_Node(root->right,teacher_id);
		}
	}
}
Teacher* show_info_course(Teacher* root){
	if(root!=NULL){
		show_info_course(root->left);
		if(root->status==1){
			printf("\t课程:%s\t课程号:%d\t学分:%d\t剩余容量:%d\t任课老师:%s\t工号:%d\t时间:%s\t地点:%s\n",root->course_name,root->course_id,root->course_credit,root->course_remain,root->teacher_name,root->teacher_id,root->course_time,root->course_place);
		}
		show_info_course(root->right);
	}
	return root;
}
void showMenu_teacher()
{
	printf("\t\t    \t 课程管理信息系统-老师  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].查询所开课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].查询课程学生信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].输入学生课程成绩  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].修改学生课程成绩  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].统计成绩人数分布  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].退出  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t 输入序号以选择对应功能 : "); 
}
void showMenu_Adimn()
{
	printf("\t\t    \t 课程管理信息系统-管理员  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].创建课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].添加课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].删除课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].统计课程总数  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].查询每门课修课的人数  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].浏览计算机专业的课程信息  ** \n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [7].退出  *\t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t 输入序号以选择对应功能 : "); 
	
}
void showMenu_student()
{
	printf("\t\t    \t 课程管理信息系统-学生  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].查询课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].报名课程学习  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].取消课程学习  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].查询课程成绩  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].浏览所有课程的信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].退出  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t 输入序号以选择对应功能 : "); 
}
Student* search_student_node(Student* studentList,int student_id){
	if(studentList==NULL||studentList->student_id==student_id){
		return studentList;
	}
	Student* temp=studentList;
	while(temp!=NULL){
		if(temp->student_id==student_id){
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}
void admin_create_course(){
	printf("\t\t请输入要创建的课程总数:");
	int course_num_now;
	scanf("%d",&course_num_now);
	while(course_num_now--){
		printf("\t\t请输入课程信息\n");
		printf("\n\t\t课程名: ");    char course_name[20];      scanf("%s",course_name);   
		printf("\t\t课程号: ");    int course_id;             scanf("%d",&course_id);       
		printf("\t\t学分: ");      int course_credit;         scanf("%d",&course_credit);    
		printf("\n\t\t总容量: ");    int course_capacity;       scanf("%d",&course_capacity); 
		printf("\t\t任课老师: ");  char course_teacher[20];   scanf("%s",course_teacher);  
		printf("\t\t老师工号: ");  int teacher_id;            scanf("%d",&teacher_id);       
		printf("\n\t\t上课时间:");   char course_time[20];      scanf("%s",course_time);   
		printf("\t\t上课地点:");   char course_place[20];     scanf("%s",course_place);  
		Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id,course_name,course_id,course_credit,course_capacity,course_time,course_place,1); 
		course_num++;
		root=insert_teacher_node(root,new_teacher);
		FILE* file =  fopen("D:\\data_struct_design\\course_info.txt","a");
		if(file==NULL){
			printf("无法打开文件!");
			return;
		}
		fprintf(file, "%s %d %d %d %s %d %s %s\n",course_name,course_id,course_credit,course_capacity,course_teacher,teacher_id,course_time,course_place);
		printf("\n\t\t课程%s-%d信息录入成功!\n",course_name,course_id );
		printf("\t\t");system("pause");
		if(course_num_now!=0){
			system("cls");
			printf("\n\t\t还需创建%d门课程\n\n",course_num_now );
		}else{
			printf("\n\t\t课程创建成功!\n\n");
			printf("\t\t");system("pause");system("cls");return;
		}
	}
}
void admin_add_course(){
	printf("\t\t请输入要添加的课程信息\n");
	printf("\n\t\t课程名: ");    char course_name[20];      scanf("%s",course_name);   
	printf("\t\t课程号: ");    int course_id;             scanf("%d",&course_id);       
	printf("\t\t学分: ");      int course_credit;         scanf("%d",&course_credit);    
	printf("\n\t\t总容量: ");    int course_capacity;       scanf("%d",&course_capacity); 
	printf("\t\t任课老师: ");  char course_teacher[20];   scanf("%s",course_teacher);  
	printf("\t\t老师工号: ");  int teacher_id;            scanf("%d",&teacher_id);       
	printf("\n\t\t上课时间:");   char course_time[30];      scanf("%s",course_time);     
	printf("\t\t上课地点:");   char course_place[20];     scanf("%s",course_place);
	Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id,course_name,course_id,course_credit,course_capacity,course_time,course_place,1); 
	root=insert_teacher_node(root,new_teacher);
	course_num++;
	FILE* file =  fopen("D:\\data_struct_design\\course_info.txt","a");
	if(file==NULL){
		printf("无法打开文件!");
		return;
	}
	fprintf(file, "%s %d %d %d %s %d %s %s\n",course_name,course_id,course_credit,course_capacity,course_teacher,teacher_id,course_time,course_place);
	printf("\n\t\t课程%s-%d信息录入成功!\n",course_name,course_id );
	printf("\t\t");system("pause");
}
void admin_delete_course(){
	if(course_num==0){
		printf("\t\t当前还未开设任何课程!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t当前开设的课程有:\n");
	inorder_Teacher_Node(root);
	printf("\t\t请输入要删除课程的老师工号:");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* find_teacher=search_teacher_node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\t未找到该老师的课程!\n");
		printf("\t\t");system("pause");
		return;
	}else{
		printf("\t\t该老师开设的课程为:%s\t",find_teacher->course_name);
		printf("\t\t学生人数为:%d\n",find_teacher->course_selected);
		printf("\t\t是否删除该课程?(y/n)");
		char choice;scanf("%s",&choice);
		if(choice=='y'||choice=='Y'){
			find_teacher->status=0;
			course_num--;
			int del_course_id=find_teacher->course_id;
			class_stu* temp=find_teacher->class_stu_list;
			//删除学生列表里的选课信息
			while(temp!=NULL){
				Student* student=search_student_node(studentList,temp->student_id);
				deleteCourse(student,del_course_id);
				temp=temp->next;
			}
			delete_Teacher_Node(root,teacher_id);
			printf("\t\t删除成功!\n");
			printf("\t\t");system("pause");
		}
	}
}
void admin_count_course(){
	if(course_num==0){
		printf("\t\t当前还未开设任何课程!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t当前课程总数为:%d\n",course_num );
	printf("\t\t");system("pause");
}
void admin_count_student(){
	if(course_num==0){
		printf("\t\t当前还未开设任何课程!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("t\t\t\t\t课程列表:\n");
	printf("\t\t——————————————————————————————————————————————————————————————\n");
	inorder_Teacher_Node(root);
	printf("\t\t请输入要查询课程的老师工号: ");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* teacher=search_teacher_node(root,teacher_id);
	if(teacher==NULL){
		printf("\t\t未找到该老师的课程!\n");
		printf("\t\t");system("pause");
		return;
	}else{
		printf("\t\t该老师开设的课程为:%s\t",teacher->course_name);
		printf("学生人数为:%d\n",teacher->course_selected);
		printf("\t\t");system("pause");
	}
}
void admin_output_all_courses(){
	if(course_num==0){
		printf("\t\t当前还未开设任何课程!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t\t\t\t课程列表\n");
	printf("\t\t——————————————————————————————————————————————————————————————\n");
	show_info_course(root);
	printf("\t\t");system("pause");
}
void admin_read_file_course(){
	FILE* file =  fopen("D:\\data_struct_design\\course_info.txt","r");
	if(file==NULL){
		printf("无法打开文件!");
		return;
	}
	char buffer[512];
	fgets(buffer, sizeof(buffer), file); // 忽略标题行
	while(fgets(buffer, sizeof(buffer), file)){
		char course_name[20];
		int course_id;
		int course_credit;
		int course_capacity;
		char course_teacher[20];
		int teacher_id;
		char course_time[20];
		char course_place[20];
		int course_status;
		sscanf(buffer, "%s %d %d %d %s %d %s %s %d", course_name,&course_id,&course_credit,&course_capacity,course_teacher,&teacher_id,course_time,course_place,&course_status);
		Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id,course_name,course_id,course_credit,course_capacity,course_time,course_place,course_status); 
		if(course_status==1){
			root=insert_teacher_node(root,new_teacher);
			course_num++;
		}
		
	}
}
void admin_fun(){

	while(1)
	{
		system("cls");
		showMenu_Adimn();
		int select;
		scanf("%d",&select);
		printf("\t\t");system("pause");
		system("cls");
		switch(select)
		{
		case 1:
			admin_create_course();
			break; 
		case 2:
			admin_add_course(); 
			break;  
		case 3:
			admin_delete_course();
			break;
		case 4:
			admin_count_course();
			break;
		case 5:
			admin_count_student();
			break;
		case 6:
			admin_output_all_courses();
			break;
			
		case 7 :
			printf("\t\t您已退出管理员系统\n");
			printf("\t\t");system("pause");
			system("cls");
			goto then ;//退出系统
		default:
			printf("\t\t输入值无效,请重新输入\n~");
			printf("\t\t");system("pause");
			continue;
		}
		
	}
	then:log_in_fun();
	
}

void deleteStudentFromTeacher(Teacher* teacher,int student_id){
	if(teacher->class_stu_list==NULL){
		return;
	}
	class_stu* pre=NULL;
	class_stu* cur=teacher->class_stu_list;
	while(cur!=NULL){
		if(cur->student_id==student_id){
			if(pre==NULL){
				teacher->class_stu_list=cur->next;
			}else{
				pre->next=cur->next;
			}
			free(cur);
			break;
		}
		pre=cur;
		cur=cur->next;
	}
	
	
	
}
void Print_Class_StudentList(class_stu* StudentList){
	class_stu* temp=StudentList;
	while(temp!=NULL){
		printf("\t\t学生姓名:%s\t学号:%d\n",temp->student_name,temp->student_id);
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
void teacher_course_info(){
	printf("\t\t您当前开设的课程为:\n");
	printf("\t\t课程名称:%s\t课程号:%d",teacher_now->course_name,teacher_now->course_id);
	printf("\t总容量为%d",teacher_now->course_capacity);
	printf("\t当前选课人数:%d",teacher_now->course_selected);
	printf("\t地点:%s\t时间:%s\n",teacher_now->course_place,teacher_now->course_time);
	printf("\t\t");system("pause");
}
void teacher_student_in_class(){
	class_stu* temp=teacher_now->class_stu_list;
	if(temp==NULL){
		printf("\t\t当前课程暂无选课学生!\n");
		printf("\t\t");system("pause");return;
	}
	printf("\t\t您所在班级里的学生为:\n");
	Print_Class_StudentList(teacher_now->class_stu_list);
	//printf("\t\t");system("pause");
}

//老师输入学生课程成绩(bug应该修复过了)
void teacher_input_student_course_score(){
	class_stu* temp=teacher_now->class_stu_list;
	if(temp==NULL){
		printf("\t\t当前课程暂无选课学生!\n");
		printf("\t\t");system("pause");return;
	}
	while(temp!=NULL){
		printf("\t\t请输入学生%s的成绩: ",temp->student_name);
		int score;scanf("%d",&score);
		temp->student_score=score;
		Student* student=search_student_node(studentList,temp->student_id);
		Stu_self_course* temp_course=student->stu_course;	//更改学生课程列表里面的成绩
		while(temp_course!=NULL){
			if(temp_course->course_id==teacher_now->course_id){
				temp_course->score=score;
				break;
			}
			temp_course=temp_course->next;
		}
		temp=temp->next;
	}
	

	
	printf("\t\t成绩录入成功!\n");
	printf("\t\t");system("pause");
	
}
void PrintStudentList(class_stu* StudentList){
	Student* temp=studentList;
	while(temp!=NULL){
		printf("\t\t学生姓名:%s\t学号:%d\n",temp->student_name,temp->student_id);
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
void teacher_change_student_course_score(){
	class_stu* temp2=teacher_now->class_stu_list;
	if(temp2==NULL){
		printf("\t\t当前课程暂无选课学生!\n");
		printf("\t\t");system("pause");return;
	}
	printf("\t\t您所在班级里的学生为:\n");
	PrintStudentList(teacher_now->class_stu_list);

	printf("\t\t请输入要修改成绩的学生学号: ");
	int student_id;scanf("%d",&student_id);
	class_stu* temp=teacher_now->class_stu_list;
	while(temp!=NULL){
		if(temp->student_id==student_id){
			printf("\t\t请输入学生%s的成绩: ",temp->student_name);
			int score;scanf("%d",&score);
			temp->student_score=score;
			Student* student=search_student_node(studentList,temp->student_id);
			Stu_self_course* temp_course=student->stu_course;
			while(temp_course!=NULL){
				if(temp_course->course_id==teacher_now->course_id){
					temp_course->score=score;
					break;
				}
				temp_course=temp_course->next;
			}
			printf("\t\t成绩修改成功!\n");
			printf("\t\t");system("pause");
			return;
		}
		temp=temp->next;
	}
	printf("\t\t未找到该学生!\n");
	printf("\t\t");system("pause");
	return;
}
void teacher_count_student_score(){
	//+,90,80,60,-
	class_stu* temp1=teacher_now->class_stu_list;
	if(temp1==NULL){
		printf("\t\t当前课程暂无选课学生!\n");
		printf("\t\t");system("pause");return;
	}
	int count[5]={0};
	class_stu* temp=teacher_now->class_stu_list;
	while(temp!=NULL){
		if(temp->student_score>=90){
			count[0]++;
		}else if(temp->student_score>=80){
			count[1]++;
		}else if(temp->student_score>=60){
			count[2]++;
		}else{
			count[3]++;
		}
		temp=temp->next;
	}
	printf("\t\t成绩分布如下:\n");
	printf("\t\t90分以上:%d\t80-89分:%d\t60-79分:%d\t60分以下:%d\n",count[0],count[1],count[2],count[3]);
	printf("\t\t");system("pause");
}
void teacher_fun(){
	//system("cls");
	if(course_num==0){
		printf("\n\n\n\t\t当前课程总数为0,系统还未登记，无法进行操作\n\t\t请管理员先创建课程!\n");
		return;
	}else{
		FILE* file =  fopen("D:\\data_struct_design\\accounts.txt","r");
		if(file==NULL){
			printf("无法打开文件!");
			return;
		}
		char buffer[512];
		fgets(buffer, sizeof(buffer), file); // 忽略标题行
		while(fgets(buffer, sizeof(buffer), file)){
			char teacher_name[20];
			int teacher_id;
			char teacher_accunt[20];
			sscanf(buffer, "%s %s %*s %d %*s", teacher_name,teacher_accunt, &teacher_id);
			if(strcmp(teacher_accunt,id )==0){
				teacher_now=search_teacher_node(root,teacher_id);
				if(teacher_now==NULL){
					printf("\t\t管理员还未添加您的课程!请联系管理员\n");
					printf("\t\t");system("pause");
					return;
				}
			}
			
		}
		while(1){
			system("cls");
			showMenu_teacher();
			int select;
			scanf("%d",&select);
			printf("\t\t");system("pause");
			system("cls");
			switch(select)
			{
			case 1:
				teacher_course_info();
				break; 
			case 2:
				teacher_student_in_class(); 
				break;  
			case 3:
				teacher_input_student_course_score();
				break;
			case 4:
				teacher_change_student_course_score();
				break;
			case 5:
				teacher_count_student_score();
				break;
			case 6:
				printf("\t\t您已退出老师系统\n");
				printf("\t\t");system("pause");
				system("cls");
				goto then ;//退出系统
			default:
				printf("\t\t输入值无效,请重新输入\n~");
				printf("\t\t");system("pause");
				continue;
			}
		}
		then:log_in_fun();
		
		
	}
}

Student* createNewStudent(int student_id,char student_name[20],char student_tel[20]){
	Student* new_student = (Student*)calloc(1, sizeof(Student));
	new_student->student_id=student_id;
	strcpy(new_student->student_name,student_name);
	strcpy(new_student->student_tel,student_tel);
	new_student->next=NULL;
	new_student->stu_course=NULL;
	return new_student;
	return NULL;
}
void deleteCourse(Student* student,int course_id){
	if(student->stu_course==NULL){
		return;
	}
	Stu_self_course* pre=NULL;
	Stu_self_course* cur=student->stu_course;
	while(cur!=NULL){
		if(cur->course_id==course_id){
			if(pre==NULL){
				student->stu_course=cur->next;
			}else{
				pre->next=cur->next;
			}
			free(cur);
			break;
		}
		pre=cur;
		cur=cur->next;
	}
}
void appendStudnet(Student** studentList,Student* new_student){
	if(*studentList==NULL){
		*studentList=new_student;
		return;
	}
	Student* temp=*studentList;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=new_student;
}

void student_course_info(){
	printf("\t\t当前可选课程如下\n");
	printf("\t\t——————————————————————————————————————————————————————————————\n");
	show_info_course(root);
}
//将学生选择的课程添加至学生信息-课程里
void addCourseToStudent(Student* student,Stu_self_course* new_course){
	if(student->stu_course==NULL){
		student->stu_course=new_course;
		return;
	}
	Stu_self_course* temp=student->stu_course;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=new_course;
}
//将学生添加至老师-班级里
class_stu* createNewClassStudent(int student_id,char student_name[20]){
	class_stu* new_student=(class_stu*)malloc(sizeof(class_stu));
	new_student->student_id=student_id;
	strcpy(new_student->student_name,student_name);
	new_student->next=NULL;
	new_student->student_score=0;
	 
	return new_student;
}
void addStudentToCourse(Teacher* teacher,class_stu* student){
	//如果课程中没有学生，将新学生设为学生链表的头节点
	if(teacher->class_stu_list==NULL){
		teacher->class_stu_list=student;
		return;
	}else{  // 否则，遍历到学生链表末尾并添加新学生
		class_stu* temp=teacher->class_stu_list;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=student;
	}
}
Stu_self_course* createNewStu_self_course(char student_name[20],char course_name[20],char course_teacher[20],int score,int course_id,int teacher_id){
	Stu_self_course* new_course=(Stu_self_course*)malloc(sizeof(Stu_self_course));
	strcpy(new_course->student_name,student_name);
	strcpy(new_course->course_name,course_name);
	strcpy(new_course->course_teacher,course_teacher);
	new_course->score=score;
	new_course->status=1;
	new_course->next=NULL;
	new_course->course_id=course_id;
	new_course->teacher_id=teacher_id;
	return new_course;
}
void student_select_course(){
	student_course_info();
	printf("\t\t请输入您要选择的课程对应的老师工号:");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* find_teacher=search_teacher_node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\t未找到该老师的课程!\n");
		printf("\t\t");system("pause");
		return;
	}else{
		printf("\t\t该老师开设的课程为:%s\t",find_teacher->course_name);
		printf("\t\t总容量为%d\t",find_teacher->course_capacity);
		printf("\t\t剩余容量为%d\n",find_teacher->course_remain);
		if(find_teacher->course_remain<=0){
			printf("\t\t该课程已满,请选择其他课程!\n");
		}else{
			find_teacher->course_remain--;
			find_teacher->course_selected++;
			class_stu* new_student_now=createNewClassStudent(student_now->student_id,student_now->student_name);
			addStudentToCourse(find_teacher,new_student_now);
			Stu_self_course* new_course=createNewStu_self_course(student_now->student_name,find_teacher->course_name,find_teacher->teacher_name,0,find_teacher->course_id,find_teacher->teacher_id);
			addCourseToStudent(student_now,new_course);
			printf("\t\t选课成功!\n");
		}
	}
}
void student_cancel_course(){
	Stu_self_course* temp1=student_now->stu_course;
	printf("\t\t您所选的课程为:\n");
	while(temp1!=NULL){
		if(temp1->status==false){
			printf("\t\t课程:%s\t课程号:%d\t",temp1->course_name, temp1->course_id);
			printf("老师:%s\n",temp1->course_teacher);
		}
		temp1=temp1->next;
	}
	printf("\t\t请输入您要取消的课程号: ");
	int course_ID;
	scanf("%d", &course_ID);
	Stu_self_course*temp=student_now->stu_course;
	while(temp != NULL) {
		if(temp->course_id == course_ID) {
			deleteCourse(student_now, course_ID);  // 删除课程
			break;
		}
		temp = temp->next;
	}
	if(temp==NULL){
		printf("\t\t找不到对应的课程号,无法取消选课。\n");
		return;
	}
	Teacher* teacher=search_teacher_node(root,temp->teacher_id);
	if(teacher==NULL){
		printf("无法找到该课程的教师信息!\n");
		printf("\t\t");system("pause");
	}else{
		teacher->course_remain++;
		teacher->course_selected--;
		deleteStudentFromTeacher(teacher, student_now->student_id);
		printf("\t\t退课成功!\n");
		printf("\t\t");system("pause");
	}
	
}
void student_query_score(){
	Stu_self_course* temp=student_now->stu_course;
	printf("\t\t您选择的课程有:\n");
	if(temp==NULL){
		printf("\t\t您还未选择任何课程!\n");
		printf("\t\t");system("pause");
		return;
	}
	while(temp!=NULL){
		printf("\t\t课程名称:%s:\t",temp->course_name);
		if(temp->score==0){
			printf("\t\t成绩还未登记!\n");
		}else{
			printf("\t\t成绩:%d\n",temp->score);
		}
		
		temp=temp->next;
	}
	//printf("\t\t");system("pause");
}
void student_output_all_courses(){
	Stu_self_course* temp=student_now->stu_course;
	if(temp==NULL){
		printf("\t\t还未选择任何课程!\n");
		return;
	}
	printf("\t\t您所选的课程为:\n");
	while(temp!=NULL){
		if(temp->status==1){
			printf("\t\t课程:%s\t",temp->course_name);
			printf("老师:%s",temp->course_teacher);
			if(temp->score==0){
				printf("\t成绩:暂未登记！\n");
			}else{
				printf("\t成绩:%d\n",temp->score);
			}
		}
		temp=temp->next;
	}
	//printf("\t\t");system("pause");
}
void student_fun(){
	if(course_num==0){
		printf("\n\n\n\t\t当前课程总数为0,系统还未登记，无法进行操作\n\t\t请管理员先创建课程!\n");
		printf("\t\t");system("pause");
		return;
	}else{
		FILE* file =  fopen("D:\\data_struct_design\\stu_info.txt","r");
		if(file==NULL){
			printf("无法打开文件!");
			return;
		}
		char buffer[512];
		
		fgets(buffer, sizeof(buffer), file); // 忽略标题行
		while(fgets(buffer, sizeof(buffer), file)){
			char student_name[20];
			int student_id;
			char student_tel[20];
			char stu_account[20];
			sscanf(buffer, "%s %s %*s %d %s", student_name,stu_account, &student_id,student_tel);
			if(strcmp(stu_account,id)==0){
				appendStudnet(&studentList,createNewStudent(student_id,student_name,student_tel));
				student_now=createNewStudent(student_id,student_name,student_tel);
			}
		}
		
		while(1){
			printf("\t\t");system("pause");
			system("cls");
			showMenu_student();
			int select;
			scanf("%d",&select);
			printf("\t\t");system("pause");
			system("cls");
			switch(select)
			{
			case 1:
				student_course_info();
				break; 
			case 2:
				student_select_course(); 
				break;  
			case 3:
				student_cancel_course();
				break;
			case 4:
				student_query_score();
				break;
			case 5:
				student_output_all_courses();
				break;
			case 6:
				printf("\t\t您已退出学生系统\n");
				printf("\t\t");system("pause");
				goto then ;//退出系统 
			default:
				printf("\t\t输入值无效,请重新输入\n~");
				printf("\t\t");system("pause");
				continue;
			}
		}
		then:log_in_fun();
	}
	
}

void admin_menu(){
	printf("\t\t    \t 课程管理信息系统-管理员  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].创建课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].添加课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].删除课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].统计课程总数  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].查询每门课修课的人数  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].浏览计算机专业的课程信息  ** \n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [7].退出  *\t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t 输入序号以选择对应功能 : "); 
}
void teacher_menu(){
	printf("\t\t    \t 课程管理信息系统-老师  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].查询所开课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].查询课程学生信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].输入学生课程成绩  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].修改学生课程成绩  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].统计成绩人数分布  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].退出  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t 输入序号以选择对应功能 : "); 
}
void student_menu(){
	printf("\t\t    \t 课程管理信息系统-学生  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].查询课程信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].报名课程学习  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].取消课程学习  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].查询课程成绩  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].浏览所有课程的信息  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].退出  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t 输入序号以选择对应功能 : "); 
}
void log_in(){
	printf("\t\t    \t 课程管理信息系统  \t    \n");
	printf("\t\t------------------------------\n\n");
	printf("\t\t账号: ");
	strcpy(id, ""); // 清空数组
	strcpy(key, "");  
	scanf("%s",id);
	printf("\t\t密码: "); 
	scanf("%s",key);
	FILE *file=fopen("D:\\data_struct_design\\accounts.txt","r");
	if(file==NULL){
		printf("\t\t无法打开文件!");
		return;
	}
	char buffer[512];
	fgets(buffer, sizeof(buffer), file); // 忽略标题行
	while(fgets(buffer, sizeof(buffer), file)){
		Account account;
		sscanf(buffer, "%s %s %s %s %s", account.name, account.account, account.password, account.work_id, account.role);
		if(strcmp(account.account,id)==0&&strcmp(account.password,key)==0){
			printf("\t\t登录成功!\n");
			printf("\t\t");system("pause");
			system("cls");
			if(strcmp(account.role,"管理员")==0){
				admin_fun();
				fclose(file); // 关闭文件
				return;
			}
			else if(strcmp(account.role,"老师")==0){
				teacher_fun();
				fclose(file); // 关闭文件
				return;
			}
			else if(strcmp(account.role,"学生")==0){
				student_fun();
				fclose(file); // 关闭文件
				return;
			}
		}
		
	}
	printf("\t\t账号或密码不正确!请重试。\n");
	printf("\t\t");
	system("pause");
	
	return;
}
void login_menu(){
	printf("\t\t    \t 课程管理信息系统  \t    \n");
	printf("\t\t------------------------------\n\n");
	printf("\t\t1. 登录\n");
	printf("\t\t0. 退出\n");
	printf("\t\t请选择: ");
}
void log_in_fun(){
	while(1){
		system("cls");	
		login_menu();
		int choice;scanf("%d",&choice);
		switch (choice) {
		case 1:
			printf("\t\t");system("pause");
			system("cls");
			log_in();
			break;
		case 0:
			printf("\n\t\t\t感谢使用,再见!\n\n");
			return;
		default:
			printf("\n\t\t\t请选择有效的选项!\n\n");
			printf("\t\t");
			system("pause");
			continue;
		}
	}
	printf("\t\t");
	system("pause");
}

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	//menu_fun();
	admin_read_file_course();//读取文件里的课程信息
	log_in_fun();
	return 0;
}