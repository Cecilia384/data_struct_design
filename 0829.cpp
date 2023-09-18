#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int MAX=110;
int course_num=0;   //课程数量
bool id_status[MAX]; //学生id是否注册
const int admin_key=112234;
typedef struct Student{
	int student_id;
	char student_name[20];
	char student_tel[20];
	struct Student* next; //指向下一个学生
	struct Student* same_class_student; //指向同班学生的下一个  
	struct Stu_self_course* stu_course;//学生所选的课程
}Student;
typedef struct Course{
	char course_name[20];
	int course_id;          //课程号
	int course_credit;      //学分
	int course_capacity;    //总人数容量
	int course_selected;    //当前选课人数
	int course_remain;      //剩余容量
	bool status;            //课程状态--是否被删除,默认为false
	char course_teacher[20];
	char course_time[20];
}Course;
typedef struct Stu_self_course{  //学生选择的课程信息
	char student_name[20];
	char course_name[20];
	int course_id;          //课程号
	int course_credit;      //学分
	char course_teacher[20];
	int teacher_id;
	int score;              //学生课程成绩
	bool status;            //课程状态--是否被删除,默认为false
	struct Stu_self_course* next;    //指向下一个课程
}Stu_self_course;

typedef struct Teacher{
	char teacher_name[20];
	int teacher_id;
	Course* course;
	Student* student_list;
	Teacher* left;
	Teacher* right;
}Teacher;

Teacher* root=NULL;
Student* studentList=NULL;      //学生系统的学生链表
Student* student_now=NULL;      //正在使用系统的学生
Teacher* teacher_now=NULL;      //正在使用系统的老师
void showMenu();
void menu_fun();
void PrintStudentList(Student* StudentList); 
Student* FindStudent(Student* StudentList,int student_id);
void addCourseToStudent(Student* student,Stu_self_course* new_course);
void deleteCourse(Student* student,int course_id);
void showMenu()
{
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t 课程管理信息系统  \t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  请选择用户类型 *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].管理员  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].老师  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].学生  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [4].退出  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t******************************************\n");
	
	printf("\n\t\t**\t 输入序号以选择对应功能 : "); 
}
void showMenu_teacher()
{
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t 学生选课系统-老师  \t**\n");
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
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t 学生选课系统-管理员  \t**\n");
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
	
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t 学生选课系统-学生  \t**\n");
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

Course* createNewCourse(char course_name[20],int course_id,int course_credit,int course_capacity,char course_teacher[20],char course_time[20]){
	Course* new_course = (Course*)calloc(1, sizeof(Course));
	strcpy(new_course->course_name,course_name);
	new_course->course_id=course_id;
	new_course->course_credit=course_credit;
	new_course->course_capacity=course_capacity;
	new_course->course_selected=0;
	new_course->status=false;
	new_course->course_remain=course_capacity;
	strcpy(new_course->course_teacher,course_teacher);
	strcpy(new_course->course_time,course_time);
	return new_course;
}
Teacher* createNewTeacher(char teacher_name[20],int teacher_id){
	Teacher* new_teacher = (Teacher*)calloc(1, sizeof(Teacher));
	strcpy(new_teacher->teacher_name,teacher_name);
	new_teacher->teacher_id=teacher_id;
	new_teacher->course=NULL;
	new_teacher->student_list=NULL;
	new_teacher->left=NULL;
	new_teacher->right=NULL;
	return new_teacher;
}

// 插入老师结点
Teacher* insert_Teacher_Node(Teacher* root,Teacher* new_teacher){
	if(root==NULL){
		root=new_teacher;
		return root;
	}
	if(new_teacher->teacher_id<root->teacher_id){
		root->left=insert_Teacher_Node(root->left,new_teacher);
	}
	else if(new_teacher->teacher_id>root->teacher_id){
		root->right=insert_Teacher_Node(root->right,new_teacher);
	}
	return root;
}

// 查找老师结点，若找到则返回该结点，否则返回NULL
Teacher* search_Teacher_Node(Teacher* root,int teacher_id){
	
	if(root==NULL||root->teacher_id==teacher_id){
		return root;
	}
	else if(teacher_id<root->teacher_id){
		return search_Teacher_Node(root->left,teacher_id);
	}
	else{
		return search_Teacher_Node(root->right,teacher_id);
	}
}

//中序遍历以老师工号为关键字的二叉树
Teacher* inorder_Teacher_Node(Teacher* root){
	if(root!=NULL){
		inorder_Teacher_Node(root->left);
		Course* temp=root->course;
		printf("\t\t课程名称:%s\t课程号:%d\t",temp->course_name,temp->course_id);
		printf("\t\t老师:%s\t工号:%d\n",root->teacher_name,root->teacher_id);
		inorder_Teacher_Node(root->right);
	}
	return root;
}
//展示选课界面(中序遍历一次)
Teacher* show_course_info(Teacher* root){
	
	printf("\t\t当前课程总数为:%d\n",course_num );
	if(root!=NULL){
		inorder_Teacher_Node(root->left);
		Course* temp=root->course;
		printf("\n\t\t课程名称:%s\t课程号:%d\t课程学分:%d\t课程容量:%d\t课程剩余容量:%d\n",temp->course_name,temp->course_id,temp->course_credit,temp->course_capacity,temp->course_remain);
		printf("\t\t任课老师:%s\t老师工号:%d\t课程上课时间:%s\n",temp->course_teacher,root->teacher_id,temp->course_time);
		show_course_info(root->right);
	}
	return root;
}
//删除老师结点
Teacher* delete_Teacher_Node(Teacher* root,int teacher_id){
	if(root==NULL){
		return root;
	}
	if(teacher_id < root->teacher_id){
		root->left=delete_Teacher_Node(root->left,teacher_id);
	}else if(teacher_id > root->teacher_id){
		root->right=delete_Teacher_Node(root->right,teacher_id);
	}else{
		// 当前节点没有子节点或只有一个子节点
		if(root->left==NULL){
			Teacher* temp=root->right;
			free(root);
			return temp;
		}else if(root->right==NULL){
			Teacher* temp=root->left;
			free(root);
			return temp;
		}else{
			Teacher* find_node=root->right;
			// 找到右子树的最小节点（继任者）
			while(find_node->left!=NULL){
				find_node=find_node->left;
			}
			// 用继任者的值替代要删除的节点
			root->teacher_id=find_node->teacher_id;
			strcpy(root->teacher_name,find_node->teacher_name);
			root->right=delete_Teacher_Node(root->right,find_node->teacher_id);
		}
	}
	return root;
}
void admin_add_course(){
//	system("cls");
	printf("\t\t请输入需要添加的课程信息\n");
	printf("\n\t\t课程名: ");    char course_name[20];      scanf("%s",course_name);
	printf("\t\t课程号: ");    int course_id;             scanf("%d",&course_id);
	printf("\t\t学分: ");      int course_credit;         scanf("%d",&course_credit);
	printf("\n\t\t总容量: ");    int course_capacity;       scanf("%d",&course_capacity);
	printf("\t\t任课老师: ");  char course_teacher[20];   scanf("%s",course_teacher);
	printf("\t\t老师工号: ");  int teacher_id;            scanf("%d",&teacher_id);
	printf("\n\t\t上课时间:");   char course_time[20];      scanf("%s",course_time);
	Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id);
	Course* new_course=createNewCourse(course_name,course_id,course_credit,course_capacity,course_teacher,course_time);
	new_teacher->course=new_course;
	course_num++;
	root=insert_Teacher_Node(root,new_teacher); //插入老师结点
	printf("\n\t\t课程%s-%d信息录入成功!\n",course_name,course_id );
}
void admin_delete_course(){
	if(course_num==0){
		printf("\t\t当前没有开设课程!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("当前开设课程的老师有:\n");
	inorder_Teacher_Node(root);
	printf("请输入要删除课程的老师工号:");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* find_teacher=search_Teacher_Node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\t未找到该老师,请重新输入\n");
		printf("\t\t");system("pause");
		return;
	}
	else{
		printf("\t\t该老师开设的课程为:%s\t",find_teacher->course->course_name);
		printf("\t\t学生人数为:%d\n",find_teacher->course->course_selected);
		printf("\t\t是否删除该课程?(y/n)");
		char choice;scanf("%s",&choice);
		if(choice=='y'){
			find_teacher->course->status=true;
			course_num--;
			int del_course_id=find_teacher->course->course_id;
			Student* temp=find_teacher->student_list;
			while(temp!=NULL){
				deleteCourse(temp,del_course_id);
				temp=temp->same_class_student;
			}
			delete_Teacher_Node(root,teacher_id);
			printf("\t\t删除成功!\n");
			printf("\t\t");system("pause");
		}
	}
}
void admin_create_course(){
//	system("cls");
	printf("\t\t请输入要创建的课程总数:");
	int course_num_now;
	scanf("%d",&course_num_now);
	while(course_num_now--){
		printf("\t\t请输入课程信息\n");
		printf("\n\t\t课程名: ");    char course_name[20];      scanf("%s",course_name);    fflush(stdin);
		printf("\t\t课程号: ");    int course_id;             scanf("%d",&course_id);       fflush(stdin);
		printf("\t\t学分: ");      int course_credit;         scanf("%d",&course_credit);   fflush(stdin);
		printf("\n\t\t总容量: ");    int course_capacity;       scanf("%d",&course_capacity);fflush(stdin);
		printf("\t\t任课老师: ");  char course_teacher[20];   scanf("%s",course_teacher);   fflush(stdin);
		printf("\t\t老师工号: ");  int teacher_id;            scanf("%d",&teacher_id);      fflush(stdin);
		printf("\n\t\t上课时间:");   char course_time[20];      scanf("%s",course_time);    fflush(stdin);
		Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id);
		Course* new_course=createNewCourse(course_name,course_id,course_credit,course_capacity,course_teacher,course_time);
		new_teacher->course=new_course;
		course_num++;
		//调试
		printf("\n\t\t test--course_num=%d\n",course_num);
		root=insert_Teacher_Node(root,new_teacher); //插入老师结点
		printf("\n\t\t课程%s-%d信息录入成功!\n",course_name,course_id );
		//调试
		printf("\t\tyou add a course\n");
		printf("\t\t course_name:%s\tcourse_id:%d\tcourse_credit:%d\tcourse_capacity:%d\tcourse_teacher:%s\tteacher_id:%d\tcourse_time:%s\n",course_name,course_id,course_credit,course_capacity,course_teacher,teacher_id,course_time);
		if(course_num_now!=0){
			system("cls");
			printf("\n\t\t还需创建%d门课程\n\n",course_num_now );
			
		}
		else {
			printf("\n\t\t课程录入完成!");
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
//	system("cls");
	if(course_num==0){
		printf("\t\t当前还未开设任何课程!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t当前开设的课程有:\n");
	inorder_Teacher_Node(root);
	printf("\t\t请输入要查询课程的老师工号\n");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher *find_teacher=search_Teacher_Node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\t未找到该老师,请重新输入\n");
		printf("\t\t");system("pause");
		return;
	}
	else{
		printf("\t\t该老师开设的课程为:%s\t",find_teacher->course->course_name);
		printf("\t\t学生人数为%d:\n",find_teacher->course->course_selected);
		printf("\t\t");system("pause");
	}
}
void admin_output_all_courses(){
//	system("cls");
	if(course_num==0){
		printf("\t\t当前还未开设任何课程!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t当前开设的课程有:\n");
	inorder_Teacher_Node(root);
	printf("\t\t");system("pause");
}

void teacher_course_info(){
//	system("cls");
	printf("\t\t您当前开设的课程为:\n");
	printf("\t\t课程名称:%s\t课程号:%d\t",teacher_now->course->course_name,teacher_now->course->course_id);
	printf("\t\t总容量为%d\t",teacher_now->course->course_capacity);
	printf("\t\t当前选课人数:%d\t",teacher_now->course->course_selected);
	printf("\t\t");system("pause");
}
void teacher_student_in_class(){
//	system("cls");
	printf("\t\t您所在班级里的学生为:\n");
	PrintStudentList(teacher_now->student_list);
	printf("\t\t");system("pause");
}
void teacher_input_student_course_score(){
	//system("cls");
	Student* temp=teacher_now->student_list;
	while(temp!=NULL){
		printf("\t\t请输入学生%s的成绩: ",temp->student_name);
		int score;scanf("%d",&score);
		Stu_self_course* temp_course=temp->stu_course;
		while(temp_course!=NULL){
			if(temp_course->course_id==teacher_now->course->course_id){
				temp_course->score=score;
				break;
			}
			temp_course=temp_course->next;
		}
		temp=temp->same_class_student;
	}
	printf("\t\t");system("pause");
}
void teacher_change_student_course_score(){
//	system("cls");
	printf("\t\t您所在班级里的学生为:\n");
	PrintStudentList(teacher_now->student_list);
	printf("\t\t请输入要修改成绩的学生学号:");
	int student_id;scanf("%d",&student_id);
	Student* find_student=FindStudent(teacher_now->student_list,student_id);
	if(find_student==NULL){
		printf("\t\t未找到该学生,请重新输入\n");
		printf("\t\t");system("pause");
		return;
	}
	else{
		printf("\t\t请输入修改后学生%s的成绩: ",find_student->student_name);
		int score;scanf("%d",&score);
		Stu_self_course* temp_course=find_student->stu_course;
		while(temp_course!=NULL){
			if(temp_course->course_id==teacher_now->course->course_id){
				temp_course->score=score;
				break;
			}
			temp_course=temp_course->next;
		}
	}
	printf("\t\t");system("pause");
}
void teacher_count_student_score(){
//	system("cls");
	//+,90,80,60,-
	int count[5]={0};
	Student* temp=teacher_now->student_list;
	while(temp!=NULL){
		Stu_self_course* temp_course=temp->stu_course;
		while(temp_course!=NULL){
			if(temp_course->course_id==teacher_now->course->course_id){
				if(temp_course->score>=90){
					count[0]++;
				}else if(temp_course->score>=80){
					count[1]++;
				}else if(temp_course->score>=60){
					count[2]++;
				}else{
					count[3]++;
				}
				break;
			}
			temp_course=temp_course->next;
		}
		temp=temp->same_class_student;
	}
	printf("\t\t成绩分布为:\n");
	printf("\t\t90分以上:%d\t80-89分:%d\t60-79分:%d\t60分以下:%d\n",count[0],count[1],count[2],count[3]);
	printf("\t\t");system("pause");
}
Stu_self_course* createNewCourse(char course_name[20],int course_id,int course_credit,char course_teacher[20],int teacher_id){
	Stu_self_course* new_course = (Stu_self_course*)calloc(1, sizeof(Stu_self_course));
	strcpy(new_course->course_name,course_name);
	new_course->course_id=course_id;
	new_course->course_credit=course_credit;
	strcpy(new_course->course_teacher,course_teacher);
	new_course->teacher_id=teacher_id;
	new_course->score=0;
	new_course->next=NULL;
	return new_course;
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
//学生退课时，删除该信息结点
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
//退课的同时,也应该在老师的班级里删除学生信息
void deleteStudentFromTeacher(Teacher* teacher,int student_id){
	if(teacher->student_list==NULL){
		return;
	}
	Student* pre=NULL;
	Student* cur=teacher->student_list;
	while(cur!=NULL){
		if(cur->student_id==student_id){
			if(pre==NULL){
				teacher->student_list=cur->same_class_student;
			}else{
				pre->same_class_student=cur->same_class_student;
			}
			free(cur);
			break;
		}
		pre=cur;
		cur=cur->same_class_student;
	}
}
//打印学生选择的课程
void printStudentCourse(Student* student){
	Stu_self_course* temp=student->stu_course;
	printf("\t\t您选择的课程有:\n");
	while(temp!=NULL){
		printf("\t\t课程名称:%s\t课程号:%d\t",temp->course_name,temp->course_id);
		printf("\t\t老师:%s\t工号:%d\n",temp->course_teacher,temp->teacher_id);
		printf("\t\t成绩:%d\n",temp->score);
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
Student* createNewStudent(int student_id,char student_name[20],char student_tel[20]) {
	Student* new_student = (Student*)calloc(1, sizeof(Student));
	new_student->student_id=student_id;
	strcpy(new_student->student_name,student_name);
	strcpy(new_student->student_tel,student_tel);
	new_student->next=NULL;
	new_student->stu_course=NULL;
	return new_student;
}

void appendStudnet(Student** StudentList,Student* new_student){
	if(*StudentList==NULL){
		*StudentList=new_student;
		return;
	}
	Student* temp=*StudentList;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=new_student;
}
//将学生添加至老师-课程里
void addStudentToCourse(Teacher* teacher,Student* student){
	//如果课程中没有学生，将新学生设为学生链表的头节点
	if(teacher->student_list==NULL){
		teacher->student_list=student;
		return;
	}else{  // 否则，遍历到学生链表末尾并添加新学生
		Student* temp=teacher->student_list;
		while(temp->same_class_student!=NULL){
			temp=temp->same_class_student;
		}
		temp->same_class_student=student;
	}
}

//输出学生链表
void PrintStudentList(Student* StudentList){
	Student* temp=StudentList;
	while(temp!=NULL){
		printf("\t\t学生姓名:%s\t学号:%d\n",temp->student_name,temp->student_id);
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
//根据学生id查找学生
Student* FindStudent(Student* StudentList,int student_id){
	Student* temp=StudentList;
	while(temp!=NULL){
		if(temp->student_id==student_id){
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}

void student_course_info(){
	//system("cls");
	printf("\t\t当前可选课程有:\n");
	show_course_info(root);
	printf("\t\t");system("pause");
}
void student_select_course(){
	//system("cls");
	printf("\t\t请输入您要选择的课程对应的老师工号:");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* find_teacher=search_Teacher_Node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\t未找到该老师,请重新输入\n");
		printf("\t\t");system("pause");
		return; }
	else{
		printf("\t\t该老师开设的课程为:%s\t",find_teacher->course->course_name);
		printf("\t\t总容量为%d\t",find_teacher->course->course_capacity);
		printf("\t\t剩余容量为%d\n",find_teacher->course->course_remain);
		if(find_teacher->course->course_remain<=0){
			printf("\t\t该课程已满,请选择其他课程!\n");
		}else{
			find_teacher->course->course_remain--;
			find_teacher->course->course_selected++;
			addStudentToCourse(find_teacher,student_now);
			Stu_self_course* new_course=createNewCourse(find_teacher->course->course_name,find_teacher->course->course_id,find_teacher->course->course_credit,find_teacher->course->course_teacher,find_teacher->teacher_id);
			new_course->score=0;
			new_course->next=NULL;
			strcpy(new_course->student_name,student_now->student_name);
			addCourseToStudent(student_now,new_course);
			printf("\t\t选课成功!\n");
			
		}
	}
	printf("\t\t");system("pause");
}
void student_cancel_course(){
	printf("请输入您要取消的课程号: ");
	int coure_ID;scanf("%d",&coure_ID);
	Stu_self_course* temp=student_now->stu_course;
	while(temp!=NULL){
		if(temp->course_id==coure_ID){
			deleteCourse(student_now,coure_ID);
			break;
		}
		temp=temp->next;
	}
	Teacher* find_teacher=search_Teacher_Node(root,temp->teacher_id);
	find_teacher->course->course_remain++;
	find_teacher->course->course_selected--;
	deleteStudentFromTeacher(find_teacher,student_now->student_id);
	printf("\t\t退课成功!\n");
	printf("\t\t");system("pause");
	
	
}
void student_query_score(){
	Stu_self_course* temp=student_now->stu_course;
	printf("\t\t您选择的课程有:\n");
	while(temp!=NULL){
		printf("\t\t课程名称:%s:\t",temp->course_name);
		if(temp->score==0){
			printf("\t\t成绩还未登记!\n");
		}else{
			printf("\t\t成绩:%d\n",temp->score);
		}
		
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
void student_output_all_courses(){
//	system("cls");  
	printStudentCourse(student_now);
	
}

void admin_fun(){
	
	printf("\t\t请输入管理员账户密码\n\t\t");
	int in_key;scanf("%d",&in_key);
	// 清空输入缓冲区
	while ((getchar()) != '\n');
	if(in_key==admin_key){
		
		printf("\t\t登陆成功!\n");
		printf("\t\t");system("pause");
		
	}else{
		printf("\t\t密码错误,请重新输入!\n");
		return;
	}
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
			return ;//退出系统
		default:
			printf("\t\t输入值无效,请重新输入\n~");
			system("pause");
			continue;
		}
		
	}
	
	menu_fun();
}
void teacher_fun(){
	//system("cls");
	if(course_num==0){
		printf("\n\n\n\t\t当前课程总数为0,系统还未登记，无法进行操作\n\t\t请管理员先创建课程!\n");
		return;
	}else{
		printf("\t\t请输入您的工号:");
		int teacher_id;scanf("%d",&teacher_id);
		teacher_now=search_Teacher_Node(root,teacher_id);
		if(teacher_now==NULL){
			printf("\t\t管理员还未添加您的课程!请联系管理员\n");
			return;
		}
		while(1){
			system("cls");
			//system("COLOR fd");
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
				return ;//退出系统
			default:
				printf("\t\t输入值无效,请重新输入\n~");
				system("pause");
				continue;
			}
		}
		menu_fun();
		
		
	}
}
void student_fun(){
	//system("cls");
	if(course_num==0){
		printf("\n\n\n\t\t当前课程总数为0,系统还未登记，无法进行操作\n\t\t请管理员先创建课程!\n");
		return;
	}else{
		printf("\t\t请输入您的学号:");
		int student_id;scanf("%d",&student_id) ;
		
		if(id_status[student_id]==false){
			printf("\t\t您还未注册,请完善信息之后重新登入\n");
			printf("\t\t请输入您的姓名:");
			char student_name[20];scanf("%s",student_name);
			printf("\t\t请输入您的电话:");char student_tel[20];scanf("%s",student_tel); 
			appendStudnet(&studentList,createNewStudent(student_id,student_name,student_tel));
			id_status[student_id]=true;  
			printf("\t\t注册成功!\n");
			return;
		}else{
			student_now=FindStudent(studentList,student_id);
		}
		while(1){
			//	system("cls");
			//system("COLOR fd");
			system("pause");
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
				return ;//退出系统
			default:
				printf("\t\t输入值无效,请重新输入\n~");
				system("pause");
				continue;
			}
		}
		menu_fun();
	}
	
}
void menu_fun(){
	while(1)
	{
		//system("COLOR fd");
		
		system("cls");	//清空控制台窗口中的所有内容。 
		showMenu();
		int select;
		scanf("%d",&select);
		while ((getchar()) != '\n');
		switch(select)
		{
		case 1:
			system("cls");
			admin_fun(); 
			break; 
		case 2:
			teacher_fun();
			break;  
		case 3:
			student_fun();
			break;
		case 4 :
			printf("\t\t您已退出学生管理系统\n");
			system("pause");
			return ;
		default:
			printf("\t\t输入值无效,请重新输入\n~");
			system("pause");
			continue;
		}
		system("pause");
		// 会暂停程序的执行，等待用户按下任意键后继续执行
		
	}
	system("pause");
}

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	menu_fun();
	return 0;
}
