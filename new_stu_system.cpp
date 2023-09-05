#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_ACCOUNT_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_NAME_LEN 50
#define MAX_WORKID_LEN 20
const int MAX=110;
int course_num=0;   //�γ�����
char id[MAX_ACCOUNT_LEN];
char key[MAX_PASSWORD_LEN];
Teacher* root=NULL;
Student* studentList=NULL;      //ѧ��ϵͳ��ѧ������ 
Student* student_now=NULL;      //����ʹ��ϵͳ��ѧ��
Teacher* teacher_now=NULL;      //����ʹ��ϵͳ����ʦ
typedef struct Teacher{
	char teacher_name[20];
	int teacher_id;
	char course_name[20];
	int course_id;          //�γ̺�
	int course_credit;      //ѧ��
	int course_capacity;    //����������
	int course_selected;    //��ǰѡ������
	int course_remain;      //ʣ������
	char course_time[20];   //�Ͽ�ʱ��
	char course_place[20];  //�Ͽεص�
	bool status;            //�γ�״̬--�Ƿ�ɾ��,Ĭ��Ϊfalse
    class_stu* class_stu_list;   //ָ��༶ѧ����ָ��
	Teacher* left;
	Teacher* right;
}Teacher;
 //ͬһ���༶���ѧ��
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
	struct Stu_self_course* stu_course;//ѧ����ѡ�Ŀγ�
	Student* next;
}Student;

typedef struct Stu_self_course{  //ѧ��ѡ��Ŀγ���Ϣ
	char student_name[20];
	char course_name[20];
	char course_teacher[20];//�ο���ʦ
	int score;              //ѧ���γ̳ɼ�
	bool status;            //�γ�״̬--�Ƿ�ɾ��,Ĭ��Ϊfalse
	struct Stu_self_course* next;    //ָ����һ���γ�
}Stu_self_course;
typedef struct {
	char name[MAX_NAME_LEN];
	char account[MAX_ACCOUNT_LEN];
	char password[MAX_PASSWORD_LEN];
	char work_id[MAX_WORKID_LEN];
	char role[MAX_NAME_LEN];
} Account;
void log_in_fun();
void log_in();
void login_menu();
void showMenu_Adimn(){}
void showMenu_Teacher(){}
void showMenu_Student(){}

Teacher* createNewTeacher(char teacher_name[20],int teacher_id,char course_name[20],int course_id,int course_credit,int course_capacity,char course_time[20],char course_place[20]){
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
	new_teacher->status=false;
	new_teacher->left=NULL;
	new_teacher->right=NULL;
	new_teacher->class_stu_list=NULL;
	return new_teacher;
}
// ������ʦ���
Teacher* insert_teacher_node(Teacher* root,Teacher* new_teacher){
	if(root==NULL){
		root=new_teacher;
		return root;
	}
	if(new_teacher->course_id<root->course_id){
		root->left=insert_teacher_node(root->left,new_teacher);
	}
	else if(new_teacher->course_id>root->course_id){
		root->right=insert_teacher_node(root->right,new_teacher);
	}
	return root;
}
// ������ʦ��㣬���ҵ��򷵻ظý�㣬���򷵻�NULL
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
//�����������ʦ����Ϊ�ؼ��ֵĶ�����
Teacher* inorder_Teacher_Node(Teacher* root){
	if(root!=NULL){
		inorder_Teacher_Node(root->left);
		printf("\t\t�γ���: %s",root->course_name);
		printf("\t�γ̺�: %d",root->course_id);
		printf("\t�ο���ʦ: %s",root->teacher_name);
		printf("\t����: %d\n",root->teacher_id);
		inorder_Teacher_Node(root->right);
	}
	return root;
}
Teacher* show_info_course(Teacher* root){
	if(root!=NULL){
		show_info_course(root->left);
		printf("\n\t\t�γ�����:%s\t�γ̺�:%d\t�γ�ѧ��:%d\t������:%d\tʣ������:%d\n",root->course_name,root->course_id,root->course_credit,root->course_capacity,root->course_remain);
		printf("\t\t�ο���ʦ:%s\t����:%d\t�Ͽ�ʱ��:%s\t�Ͽεص�:%s\n",root->teacher_name,root->teacher_id,root->course_time,root->course_place);
		printf("����������������������������������������������������������������������������������������������������������������������������\n");
		show_info_course(root->right);
	}
	return root;
}
void showMenu_teacher()
{
	printf("\t\t    \t �γ̹�����Ϣϵͳ-��ʦ  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].��ѯ�����γ���Ϣ  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].��ѯ�γ�ѧ����Ϣ  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].����ѧ���γ̳ɼ�  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].�޸�ѧ���γ̳ɼ�  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].ͳ�Ƴɼ������ֲ�  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].�˳�  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t ���������ѡ���Ӧ���� : "); 
}
void showMenu_Adimn()
{
	printf("\t\t    \t �γ̹�����Ϣϵͳ-����Ա  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].�����γ���Ϣ  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].��ӿγ���Ϣ  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].ɾ���γ���Ϣ  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].ͳ�ƿγ�����  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].��ѯÿ�ſ��޿ε�����  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].��������רҵ�Ŀγ���Ϣ  ** \n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [7].�˳�  *\t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t ���������ѡ���Ӧ���� : "); 
	
}
void showMenu_student()
{
	printf("\t\t    \t �γ̹�����Ϣϵͳ-ѧ��  \t    \n");
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].��ѯ�γ���Ϣ  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].�����γ�ѧϰ  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].ȡ���γ�ѧϰ  *\t**\n");
	printf("\t\t**\t                        \t**\n"); 
	printf("\t\t**\t*  [4].��ѯ�γ̳ɼ�  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [5].������пγ̵���Ϣ  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [6].�˳�  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t******************************************\n");
	printf("\n\t\t**\t ���������ѡ���Ӧ���� : "); 
}

void admin_create_course(){
	printf("\t\t������Ҫ�����Ŀγ�����:");
	int course_num_now;
	scanf("%d",&course_num_now);
	while(course_num--){
		printf("\t\t������γ���Ϣ\n");
		printf("\n\t\t�γ���: ");    char course_name[20];      scanf("%s",course_name);   
		printf("\t\t�γ̺�: ");    int course_id;             scanf("%d",&course_id);       
		printf("\t\tѧ��: ");      int course_credit;         scanf("%d",&course_credit);    
		printf("\n\t\t������: ");    int course_capacity;       scanf("%d",&course_capacity); 
		printf("\t\t�ο���ʦ: ");  char course_teacher[20];   scanf("%s",course_teacher);  
		printf("\t\t��ʦ����: ");  int teacher_id;            scanf("%d",&teacher_id);       
		printf("\n\t\t�Ͽ�ʱ��:");   char course_time[20];      scanf("%s",course_time);   
		printf("\t\t�Ͽεص�:");   char course_place[20];     scanf("%s",course_place);  
		Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id,course_name,course_id,course_credit,course_capacity,course_time,course_place); 
		course_num++;
		
		if(course_num_now!=0){
			system("cls");
			printf("\n\t\t���贴��%d�ſγ�\n\n",course_num_now );
		}else{
			printf("\n\t\t�γ̴����ɹ�!\n\n");
			//printf("\t\t");system("pause");system("cls");return;
		}
	}
}
void admin_add_course(){
	printf("\t\t������Ҫ��ӵĿγ���Ϣ\n");
	printf("\n\t\t�γ���: ");    char course_name[20];      scanf("%s",course_name);   
	printf("\t\t�γ̺�: ");    int course_id;             scanf("%d",&course_id);       
	printf("\t\tѧ��: ");      int course_credit;         scanf("%d",&course_credit);    
	printf("\n\t\t������: ");    int course_capacity;       scanf("%d",&course_capacity); 
	printf("\t\t�ο���ʦ: ");  char course_teacher[20];   scanf("%s",course_teacher);  
	printf("\t\t��ʦ����: ");  int teacher_id;            scanf("%d",&teacher_id);       
	printf("\n\t\t�Ͽ�ʱ��:");   char course_time[20];      scanf("%s",course_time);     
	printf("\t\t�Ͽεص�:");   char course_place[20];     scanf("%s",course_place);
	Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id,course_name,course_id,course_credit,course_capacity,course_time,course_place); 
	course_num++;
}
void admin_delete_course(){}
void admin_count_course(){
	if(course_num==0){
		printf("\t\t��ǰ��δ�����κογ�!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t��ǰ�γ�����Ϊ:%d\n",course_num );
	printf("\t\t");system("pause");
}
void admin_count_student(){
	if(course_num==0){
		printf("\t\t��ǰ��δ�����κογ�!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t��ǰ����Ŀγ���:\n");
	inorder_Teacher_Node(root);
	printf("\t\t������Ҫ��ѯ�γ̵���ʦ����\n");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* teacher=search_teacher_node(root,teacher_id);
	if(teacher==NULL){
		printf("\t\tδ�ҵ�����ʦ�Ŀγ�!\n");
		printf("\t\t");system("pause");
		return;
	}else{
		printf("����ʦ����Ŀγ�Ϊ:%s\t",teacher->course_name);
		printf("ѧ������Ϊ:%d\n",teacher->course_selected);
		printf("\t\t");system("pause");
	}
}
void admin_output_all_courses(){
	if(course_num==0){
		printf("\t\t��ǰ��δ�����κογ�!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t��ǰ����Ŀγ���:\n");
	inorder_Teacher_Node(root);
	printf("\t\t");system("pause");
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
			printf("\t\t�����˳�����Աϵͳ\n");
			printf("\t\t");
			system("pause");
			system("cls");
			goto then ;//�˳�ϵͳ
		default:
			printf("\t\t����ֵ��Ч,����������\n~");
			system("pause");
			continue;
		}
		
	}
	then:log_in_fun();
	
}

void Print_Class_StudentList(class_stu* StudentList){
	class_stu* temp=StudentList;
	while(temp!=NULL){
		printf("\t\tѧ������:%s\tѧ��:%d\n",temp->student_name,temp->student_id);
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
void teacher_course_info(){
	printf("\t\t����ǰ����Ŀγ�Ϊ:\n");
	printf("\t\t�γ�����:%s\t�γ̺�:%d\t",teacher_now->course_name,teacher_now->course_id);
	printf("\t\t������Ϊ%d\t",teacher_now->course_capacity);
	printf("\t\t��ǰѡ������:%d\t",teacher_now->course_selected);
	printf("\t\t");system("pause");
}
void teacher_student_in_class(){
	printf("\t\t�����ڰ༶���ѧ��Ϊ:\n");
	Print_Class_StudentList(teacher_now->class_stu_list);
	printf("\t\t");system("pause");
}
void teacher_input_student_course_score(){
	class_stu* temp=teacher_now->class_stu_list;
	printf("\t\t������ѧ��%s�ĳɼ�: ",temp->student_name);
	int score;scanf("%d",&score);
	temp->student_score=score;
	 
	 //����ѧ���γ��б�����ĳɼ�

		
}
void teacher_change_student_course_score(){}
void teacher_count_student_score(){}

void teacher_fun(){
	//system("cls");
	if(course_num==0){
		printf("\n\n\n\t\t��ǰ�γ�����Ϊ0,ϵͳ��δ�Ǽǣ��޷����в���\n\t\t�����Ա�ȴ����γ�!\n");
	
		return;
	}else{
		FILE* file =  fopen("D:\\data_struct_design\\stu_info.txt","r");
		if(file==NULL){
			printf("�޷����ļ�!");
			return;
		}
		char buffer[512];
		fgets(buffer, sizeof(buffer), file); // ���Ա�����
		 while(fgets(buffer, sizeof(buffer), file)){
			char teacher_name[20];
			int teacher_id;
			char teacher_accunt[20];
			sscanf(buffer, "%s %s %*s %d %s", teacher_name,teacher_accunt, &teacher_id);
			if(strcmp(teacher_accunt,id )==0){
				teacher_now=search_teacher_node(root,teacher_id);
				if(teacher_now==NULL){
					printf("\t\t����Ա��δ������Ŀγ�!����ϵ����Ա\n");
					printf("\t\t");system("pause");
					return;
				}
			}
		 
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
				printf("\t\t�����˳���ʦϵͳ\n");
				printf("\t\t");
				system("pause");
				system("cls");
				goto then ;//�˳�ϵͳ
			default:
				printf("\t\t����ֵ��Ч,����������\n~");
				system("pause");
				continue;
			}
		}
		then:log_in_fun();
		
		
	}
}
Student* FindStudent(Student* studentList,int student_id){
	Student* temp=studentList;
	while(temp!=NULL){
		if(temp->student_id==student_id){
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
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
	printf("\t\t��ǰ��ѡ�γ�����\n");
	printf("����������������������������������������������������������������������������������������������������������������������������\n");
	show_info_course(root);
}
//��ѧ��ѡ��Ŀγ������ѧ����Ϣ-�γ���
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
//��ѧ���������ʦ-�༶��

void addStudentToCourse(Teacher* teacher,class_stu* student){
	//����γ���û��ѧ��������ѧ����Ϊѧ�������ͷ�ڵ�
	if(teacher->class_stu_list==NULL){
		teacher->class_stu_list=student;
		return;
	}else{  // ���򣬱�����ѧ������ĩβ�������ѧ��
		class_stu* temp=teacher->class_stu_list;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=student;
	}
}
Stu_self_course* createNewStu_self_course(char student_name[20],char course_name[20],char course_teacher[20],int score){
	Stu_self_course* new_course=(Stu_self_course*)malloc(sizeof(Stu_self_course));
	strcpy(new_course->student_name,student_name);
	strcpy(new_course->course_name,course_name);
	strcpy(new_course->course_teacher,course_teacher);
	new_course->score=score;
	new_course->status=false;
	new_course->next=NULL;
	return new_course;
}
void student_select_course(){
	student_course_info();
	printf("\t\t��������Ҫѡ��Ŀγ̶�Ӧ����ʦ����:");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* find_teacher=search_teacher_node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\tδ�ҵ�����ʦ�Ŀγ�!\n");
		printf("\t\t");system("pause");
		return;
	}else{
		printf("\t\t����ʦ����Ŀγ�Ϊ:%s\t",find_teacher->course_name);
		printf("\t\t������Ϊ%d\t",find_teacher->course_capacity);
		printf("\t\tʣ������Ϊ%d\n",find_teacher->course_remain);
		if(find_teacher->course_remain<=0){
			printf("\t\t�ÿγ�����,��ѡ�������γ�!\n");
		}else{
			find_teacher->course_remain--;
			find_teacher->course_selected++;
			addStudentToCourse(find_teacher,student_now);
			Stu_self_course* new_course=createNewStu_self_course(student_now->student_name,find_teacher->course_name,find_teacher->teacher_name,0);
			addCourseToStudent(student_now,new_course);
			printf("\t\tѡ�γɹ�!\n");
		}
	}
	printf("\t\t");system("pause");
}
void student_cancel_course(){}
void student_query_score(){}
void student_output_all_courses(){
	Stu_self_course* temp=student_now->stu_course;
	printf("\t\t����ѡ�Ŀγ�Ϊ:\n");
	while(temp!=NULL){
		printf("\t\t�γ�����:%s\t",temp->course_name);
		printf("��ʦ:%s\n",temp->course_teacher);
		if(temp->score==0){
			printf("\t\t�ɼ�:��δ�Ǽǣ�\n");
		}else{
			printf("\t\t�ɼ�:%d\n",temp->score);
		}
		
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
void student_fun(){
	//system("cls");
	if(course_num==0){
		printf("\n\n\n\t\t��ǰ�γ�����Ϊ0,ϵͳ��δ�Ǽǣ��޷����в���\n\t\t�����Ա�ȴ����γ�!\n");
		printf("\t\t");
		system("pause");
		return;
	}else{
		FILE* file =  fopen("D:\\data_struct_design\\stu_info.txt","r");
		if(file==NULL){
			printf("�޷����ļ�!");
			return;
		}
		char buffer[512];
		
		fgets(buffer, sizeof(buffer), file); // ���Ա�����
		while(fgets(buffer, sizeof(buffer), file)){
			char student_name[20];
			int student_id;
			char student_tel[20];
			char stu_account[20];
			//Student* new_student=(Student*)malloc(sizeof(Student));
			sscanf(buffer, "%s %s %*s %d %s", student_name,stu_account, &student_id,student_tel);
			if(strcmp(stu_account,id)==0){
				appendStudnet(&studentList,createNewStudent(student_id,student_name,student_tel));
				student_now=FindStudent(studentList,student_id);
			}
		}
		
		while(1){
			//	system("cls");
			//system("COLOR fd");
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
				printf("\t\t�����˳�ѧ��ϵͳ\n");
				printf("\t\t");
				system("pause");
				system("cls");
				goto then ;//�˳�ϵͳ 
			default:
				printf("\t\t����ֵ��Ч,����������\n~");
				printf("\t\t");system("pause");
				continue;
			}
		}
		then:log_in_fun();
	}
	
}
 
void menu_fun(){}

void admin_menu(){}
void teacher_menu(){}
void student_menu(){}
void log_in(){
	printf("\t\t    \t �γ̹�����Ϣϵͳ  \t    \n");
	printf("\t\t------------------------------\n\n");
	printf("\t\t�˺�: ");
	strcpy(id, ""); // �������
	strcpy(key, "");  
	scanf("%s",id);
	printf("\t\t����: "); 
	scanf("%s",key);
	FILE *file=fopen("D:\\data_struct_design\\accounts.txt","r");
	if(file==NULL){
		printf("\t\t�޷����ļ�!");
		return;
	}
	char buffer[512];
	fgets(buffer, sizeof(buffer), file); // ���Ա�����
	while(fgets(buffer, sizeof(buffer), file)){
		Account account;
		sscanf(buffer, "%s %s %s %s %s", account.name, account.account, account.password, account.work_id, account.role);
		if(strcmp(account.account,id)==0&&strcmp(account.password,key)==0){
			if(strcmp(account.role,"����Ա")==0){
				printf("\t\t��¼�ɹ�!\n");
				printf("\t\t");system("pause");
				system("cls");
				admin_fun();
				fclose(file); // �ر��ļ�
				return;
			}
			else if(strcmp(account.role,"��ʦ")==0){
				printf("\t\t��¼�ɹ�!\n");
				printf("\t\t");system("pause");
				system("cls");
				teacher_fun();
				fclose(file); // �ر��ļ�
				return;
			}
			else if(strcmp(account.role,"ѧ��")==0){
				printf("\t\t��¼�ɹ�!\n");
				printf("\t\t");system("pause");
				//system("cls");
				student_fun();
				fclose(file); // �ر��ļ�
				return;
			}
		}
		
	}
	printf("\t\t�˺Ż����벻��ȷ!�����ԡ�\n");
	printf("\t\t");
	system("pause");
	
	return;
}
void login_menu(){
	printf("\t\t    \t �γ̹�����Ϣϵͳ  \t    \n");
	printf("\t\t------------------------------\n\n");
	printf("\t\t1. ��¼\n");
	printf("\t\t0. �˳�\n");
	printf("\t\t��ѡ��: ");
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
			printf("\n\t\t\t��лʹ��,�ټ�!\n\n");
			return;
		default:
			printf("\n\t\t\t��ѡ����Ч��ѡ��!\n\n");
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
	log_in_fun();
	return 0;
}