#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int MAX=110;
int course_num=0;   //�γ�����
bool id_status[MAX]; //ѧ��id�Ƿ�ע��
const int admin_key=112234;
typedef struct Student{
	int student_id;
	char student_name[20];
	char student_tel[20];
	struct Student* next; //ָ����һ��ѧ��
	struct Student* same_class_student; //ָ��ͬ��ѧ������һ��  
	struct Stu_self_course* stu_course;//ѧ����ѡ�Ŀγ�
}Student;
typedef struct Course{
	char course_name[20];
	int course_id;          //�γ̺�
	int course_credit;      //ѧ��
	int course_capacity;    //����������
	int course_selected;    //��ǰѡ������
	int course_remain;      //ʣ������
	bool status;            //�γ�״̬--�Ƿ�ɾ��,Ĭ��Ϊfalse
	char course_teacher[20];
	char course_time[20];
}Course;
typedef struct Stu_self_course{  //ѧ��ѡ��Ŀγ���Ϣ
	char student_name[20];
	char course_name[20];
	int course_id;          //�γ̺�
	int course_credit;      //ѧ��
	char course_teacher[20];
	int teacher_id;
	int score;              //ѧ���γ̳ɼ�
	bool status;            //�γ�״̬--�Ƿ�ɾ��,Ĭ��Ϊfalse
	struct Stu_self_course* next;    //ָ����һ���γ�
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
Student* studentList=NULL;      //ѧ��ϵͳ��ѧ������
Student* student_now=NULL;      //����ʹ��ϵͳ��ѧ��
Teacher* teacher_now=NULL;      //����ʹ��ϵͳ����ʦ
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
	printf("\t\t**\t �γ̹�����Ϣϵͳ  \t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  ��ѡ���û����� *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [1].����Ա  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [2].��ʦ  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [3].ѧ��  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t*  [4].�˳�  *\t**\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t******************************************\n");
	
	printf("\n\t\t**\t ���������ѡ���Ӧ���� : "); 
}
void showMenu_teacher()
{
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t ѧ��ѡ��ϵͳ-��ʦ  \t**\n");
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
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t ѧ��ѡ��ϵͳ-����Ա  \t**\n");
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
	
	printf("\t\t******************************************\n");
	printf("\t\t**\t                        \t**\n");
	printf("\t\t**\t ѧ��ѡ��ϵͳ-ѧ��  \t**\n");
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

// ������ʦ���
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

// ������ʦ��㣬���ҵ��򷵻ظý�㣬���򷵻�NULL
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

//�����������ʦ����Ϊ�ؼ��ֵĶ�����
Teacher* inorder_Teacher_Node(Teacher* root){
	if(root!=NULL){
		inorder_Teacher_Node(root->left);
		Course* temp=root->course;
		printf("\t\t�γ�����:%s\t�γ̺�:%d\t",temp->course_name,temp->course_id);
		printf("\t\t��ʦ:%s\t����:%d\n",root->teacher_name,root->teacher_id);
		inorder_Teacher_Node(root->right);
	}
	return root;
}
//չʾѡ�ν���(�������һ��)
Teacher* show_course_info(Teacher* root){
	
	printf("\t\t��ǰ�γ�����Ϊ:%d\n",course_num );
	if(root!=NULL){
		inorder_Teacher_Node(root->left);
		Course* temp=root->course;
		printf("\n\t\t�γ�����:%s\t�γ̺�:%d\t�γ�ѧ��:%d\t�γ�����:%d\t�γ�ʣ������:%d\n",temp->course_name,temp->course_id,temp->course_credit,temp->course_capacity,temp->course_remain);
		printf("\t\t�ο���ʦ:%s\t��ʦ����:%d\t�γ��Ͽ�ʱ��:%s\n",temp->course_teacher,root->teacher_id,temp->course_time);
		show_course_info(root->right);
	}
	return root;
}
//ɾ����ʦ���
Teacher* delete_Teacher_Node(Teacher* root,int teacher_id){
	if(root==NULL){
		return root;
	}
	if(teacher_id < root->teacher_id){
		root->left=delete_Teacher_Node(root->left,teacher_id);
	}else if(teacher_id > root->teacher_id){
		root->right=delete_Teacher_Node(root->right,teacher_id);
	}else{
		// ��ǰ�ڵ�û���ӽڵ��ֻ��һ���ӽڵ�
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
			// �ҵ�����������С�ڵ㣨�����ߣ�
			while(find_node->left!=NULL){
				find_node=find_node->left;
			}
			// �ü����ߵ�ֵ���Ҫɾ���Ľڵ�
			root->teacher_id=find_node->teacher_id;
			strcpy(root->teacher_name,find_node->teacher_name);
			root->right=delete_Teacher_Node(root->right,find_node->teacher_id);
		}
	}
	return root;
}
void admin_add_course(){
//	system("cls");
	printf("\t\t��������Ҫ��ӵĿγ���Ϣ\n");
	printf("\n\t\t�γ���: ");    char course_name[20];      scanf("%s",course_name);
	printf("\t\t�γ̺�: ");    int course_id;             scanf("%d",&course_id);
	printf("\t\tѧ��: ");      int course_credit;         scanf("%d",&course_credit);
	printf("\n\t\t������: ");    int course_capacity;       scanf("%d",&course_capacity);
	printf("\t\t�ο���ʦ: ");  char course_teacher[20];   scanf("%s",course_teacher);
	printf("\t\t��ʦ����: ");  int teacher_id;            scanf("%d",&teacher_id);
	printf("\n\t\t�Ͽ�ʱ��:");   char course_time[20];      scanf("%s",course_time);
	Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id);
	Course* new_course=createNewCourse(course_name,course_id,course_credit,course_capacity,course_teacher,course_time);
	new_teacher->course=new_course;
	course_num++;
	root=insert_Teacher_Node(root,new_teacher); //������ʦ���
	printf("\n\t\t�γ�%s-%d��Ϣ¼��ɹ�!\n",course_name,course_id );
}
void admin_delete_course(){
	if(course_num==0){
		printf("\t\t��ǰû�п���γ�!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("��ǰ����γ̵���ʦ��:\n");
	inorder_Teacher_Node(root);
	printf("������Ҫɾ���γ̵���ʦ����:");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* find_teacher=search_Teacher_Node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\tδ�ҵ�����ʦ,����������\n");
		printf("\t\t");system("pause");
		return;
	}
	else{
		printf("\t\t����ʦ����Ŀγ�Ϊ:%s\t",find_teacher->course->course_name);
		printf("\t\tѧ������Ϊ:%d\n",find_teacher->course->course_selected);
		printf("\t\t�Ƿ�ɾ���ÿγ�?(y/n)");
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
			printf("\t\tɾ���ɹ�!\n");
			printf("\t\t");system("pause");
		}
	}
}
void admin_create_course(){
//	system("cls");
	printf("\t\t������Ҫ�����Ŀγ�����:");
	int course_num_now;
	scanf("%d",&course_num_now);
	while(course_num_now--){
		printf("\t\t������γ���Ϣ\n");
		printf("\n\t\t�γ���: ");    char course_name[20];      scanf("%s",course_name);    fflush(stdin);
		printf("\t\t�γ̺�: ");    int course_id;             scanf("%d",&course_id);       fflush(stdin);
		printf("\t\tѧ��: ");      int course_credit;         scanf("%d",&course_credit);   fflush(stdin);
		printf("\n\t\t������: ");    int course_capacity;       scanf("%d",&course_capacity);fflush(stdin);
		printf("\t\t�ο���ʦ: ");  char course_teacher[20];   scanf("%s",course_teacher);   fflush(stdin);
		printf("\t\t��ʦ����: ");  int teacher_id;            scanf("%d",&teacher_id);      fflush(stdin);
		printf("\n\t\t�Ͽ�ʱ��:");   char course_time[20];      scanf("%s",course_time);    fflush(stdin);
		Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id);
		Course* new_course=createNewCourse(course_name,course_id,course_credit,course_capacity,course_teacher,course_time);
		new_teacher->course=new_course;
		course_num++;
		//����
		printf("\n\t\t test--course_num=%d\n",course_num);
		root=insert_Teacher_Node(root,new_teacher); //������ʦ���
		printf("\n\t\t�γ�%s-%d��Ϣ¼��ɹ�!\n",course_name,course_id );
		//����
		printf("\t\tyou add a course\n");
		printf("\t\t course_name:%s\tcourse_id:%d\tcourse_credit:%d\tcourse_capacity:%d\tcourse_teacher:%s\tteacher_id:%d\tcourse_time:%s\n",course_name,course_id,course_credit,course_capacity,course_teacher,teacher_id,course_time);
		if(course_num_now!=0){
			system("cls");
			printf("\n\t\t���贴��%d�ſγ�\n\n",course_num_now );
			
		}
		else {
			printf("\n\t\t�γ�¼�����!");
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
//	system("cls");
	if(course_num==0){
		printf("\t\t��ǰ��δ�����κογ�!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t��ǰ����Ŀγ���:\n");
	inorder_Teacher_Node(root);
	printf("\t\t������Ҫ��ѯ�γ̵���ʦ����\n");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher *find_teacher=search_Teacher_Node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\tδ�ҵ�����ʦ,����������\n");
		printf("\t\t");system("pause");
		return;
	}
	else{
		printf("\t\t����ʦ����Ŀγ�Ϊ:%s\t",find_teacher->course->course_name);
		printf("\t\tѧ������Ϊ%d:\n",find_teacher->course->course_selected);
		printf("\t\t");system("pause");
	}
}
void admin_output_all_courses(){
//	system("cls");
	if(course_num==0){
		printf("\t\t��ǰ��δ�����κογ�!\n");
		printf("\t\t");system("pause");
		return;
	}
	printf("\t\t��ǰ����Ŀγ���:\n");
	inorder_Teacher_Node(root);
	printf("\t\t");system("pause");
}

void teacher_course_info(){
//	system("cls");
	printf("\t\t����ǰ����Ŀγ�Ϊ:\n");
	printf("\t\t�γ�����:%s\t�γ̺�:%d\t",teacher_now->course->course_name,teacher_now->course->course_id);
	printf("\t\t������Ϊ%d\t",teacher_now->course->course_capacity);
	printf("\t\t��ǰѡ������:%d\t",teacher_now->course->course_selected);
	printf("\t\t");system("pause");
}
void teacher_student_in_class(){
//	system("cls");
	printf("\t\t�����ڰ༶���ѧ��Ϊ:\n");
	PrintStudentList(teacher_now->student_list);
	printf("\t\t");system("pause");
}
void teacher_input_student_course_score(){
	//system("cls");
	Student* temp=teacher_now->student_list;
	while(temp!=NULL){
		printf("\t\t������ѧ��%s�ĳɼ�: ",temp->student_name);
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
	printf("\t\t�����ڰ༶���ѧ��Ϊ:\n");
	PrintStudentList(teacher_now->student_list);
	printf("\t\t������Ҫ�޸ĳɼ���ѧ��ѧ��:");
	int student_id;scanf("%d",&student_id);
	Student* find_student=FindStudent(teacher_now->student_list,student_id);
	if(find_student==NULL){
		printf("\t\tδ�ҵ���ѧ��,����������\n");
		printf("\t\t");system("pause");
		return;
	}
	else{
		printf("\t\t�������޸ĺ�ѧ��%s�ĳɼ�: ",find_student->student_name);
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
	printf("\t\t�ɼ��ֲ�Ϊ:\n");
	printf("\t\t90������:%d\t80-89��:%d\t60-79��:%d\t60������:%d\n",count[0],count[1],count[2],count[3]);
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
//ѧ���˿�ʱ��ɾ������Ϣ���
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
//�˿ε�ͬʱ,ҲӦ������ʦ�İ༶��ɾ��ѧ����Ϣ
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
//��ӡѧ��ѡ��Ŀγ�
void printStudentCourse(Student* student){
	Stu_self_course* temp=student->stu_course;
	printf("\t\t��ѡ��Ŀγ���:\n");
	while(temp!=NULL){
		printf("\t\t�γ�����:%s\t�γ̺�:%d\t",temp->course_name,temp->course_id);
		printf("\t\t��ʦ:%s\t����:%d\n",temp->course_teacher,temp->teacher_id);
		printf("\t\t�ɼ�:%d\n",temp->score);
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
//��ѧ���������ʦ-�γ���
void addStudentToCourse(Teacher* teacher,Student* student){
	//����γ���û��ѧ��������ѧ����Ϊѧ�������ͷ�ڵ�
	if(teacher->student_list==NULL){
		teacher->student_list=student;
		return;
	}else{  // ���򣬱�����ѧ������ĩβ�������ѧ��
		Student* temp=teacher->student_list;
		while(temp->same_class_student!=NULL){
			temp=temp->same_class_student;
		}
		temp->same_class_student=student;
	}
}

//���ѧ������
void PrintStudentList(Student* StudentList){
	Student* temp=StudentList;
	while(temp!=NULL){
		printf("\t\tѧ������:%s\tѧ��:%d\n",temp->student_name,temp->student_id);
		temp=temp->next;
	}
	printf("\t\t");system("pause");
}
//����ѧ��id����ѧ��
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
	printf("\t\t��ǰ��ѡ�γ���:\n");
	show_course_info(root);
	printf("\t\t");system("pause");
}
void student_select_course(){
	//system("cls");
	printf("\t\t��������Ҫѡ��Ŀγ̶�Ӧ����ʦ����:");
	int teacher_id;scanf("%d",&teacher_id);
	Teacher* find_teacher=search_Teacher_Node(root,teacher_id);
	if(find_teacher==NULL){
		printf("\t\tδ�ҵ�����ʦ,����������\n");
		printf("\t\t");system("pause");
		return; }
	else{
		printf("\t\t����ʦ����Ŀγ�Ϊ:%s\t",find_teacher->course->course_name);
		printf("\t\t������Ϊ%d\t",find_teacher->course->course_capacity);
		printf("\t\tʣ������Ϊ%d\n",find_teacher->course->course_remain);
		if(find_teacher->course->course_remain<=0){
			printf("\t\t�ÿγ�����,��ѡ�������γ�!\n");
		}else{
			find_teacher->course->course_remain--;
			find_teacher->course->course_selected++;
			addStudentToCourse(find_teacher,student_now);
			Stu_self_course* new_course=createNewCourse(find_teacher->course->course_name,find_teacher->course->course_id,find_teacher->course->course_credit,find_teacher->course->course_teacher,find_teacher->teacher_id);
			new_course->score=0;
			new_course->next=NULL;
			strcpy(new_course->student_name,student_now->student_name);
			addCourseToStudent(student_now,new_course);
			printf("\t\tѡ�γɹ�!\n");
			
		}
	}
	printf("\t\t");system("pause");
}
void student_cancel_course(){
	printf("��������Ҫȡ���Ŀγ̺�: ");
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
	printf("\t\t�˿γɹ�!\n");
	printf("\t\t");system("pause");
	
	
}
void student_query_score(){
	Stu_self_course* temp=student_now->stu_course;
	printf("\t\t��ѡ��Ŀγ���:\n");
	while(temp!=NULL){
		printf("\t\t�γ�����:%s:\t",temp->course_name);
		if(temp->score==0){
			printf("\t\t�ɼ���δ�Ǽ�!\n");
		}else{
			printf("\t\t�ɼ�:%d\n",temp->score);
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
	
	printf("\t\t���������Ա�˻�����\n\t\t");
	int in_key;scanf("%d",&in_key);
	// ������뻺����
	while ((getchar()) != '\n');
	if(in_key==admin_key){
		
		printf("\t\t��½�ɹ�!\n");
		printf("\t\t");system("pause");
		
	}else{
		printf("\t\t�������,����������!\n");
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
			printf("\t\t�����˳�����Աϵͳ\n");
			return ;//�˳�ϵͳ
		default:
			printf("\t\t����ֵ��Ч,����������\n~");
			system("pause");
			continue;
		}
		
	}
	
	menu_fun();
}
void teacher_fun(){
	//system("cls");
	if(course_num==0){
		printf("\n\n\n\t\t��ǰ�γ�����Ϊ0,ϵͳ��δ�Ǽǣ��޷����в���\n\t\t�����Ա�ȴ����γ�!\n");
		return;
	}else{
		printf("\t\t���������Ĺ���:");
		int teacher_id;scanf("%d",&teacher_id);
		teacher_now=search_Teacher_Node(root,teacher_id);
		if(teacher_now==NULL){
			printf("\t\t����Ա��δ������Ŀγ�!����ϵ����Ա\n");
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
				printf("\t\t�����˳���ʦϵͳ\n");
				return ;//�˳�ϵͳ
			default:
				printf("\t\t����ֵ��Ч,����������\n~");
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
		printf("\n\n\n\t\t��ǰ�γ�����Ϊ0,ϵͳ��δ�Ǽǣ��޷����в���\n\t\t�����Ա�ȴ����γ�!\n");
		return;
	}else{
		printf("\t\t����������ѧ��:");
		int student_id;scanf("%d",&student_id) ;
		
		if(id_status[student_id]==false){
			printf("\t\t����δע��,��������Ϣ֮�����µ���\n");
			printf("\t\t��������������:");
			char student_name[20];scanf("%s",student_name);
			printf("\t\t���������ĵ绰:");char student_tel[20];scanf("%s",student_tel); 
			appendStudnet(&studentList,createNewStudent(student_id,student_name,student_tel));
			id_status[student_id]=true;  
			printf("\t\tע��ɹ�!\n");
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
				printf("\t\t�����˳�ѧ��ϵͳ\n");
				return ;//�˳�ϵͳ
			default:
				printf("\t\t����ֵ��Ч,����������\n~");
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
		
		system("cls");	//��տ���̨�����е��������ݡ� 
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
			printf("\t\t�����˳�ѧ������ϵͳ\n");
			system("pause");
			return ;
		default:
			printf("\t\t����ֵ��Ч,����������\n~");
			system("pause");
			continue;
		}
		system("pause");
		// ����ͣ�����ִ�У��ȴ��û���������������ִ��
		
	}
	system("pause");
}

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	menu_fun();
	return 0;
}
