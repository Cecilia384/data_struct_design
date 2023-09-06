#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_ACCOUNT_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_NAME_LEN 50
#define MAX_WORKID_LEN 20
const int MAX=110;
int course_num=0;   //�γ�����
char id[MAX_ACCOUNT_LEN];//�û��˺�
char key[MAX_PASSWORD_LEN];//��¼����

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
	int course_id;     //�γ̺�
	char course_teacher[20];//�ο���ʦ
	int teacher_id;    //�ο���ʦ����
	int score;              //ѧ���γ̳ɼ�
	int status;            //�γ�״̬--�Ƿ�ɾ��,Ĭ��Ϊfalse
	struct Stu_self_course* next;    //ָ����һ���γ�
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
	int course_id;          //�γ̺�
	int course_credit;      //ѧ��
	int course_capacity;    //����������
	int course_selected;    //��ǰѡ������
	int course_remain;      //ʣ������
	char course_time[20];   //�Ͽ�ʱ��
	char course_place[20];  //�Ͽεص�
	int status;            //�γ�״̬--�Ƿ�ɾ��,Ĭ��Ϊfalse
	class_stu* class_stu_list;   //ָ��༶ѧ����ָ��
	Teacher* left;
	Teacher* right;
}Teacher;
Teacher* root=NULL;
Student* studentList=NULL;      //ѧ��ϵͳ��ѧ������ 
Student* student_now=NULL;      //����ʹ��ϵͳ��ѧ��
Teacher* teacher_now=NULL;      //����ʹ��ϵͳ����ʦ
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
// ������ʦ���
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
		if(root->status==1){
			printf("\t\t�γ�:%s\t�γ̺�:%d\t�ο���ʦ:%s\t����:%d\n",root->course_name,root->course_id,root->teacher_name,root->teacher_id);
		}
		inorder_Teacher_Node(root->right);
	}
	return root;
}
bool delete_node(Teacher *&p){
	Teacher *q,*s;
	if(p->left==NULL&&p->right==NULL){ //����������Ϊ��
		p=NULL;
	}else if(p->left==NULL){ //������Ϊ��
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
			printf("\t�γ�:%s\t�γ̺�:%d\tѧ��:%d\tʣ������:%d\t�ο���ʦ:%s\t����:%d\tʱ��:%s\t�ص�:%s\n",root->course_name,root->course_id,root->course_credit,root->course_remain,root->teacher_name,root->teacher_id,root->course_time,root->course_place);
		}
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
	printf("\t\t������Ҫ�����Ŀγ�����:");
	int course_num_now;
	scanf("%d",&course_num_now);
	while(course_num_now--){
		printf("\t\t������γ���Ϣ\n");
		printf("\n\t\t�γ���: ");    char course_name[20];      scanf("%s",course_name);   
		printf("\t\t�γ̺�: ");    int course_id;             scanf("%d",&course_id);       
		printf("\t\tѧ��: ");      int course_credit;         scanf("%d",&course_credit);    
		printf("\n\t\t������: ");    int course_capacity;       scanf("%d",&course_capacity); 
		printf("\t\t�ο���ʦ: ");  char course_teacher[20];   scanf("%s",course_teacher);  
		printf("\t\t��ʦ����: ");  int teacher_id;            scanf("%d",&teacher_id);       
		printf("\n\t\t�Ͽ�ʱ��:");   char course_time[20];      scanf("%s",course_time);   
		printf("\t\t�Ͽεص�:");   char course_place[20];     scanf("%s",course_place);  
		Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id,course_name,course_id,course_credit,course_capacity,course_time,course_place,1); 
		course_num++;
		root=insert_teacher_node(root,new_teacher);
		FILE* file =  fopen("D:\\data_struct_design\\course_info.txt","a");
		if(file==NULL){
			printf("�޷����ļ�!");
			return;
		}
		fprintf(file, "%s %d %d %d %s %d %s %s\n",course_name,course_id,course_credit,course_capacity,course_teacher,teacher_id,course_time,course_place);
		printf("\n\t\t�γ�%s-%d��Ϣ¼��ɹ�!\n",course_name,course_id );
		printf("\t\t");system("pause");
		if(course_num_now!=0){
			system("cls");
			printf("\n\t\t���贴��%d�ſγ�\n\n",course_num_now );
		}else{
			printf("\n\t\t�γ̴����ɹ�!\n\n");
			printf("\t\t");system("pause");system("cls");return;
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
	printf("\n\t\t�Ͽ�ʱ��:");   char course_time[30];      scanf("%s",course_time);     
	printf("\t\t�Ͽεص�:");   char course_place[20];     scanf("%s",course_place);
	Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id,course_name,course_id,course_credit,course_capacity,course_time,course_place,1); 
	root=insert_teacher_node(root,new_teacher);
	course_num++;
	FILE* file =  fopen("D:\\data_struct_design\\course_info.txt","a");
	if(file==NULL){
		printf("�޷����ļ�!");
		return;
	}
	fprintf(file, "%s %d %d %d %s %d %s %s\n",course_name,course_id,course_credit,course_capacity,course_teacher,teacher_id,course_time,course_place);
	printf("\n\t\t�γ�%s-%d��Ϣ¼��ɹ�!\n",course_name,course_id );
	printf("\t\t");system("pause");
}
void admin_delete_course(){
	if(course_num==0){
		printf("\t\t��ǰ��δ�����κογ�!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t��ǰ����Ŀγ���:\n");
	inorder_Teacher_Node(root);
	printf("\t\t������Ҫɾ���γ̵���ʦ����:");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* find_teacher=search_teacher_node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\tδ�ҵ�����ʦ�Ŀγ�!\n");
		printf("\t\t");system("pause");
		return;
	}else{
		printf("\t\t����ʦ����Ŀγ�Ϊ:%s\t",find_teacher->course_name);
		printf("\t\tѧ������Ϊ:%d\n",find_teacher->course_selected);
		printf("\t\t�Ƿ�ɾ���ÿγ�?(y/n)");
		char choice;scanf("%s",&choice);
		if(choice=='y'||choice=='Y'){
			find_teacher->status=0;
			course_num--;
			int del_course_id=find_teacher->course_id;
			class_stu* temp=find_teacher->class_stu_list;
			//ɾ��ѧ���б����ѡ����Ϣ
			while(temp!=NULL){
				Student* student=search_student_node(studentList,temp->student_id);
				deleteCourse(student,del_course_id);
				temp=temp->next;
			}
			delete_Teacher_Node(root,teacher_id);
			printf("\t\tɾ���ɹ�!\n");
			printf("\t\t");system("pause");
		}
	}
}
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
	printf("t\t\t\t\t�γ��б�:\n");
	printf("\t\t����������������������������������������������������������������������������������������������������������������������������\n");
	inorder_Teacher_Node(root);
	printf("\t\t������Ҫ��ѯ�γ̵���ʦ����: ");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* teacher=search_teacher_node(root,teacher_id);
	if(teacher==NULL){
		printf("\t\tδ�ҵ�����ʦ�Ŀγ�!\n");
		printf("\t\t");system("pause");
		return;
	}else{
		printf("\t\t����ʦ����Ŀγ�Ϊ:%s\t",teacher->course_name);
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
	printf("\t\t\t\t\t�γ��б�\n");
	printf("\t\t����������������������������������������������������������������������������������������������������������������������������\n");
	show_info_course(root);
	printf("\t\t");system("pause");
}
void admin_read_file_course(){
	FILE* file =  fopen("D:\\data_struct_design\\course_info.txt","r");
	if(file==NULL){
		printf("�޷����ļ�!");
		return;
	}
	char buffer[512];
	fgets(buffer, sizeof(buffer), file); // ���Ա�����
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
			printf("\t\t�����˳�����Աϵͳ\n");
			printf("\t\t");system("pause");
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
		printf("\t\tѧ������:%s\tѧ��:%d\n",temp->student_name,temp->student_id);
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
void teacher_course_info(){
	printf("\t\t����ǰ����Ŀγ�Ϊ:\n");
	printf("\t\t�γ�����:%s\t�γ̺�:%d",teacher_now->course_name,teacher_now->course_id);
	printf("\t������Ϊ%d",teacher_now->course_capacity);
	printf("\t��ǰѡ������:%d",teacher_now->course_selected);
	printf("\t�ص�:%s\tʱ��:%s\n",teacher_now->course_place,teacher_now->course_time);
	printf("\t\t");system("pause");
}
void teacher_student_in_class(){
	class_stu* temp=teacher_now->class_stu_list;
	if(temp==NULL){
		printf("\t\t��ǰ�γ�����ѡ��ѧ��!\n");
		printf("\t\t");system("pause");return;
	}
	printf("\t\t�����ڰ༶���ѧ��Ϊ:\n");
	Print_Class_StudentList(teacher_now->class_stu_list);
	//printf("\t\t");system("pause");
}

//��ʦ����ѧ���γ̳ɼ�(bugӦ���޸�����)
void teacher_input_student_course_score(){
	class_stu* temp=teacher_now->class_stu_list;
	if(temp==NULL){
		printf("\t\t��ǰ�γ�����ѡ��ѧ��!\n");
		printf("\t\t");system("pause");return;
	}
	while(temp!=NULL){
		printf("\t\t������ѧ��%s�ĳɼ�: ",temp->student_name);
		int score;scanf("%d",&score);
		temp->student_score=score;
		Student* student=search_student_node(studentList,temp->student_id);
		Stu_self_course* temp_course=student->stu_course;	//����ѧ���γ��б�����ĳɼ�
		while(temp_course!=NULL){
			if(temp_course->course_id==teacher_now->course_id){
				temp_course->score=score;
				break;
			}
			temp_course=temp_course->next;
		}
		temp=temp->next;
	}
	

	
	printf("\t\t�ɼ�¼��ɹ�!\n");
	printf("\t\t");system("pause");
	
}
void PrintStudentList(class_stu* StudentList){
	Student* temp=studentList;
	while(temp!=NULL){
		printf("\t\tѧ������:%s\tѧ��:%d\n",temp->student_name,temp->student_id);
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
void teacher_change_student_course_score(){
	class_stu* temp2=teacher_now->class_stu_list;
	if(temp2==NULL){
		printf("\t\t��ǰ�γ�����ѡ��ѧ��!\n");
		printf("\t\t");system("pause");return;
	}
	printf("\t\t�����ڰ༶���ѧ��Ϊ:\n");
	PrintStudentList(teacher_now->class_stu_list);

	printf("\t\t������Ҫ�޸ĳɼ���ѧ��ѧ��: ");
	int student_id;scanf("%d",&student_id);
	class_stu* temp=teacher_now->class_stu_list;
	while(temp!=NULL){
		if(temp->student_id==student_id){
			printf("\t\t������ѧ��%s�ĳɼ�: ",temp->student_name);
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
			printf("\t\t�ɼ��޸ĳɹ�!\n");
			printf("\t\t");system("pause");
			return;
		}
		temp=temp->next;
	}
	printf("\t\tδ�ҵ���ѧ��!\n");
	printf("\t\t");system("pause");
	return;
}
void teacher_count_student_score(){
	//+,90,80,60,-
	class_stu* temp1=teacher_now->class_stu_list;
	if(temp1==NULL){
		printf("\t\t��ǰ�γ�����ѡ��ѧ��!\n");
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
	printf("\t\t�ɼ��ֲ�����:\n");
	printf("\t\t90������:%d\t80-89��:%d\t60-79��:%d\t60������:%d\n",count[0],count[1],count[2],count[3]);
	printf("\t\t");system("pause");
}
void teacher_fun(){
	//system("cls");
	if(course_num==0){
		printf("\n\n\n\t\t��ǰ�γ�����Ϊ0,ϵͳ��δ�Ǽǣ��޷����в���\n\t\t�����Ա�ȴ����γ�!\n");
		return;
	}else{
		FILE* file =  fopen("D:\\data_struct_design\\accounts.txt","r");
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
			sscanf(buffer, "%s %s %*s %d %*s", teacher_name,teacher_accunt, &teacher_id);
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
				printf("\t\t");system("pause");
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
	printf("\t\t��ǰ��ѡ�γ�����\n");
	printf("\t\t����������������������������������������������������������������������������������������������������������������������������\n");
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
class_stu* createNewClassStudent(int student_id,char student_name[20]){
	class_stu* new_student=(class_stu*)malloc(sizeof(class_stu));
	new_student->student_id=student_id;
	strcpy(new_student->student_name,student_name);
	new_student->next=NULL;
	new_student->student_score=0;
	 
	return new_student;
}
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
			class_stu* new_student_now=createNewClassStudent(student_now->student_id,student_now->student_name);
			addStudentToCourse(find_teacher,new_student_now);
			Stu_self_course* new_course=createNewStu_self_course(student_now->student_name,find_teacher->course_name,find_teacher->teacher_name,0,find_teacher->course_id,find_teacher->teacher_id);
			addCourseToStudent(student_now,new_course);
			printf("\t\tѡ�γɹ�!\n");
		}
	}
}
void student_cancel_course(){
	Stu_self_course* temp1=student_now->stu_course;
	printf("\t\t����ѡ�Ŀγ�Ϊ:\n");
	while(temp1!=NULL){
		if(temp1->status==false){
			printf("\t\t�γ�:%s\t�γ̺�:%d\t",temp1->course_name, temp1->course_id);
			printf("��ʦ:%s\n",temp1->course_teacher);
		}
		temp1=temp1->next;
	}
	printf("\t\t��������Ҫȡ���Ŀγ̺�: ");
	int course_ID;
	scanf("%d", &course_ID);
	Stu_self_course*temp=student_now->stu_course;
	while(temp != NULL) {
		if(temp->course_id == course_ID) {
			deleteCourse(student_now, course_ID);  // ɾ���γ�
			break;
		}
		temp = temp->next;
	}
	if(temp==NULL){
		printf("\t\t�Ҳ�����Ӧ�Ŀγ̺�,�޷�ȡ��ѡ�Ρ�\n");
		return;
	}
	Teacher* teacher=search_teacher_node(root,temp->teacher_id);
	if(teacher==NULL){
		printf("�޷��ҵ��ÿγ̵Ľ�ʦ��Ϣ!\n");
		printf("\t\t");system("pause");
	}else{
		teacher->course_remain++;
		teacher->course_selected--;
		deleteStudentFromTeacher(teacher, student_now->student_id);
		printf("\t\t�˿γɹ�!\n");
		printf("\t\t");system("pause");
	}
	
}
void student_query_score(){
	Stu_self_course* temp=student_now->stu_course;
	printf("\t\t��ѡ��Ŀγ���:\n");
	if(temp==NULL){
		printf("\t\t����δѡ���κογ�!\n");
		printf("\t\t");system("pause");
		return;
	}
	while(temp!=NULL){
		printf("\t\t�γ�����:%s:\t",temp->course_name);
		if(temp->score==0){
			printf("\t\t�ɼ���δ�Ǽ�!\n");
		}else{
			printf("\t\t�ɼ�:%d\n",temp->score);
		}
		
		temp=temp->next;
	}
	//printf("\t\t");system("pause");
}
void student_output_all_courses(){
	Stu_self_course* temp=student_now->stu_course;
	if(temp==NULL){
		printf("\t\t��δѡ���κογ�!\n");
		return;
	}
	printf("\t\t����ѡ�Ŀγ�Ϊ:\n");
	while(temp!=NULL){
		if(temp->status==1){
			printf("\t\t�γ�:%s\t",temp->course_name);
			printf("��ʦ:%s",temp->course_teacher);
			if(temp->score==0){
				printf("\t�ɼ�:��δ�Ǽǣ�\n");
			}else{
				printf("\t�ɼ�:%d\n",temp->score);
			}
		}
		temp=temp->next;
	}
	//printf("\t\t");system("pause");
}
void student_fun(){
	if(course_num==0){
		printf("\n\n\n\t\t��ǰ�γ�����Ϊ0,ϵͳ��δ�Ǽǣ��޷����в���\n\t\t�����Ա�ȴ����γ�!\n");
		printf("\t\t");system("pause");
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
				printf("\t\t�����˳�ѧ��ϵͳ\n");
				printf("\t\t");system("pause");
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

void admin_menu(){
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
void teacher_menu(){
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
void student_menu(){
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
			printf("\t\t��¼�ɹ�!\n");
			printf("\t\t");system("pause");
			system("cls");
			if(strcmp(account.role,"����Ա")==0){
				admin_fun();
				fclose(file); // �ر��ļ�
				return;
			}
			else if(strcmp(account.role,"��ʦ")==0){
				teacher_fun();
				fclose(file); // �ر��ļ�
				return;
			}
			else if(strcmp(account.role,"ѧ��")==0){
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
	admin_read_file_course();//��ȡ�ļ���Ŀγ���Ϣ
	log_in_fun();
	return 0;
}