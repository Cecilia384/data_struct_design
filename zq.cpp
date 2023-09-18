#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<malloc.h>
#define MAX_COURSES 100
#define MAX_STUDENTS 100
#define MAX_LENGTH 50
int course_num=0;
void control_panel();
typedef struct Course {
	int course_id;
	char course_name[20];
	int course_credit;
	char course_time[20];
	char course_place[20];
	char course_teacher[20];
	struct Teacher* teacher;
	int class_num;
	int class_remain_num;
	int course_grade[50];
} Course;

typedef struct Student{
	int student_num;
	char student_name[20];
	char student_tel[20];
	int enrolled_courses[MAX_COURSES];
	int num_enrolled_courses;
	struct Student* class_next;
	struct selected_course* student_course;
} Student;

typedef struct Teacher {
	int id;
	char name[20];
	Student* students;//�����ڵ�ѧ��
	Teacher* left;
	Teacher* right;
	Course* courses;//�����ڵĿγ�
} Teacher;

typedef struct selected_course {
	int course_id;
	int course_grade;
	char student_name[20];
	char course_name[20];
	char course_teacher[20];
	bool selected_status;
	struct selected_course* next;
} selected_course;

// �û��ṹ��
typedef struct {
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];
	char role[MAX_LENGTH];
} User;

Teacher* teacher_root=NULL;//��ʦ���ڵ�
Student* student_head=NULL;//ѧ������ͷ�ڵ�
Student* now_student=NULL;//��ǰ��¼��ѧ��
Teacher* now_teacher=NULL;//��ǰ��¼�Ľ�ʦ
Course courses[MAX_COURSES];
Teacher teachers[MAX_COURSES];
Student students[MAX_STUDENTS];
//int num_courses = 0;
int num_teachers = 0;
int num_students = 0;

Course* new_course_node(int course_id, char course_name[20], int course_credit, char course_time[20], char course_place[20], Teacher* teacher){
	Course* new_course = (Course*)calloc(1, sizeof(Course));
	new_course->course_id=course_id;
	strcpy(new_course->course_name,course_name);
	new_course->course_credit=course_credit;
	strcpy(new_course->course_time,course_time);
	strcpy(new_course->course_place,course_place);
	new_course->teacher=teacher;
	new_course->class_num=0;
	new_course->class_remain_num=0;
	new_course->course_grade[50]={0};
//	for(int i=0;i<5;i++){
//		new_course->course_grade[i]=0;
//	}
	return new_course;
}
Teacher* new_teacher_node(int id, char name[20]){
	Teacher* new_teacher = (Teacher*)calloc(1, sizeof(Teacher));
	new_teacher->id=id;
	strcpy(new_teacher->name,name);
	new_teacher->students=NULL;
	new_teacher->right=NULL;
	new_teacher->left=NULL;
	new_teacher->courses=NULL;
	return new_teacher;
}
Teacher* new_teacher_insert(Teacher* teacher_root, Teacher* newteacher){
	if(teacher_root==NULL){
		teacher_root=newteacher;
		return teacher_root;
	}
	if(newteacher->id<teacher_root->id){
		teacher_root->left=new_teacher_insert(teacher_root->left,newteacher);
	}
	else{
		teacher_root->right=new_teacher_insert(teacher_root->right,newteacher);
	}
	return teacher_root;
}

void main_menu() {
	printf("��ӭʹ�ÿγ̹�����Ϣϵͳ��\n");
	printf("---------------------------\n");
	printf("��ѡ��������ݣ�\n");
	printf("1. ����Ա\n");
	printf("2. ��ʦ\n");
	printf("3. ѧ��\n");
	printf("4. �˳�\n");
	printf("---------------------------\n");
}

void administer_menu() {
	printf("[����Ա] ��ѡ�������\n");
	printf("1. ���������רҵ�γ���Ϣ\n");
	printf("2. ɾ�������רҵ�γ���Ϣ\n");
	printf("3. ͳ�Ƽ����רҵ����γ̵�����\n");
	printf("4. ��ѯÿ�ſγ��޿�����\n");
	printf("5. ��������רҵ�Ŀγ���Ϣ\n");
	printf("6. �˳�\n");
}

void teacher_menu() {
	printf("[��ʦ] ��ѡ�������\n");
	printf("1. �鿴�����ڵĿγ���Ϣ\n");
	printf("2. ��ѯ�����ڵ�ѧ������Ϣ\n");
	printf("3. ����γ̳ɼ�\n");
	printf("4. �޸Ŀγ̳ɼ�\n");
	printf("5. ͳ�Ƴɼ���Ϣ(ͳ��90�����ϡ�80~90�֡�60~80�֡�60�����µ�����)\n");
	printf("6. �˳�\n");
}

void student_menu() {
	printf("[ѧ��] ��ѡ�������\n");
	printf("1. ��ѯ�γ���Ϣ\n");
	printf("2. �����γ�\n");
	printf("3. ȡ���γ̱���\n");
	printf("4. ��ѯ�ɼ�\n");
	printf("5. ������пγ���Ϣ\n");
	printf("6. �˳�\n");
}
//����Ա���ܼ���


// �����γ���Ϣ
Course* createNewCourse(char course_name[20],int course_id,char course_teacher[20],int course_credit,char course_time[20]){
	Course* new_course = (Course*)calloc(1, sizeof(Course));
	strcpy(new_course->course_name,course_name);
	new_course->course_id=course_id;
	new_course->course_credit=course_credit;
	strcpy(new_course->course_teacher,course_teacher);
	strcpy(new_course->course_time,course_time);
	return new_course;
}
void establish_course() {
	Course *course;
	Course* new_course = (Course*)calloc(1, sizeof(Course));
	int course_id;
	char course_name[20];
	int course_credit;
	char course_time[20];
	char course_place[20];
	char course_teacher[20];
	Teacher* teacher;
	printf("�γ̺ţ�");
	scanf("%d", &course_id);
	printf("�γ�����");
	scanf("%s", course_name);
	printf("�γ�ѧ�֣�");


	scanf("%d", &course_credit);
	char teacher_name[20];
	int teacher_id;


	printf("�������ον�ʦ��������");

	scanf("%s", teacher_name);
	//Teacher* teacher;


	printf("�������ον�ʦ�Ĺ��ţ�");
	scanf("%d", &teacher_id);
	Teacher* new_teacher = new_teacher_node(teacher_id, teacher_name);
	new_course = new_course_node(course_id, course_name, course_credit, course_time, course_place, new_teacher);
	new_teacher->courses=new_course;
	teacher_root=new_teacher_insert(teacher_root, new_teacher);
	printf("�ɹ������γ���Ϣ%s-%d��\n", course_name, course_id);
	course_num++;
}

// ɾ���γ���Ϣ
void delete_course_info() {
	int course_id;
	printf("������γ̺�:\n");
	scanf("%d",&course_id);
	int removed_index = -1;
	for (int i = 0; i < course_num; i++) {
		if (courses[i].course_id == course_id) {
			removed_index = i;
			break;
		}
	}
	if (removed_index == -1) {
		printf("δ�ҵ��γ̺�Ϊ %d �Ŀγ���Ϣ��\n", course_id);
		return;
	}
	// ɾ���ÿγ�
	for (int i = removed_index+1; i < course_num; i++) {
		courses[i-1] = courses[i];
	}
	course_num--;
	
	printf("�ɹ�ɾ���γ̺�Ϊ %d �Ŀγ���Ϣ��\n", course_id);
	course_num--;
}
// ͳ�Ƽ��������γ�����
void count_total_courses() {
	int total_courses = course_num;
	printf("���������γ�������%d\n", total_courses);
}
//ÿ�ſ��޿�����
void count_students_in_course() {
	int course_id;
	printf("������γ̺�:\n");
	scanf("%d",&course_id);
	int count = 0;
	for (int i = 0; i < num_students; i++) {
		for (int j = 0; j < students[i].num_enrolled_courses; j++) {
			if (students[i].enrolled_courses[j] == course_id) {
				count++;
				break;
			}
		}
	}
	printf("���ſ��޿�����Ϊ:  %d",count);
	return;
}

//
// ��ѯ�γ̳ɼ�
void search_grade_by_course_id() {
	int course_id;
	printf("������γ̺�:\n");
	scanf("%d",&course_id);
	for (int i = 0; i < course_num; i++) {
		if (courses[i].course_id == course_id) {
			printf("�γ�ID��%d\n", courses[i].course_id);
			printf("�γ����ƣ�%s\n", courses[i].course_name);
			printf("�γ̽�ʦ��%s\n", courses[i].course_teacher);
			printf("�γ�ѧ�֣�%d\n", courses[i].course_credit);
			printf("��ѡ�ÿγ�ѧ�����ɼ���\n");
			selected_course* current_course = students[0].student_course;
			while (current_course != NULL) {
				if (current_course->course_id == course_id) {
					printf("ѧ��������%s\t�ɼ���%d\n", current_course->student_name, current_course->course_grade);
				}
				current_course = current_course->next;
			}
			return;
		}
	}
	printf("δ�ҵ��ÿγ̣�\n");
}

// ����ѧ�Ų�ѯ�γ���Ϣ
void search_courses_by_student_num() {
	int student_num;
	printf("������ѧ��:\n");
	scanf("%d",&student_num);
	Student* current_student = NULL;
	for (int i = 0; i < num_students; i++) {
		if (students[i].student_num == student_num) {
			current_student = &students[i];
			break;
		}
	}
	
	if (current_student == NULL) {
		printf("δ�ҵ���ѧ����\n");
		return;
	}
	
	printf("ѧ��������%s\n", current_student->student_name);
	
	selected_course* current_course = current_student->student_course;
	if (current_course == NULL) {
		printf("��ѧ��δѡ���κογ̣�\n");
		return;
	}
	
	printf("��ѡ�γ���Ϣ��\n");
	while (current_course != NULL) {
		int course_id = current_course->course_id;
		for (int i = 0; i < course_num; i++) {
			if (courses[i].course_id == course_id) {
				printf("�γ�ID��%d\n", courses[i].course_id);
				printf("�γ����ƣ�%s\n", courses[i].course_name);
				printf("�γ̽�ʦ��%s\n", courses[i].course_teacher);
				printf("�γ�ѧ�֣�%d\n", courses[i].course_credit);
				printf("\n");
				break;
			}
		}
		current_course = current_course->next;
	}
}

Course* find_course_by_id(int course_id) {
	for (int i = 0; i < course_num; i++) {
		if (courses[i].course_id == course_id) {
			return &courses[i];
		}
	}
	return NULL; // ����Ҳ�����Ӧ�γ̣�����NULL
}
void search_course_by_id(){
	int course_id;
	printf("������γ̺ţ�\n");
	scanf("%d",&course_id);
	Course* course = find_course_by_id(course_id); // ���ݿγ̺�123��ѯ�γ���Ϣ
	if (course != NULL) {
		// ����γ���Ϣ
		printf("�γ����ƣ�%s\n", course->course_name);
		printf("ѧ�֣�%d\n", course->course_credit);
		// �����γ���Ϣ
	} else {
		printf("δ�ҵ���Ӧ�γ̣�\n");
	}
}

void count_students_by_grade() {
	int course_id;
	printf("������γ̺�:\n");
	scanf("%d",&course_id);
	int count_90_above = 0;
	int count_80_to_90 = 0;
	int count_60_to_80 = 0;
	int count_below_60 = 0;
	// ��������ѧ��
	for (int i = 0; i < num_students; i++) {
		Student* current_student = &students[i];
		
		// ���ѧ���Ƿ�ѡ����ָ���γ�
		for (int j = 0; j < current_student->num_enrolled_courses; j++) {
			int enrolled_course_id = current_student->enrolled_courses[j];
			if (enrolled_course_id == course_id) {
				// ��ȡ��ѧ���ĳɼ�
				int grade = current_student->student_course->course_grade;
				
				// ���ݳɼ���Χ�����жϺ�ͳ��
				if (grade >= 90) {
					count_90_above++;
				} else if (grade >= 80 && grade < 90) {
					count_80_to_90++;
				} else if (grade >= 60 && grade < 80) {
					count_60_to_80++;
				} else {
					count_below_60++;
				}
			}
		}
	}
	// ��ӡͳ�ƽ��
	printf("90�����ϵ�������%d\n", count_90_above);
	printf("80-90�ֵ�������%d\n", count_80_to_90);
	printf("60-80�ֵ�������%d\n", count_60_to_80);
	printf("60�����µ�������%d\n", count_below_60);
}

void input_student_grade() {
	int student_num;
	int course_id;
	printf("������ѧ��ѧ��:\n");
	scanf("%d",&student_num);
	printf("������γ̺�:\n");
	scanf("%d",&course_id);
	bool found_student = false;
	bool found_course = false;
	// ����ѧ������
	for (int i = 0; i < num_students; i++) {
		Student* current_student = &students[i];
		// �ҵ�ƥ��ѧ�ŵ�ѧ��
		if (current_student->student_num == student_num) {
			found_student = true;
			
			// ���ѧ����ѡ�μ�¼
			selected_course* current_course = current_student->student_course;
			while (current_course != NULL) {
				// �ҵ�ƥ��γ�ID��ѡ�μ�¼
				if (current_course->course_id == course_id) {
					found_course = true;
					
					// ��ʾ����γ̳ɼ�
					printf("������ѧ�� %s �Ŀγ̳ɼ���", current_student->student_name);
					int grade;
					scanf("%d", &grade);
					
					// ����ѡ�μ�¼�еĳɼ�
					current_course->course_grade = grade;
					
					printf("�ѳɹ�����ѧ�� %s �Ŀγ̳ɼ���\n", current_student->student_name);
					break;
				}
				
				current_course = current_course->next;
			}
			
			// ���û���ҵ�ƥ���ѡ�μ�¼
			if (!found_course) {
				printf("��ѧ��δѡ�޸��ſγ̡�\n");
			}
			
			break;
		}
	}
	// ���������쳣���
	if (!found_student) {
		printf("ѧ�� %d �����ڡ�\n", student_num);
	}
}

void modify_student_grade() {
	int student_num;
	int course_id;
	printf("������ѧ��ѧ��:\n");
	scanf("%d",&student_num);
	printf("������γ̺�:\n");
	scanf("%d",&course_id);
	bool found_student = false;
	bool found_course = false;
	
	// ����ѧ������
	for (int i = 0; i < num_students; i++) {
		Student* current_student = &students[i];
		
		// �ҵ�ƥ��ѧ�ŵ�ѧ��
		if (current_student->student_num == student_num) {
			found_student = true;
			
			// ���ѧ����ѡ�μ�¼
			selected_course* current_course = current_student->student_course;
			while (current_course != NULL) {
				// �ҵ�ƥ��γ�ID��ѡ�μ�¼
				if (current_course->course_id == course_id) {
					found_course = true;
					
					// ��ʾ�����µĿγ̳ɼ�
					printf("������ѧ�� %s ���¿γ̳ɼ���", current_student->student_name);
					int grade;
					scanf("%d", &grade);
					
					// ����ѡ�μ�¼�еĳɼ�
					current_course->course_grade = grade;
					
					printf("�ѳɹ��޸�ѧ�� %s �Ŀγ̳ɼ���\n", current_student->student_name);
					break;
				}
				current_course = current_course->next;
			}
			// ���û���ҵ�ƥ���ѡ�μ�¼
			if (!found_course) {
				printf("��ѧ��δѡ�޸��ſγ̡�\n");
			}
			
			break;
		}
	}
	
	// ���������쳣���
	if (!found_student) {
		printf("ѧ�� %d �����ڡ�\n", student_num);
	}
}

// ��������������γ̺��������
Teacher* inorder_traversal(Teacher* teacher_root) {
	if (teacher_root != NULL) {
		inorder_traversal(teacher_root->left);
		Course* temp=teacher_root->courses;
		printf("  �γ�����:%s  �γ̺�:%d\t",temp->course_name,temp->course_id);
		printf("  ��ʦ:%s      ����:%d\n",teacher_root->name,teacher_root->id);
		inorder_traversal(teacher_root->right);
	}
	return teacher_root;
}
Teacher* show_course_info(Teacher* root){
	printf("\t\t��ǰ�γ�����Ϊ:%d\n",course_num );
	if(root!=NULL){
		inorder_traversal(root->left);
		Course* temp=root->courses;
		printf("\n\t\t�γ�����:%s\t�γ̺�:%d\t�γ�ѧ��:%d\n",temp->course_name,temp->course_id,temp->course_credit);
		printf("\t\t�ο���ʦ:%s\t��ʦ����:%d\t�γ��Ͽ�ʱ��:%s\n",temp->course_teacher,root->id,temp->course_time);
		show_course_info(root->right);
	}else{
		printf("��ǰ�γ�Ϊ�գ������½��γ�!\n");
	}
	return root;
}
Teacher* createNewTeacher(char teacher_name[20],int teacher_id){
	Teacher* new_teacher = (Teacher*)calloc(1, sizeof(Teacher));
	strcpy(new_teacher->name,teacher_name);
	new_teacher->id=teacher_id;
	new_teacher->courses=NULL;
	new_teacher->students=NULL;
	new_teacher->left=NULL;
	new_teacher->right=NULL;
	return new_teacher;
}
Student* createNewStudent(char student_name[20],int student_num,char student_tel[20]){
    Student* new_student = (Student*)calloc(1, sizeof(Student));
    strcpy(new_student->student_name,student_name);
    new_student->student_num=student_num;
    strcpy(new_student->student_tel,student_tel);
    new_student->num_enrolled_courses=0;
    new_student->class_next=NULL;
    new_student->student_course=NULL;
    return new_student;
}
void appendStudnet(Student** studentList,Student* new_student){
    if(*studentList==NULL){
        *studentList=new_student;
        return;
    }
    Student* current_student=*studentList;
    while(current_student->class_next!=NULL){
        current_student=current_student->class_next;
    }
    current_student->class_next=new_student;
}
Teacher* find_node() {
	Teacher* current = teacher_root;
	if(current==NULL){
		return teacher_root;
	}
	while (current != NULL) {
		if(teacher_root->id==current->id){
			return current;
		}
		else if (teacher_root->id < current->id) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	
}
Teacher* inorder_traversal_teacher(Teacher* teacher_root, int id) {
	if (teacher_root != NULL) {
		inorder_traversal_teacher(teacher_root->left, id);
		if(teacher_root->id==id){
			return teacher_root;}
		Course* temp=teacher_root->courses;
		printf("\t\t�γ�����:%s\t�γ̺�:%d\t",temp->course_name,temp->course_id);
		printf("\t\t��ʦ:%s\t����:%d\n",teacher_root->name,teacher_root->id);
		inorder_traversal_teacher(teacher_root->right, id);
	}
}

// ѧ��ѡ��
void enroll_course(Student* student ) {
	int course_id;
	printf("������ѡ�εĿγ̺�:\n");
	scanf("%d",&course_id);
	if (student->num_enrolled_courses >= MAX_COURSES) {
		printf("%s ѧ��ѡ���Ѵ����ޣ��޷���ѡ��\n", student->student_name);
		return;
	}
	
	Course* selected_course = NULL;
	for (int i = 0; i < course_num; i++) {
		if (courses[i].course_id == course_id) {
			selected_course = &courses[i];
			break;
		}
	}
	
	if (selected_course == NULL) {
		printf("δ�ҵ��γ̺�Ϊ %d �Ŀγ���Ϣ��\n", course_id);
		return;
	}
	
	if (selected_course->class_remain_num <= 0) {
		printf("%s �γ������������޷�ѡ�Σ�\n", selected_course->course_name);
		return;
	}
	
	int enrolled_course_index = student->num_enrolled_courses;
	student->enrolled_courses[enrolled_course_index] = course_id;
	student->num_enrolled_courses++;
	selected_course->class_remain_num--;
	printf("%s ѧ���ɹ�ѡ�� %s �γ̣�\n", student->student_name, selected_course->course_name);
}

// ȡ��ѡ��
void cancel_enrollment(Student* student) {
	int removed_index = -1;
	int course_id;
	for (int i = 0; i < student->num_enrolled_courses; i++) {
		if (student->enrolled_courses[i] == course_id) {
			removed_index = i;
			break;
		}
	}
	
	if (removed_index == -1) {
		printf("%s δѡ�޿γ̺�Ϊ %d �Ŀγ̣�\n", student->student_name, course_id);
		return;
	}
	
	// ����ѧ����ѡ����Ϣ
	for (int i = removed_index+1; i < student->num_enrolled_courses; i++) {
		student->enrolled_courses[i-1] = student->enrolled_courses[i];
	}
	student->num_enrolled_courses--;
	
	// ���¿γ̵�����
	Course* removed_course = NULL;
	for (int i = 0; i < course_num; i++) {
		if (courses[i].course_id == course_id) {
			removed_course = &courses[i];
			break;
		}
	}
	removed_course->class_remain_num++;
	
	printf("%s �ɹ�ȡ��ѡ�޿γ� %s (�γ̺ţ�%d)��\n", student->student_name, removed_course->course_name, course_id);
}
// ��ѯ�ɼ�
void search_grade_by_student_id(int student_id) {
	Student* current_student = now_student;
	while (current_student != NULL) {
		if (current_student->student_num == student_id) {
			printf("ѧ�ţ�%d\n", current_student->student_num);
			printf("������%s\n", current_student->student_name);
			printf("�绰��%s\n", current_student->student_tel);
			printf("��ѡ�γ̼��ɼ���\n");
			selected_course* current_course = current_student->student_course;
			while (current_course != NULL) {
				printf("�γ̣�%s\t�ɼ���%d\n", current_course->course_name, current_course->course_grade);
				if(current_course->next!=NULL)
					current_course = current_course->next;
			}
			return;
		}
		// current_student->class_next = current_student;
	}
	printf("δ�ҵ���ѧ����\n");
}

// ������пγ���Ϣ
void browse_all_courses() {
	printf("���пγ���Ϣ��\n");
	for (int i = 0; i < course_num; i++) {
		printf("�γ�ID��%d\n", courses[i].course_id);
		printf("�γ����ƣ�%s\n", courses[i].course_name);
		printf("�γ̽�ʦ��%s\n", courses[i].course_teacher);
		printf("�γ�ѧ�֣�%d\n", courses[i].course_credit);
		printf("�γ��Ͽ�ʱ�䣺%s\n", courses[i].course_time);
		printf("�γ��Ͽεص㣺%s\n", courses[i].course_place);
		printf("ʣ�����%d\n", courses[i].class_remain_num);
		printf("\n");
	}
}
void display_all_courses(Teacher* teacher_root) {
	if (teacher_root != NULL) {
		display_all_courses(teacher_root->left);
		Course* temp = teacher_root->courses;
		while (temp != NULL) {
			printf("�γ����ƣ�%s\t�γ̺ţ�%d\t��ʦ��%s\t���ţ�%d\n",
				temp->course_name, temp->course_id,
				teacher_root->name, teacher_root->id);
		//	temp = temp->next;
		}
		display_all_courses(teacher_root->right);
	}
}
/*
  int student_login(Student students[]) {
  int student_num;int student_count;
  printf("������ѧ�ţ�");
  scanf("%d", &student_num);
  for (int i = 0; i < student_count; i++) {
  if (student_num == students[i].student_num) {
  return i;
  }
  }
  printf("��¼ʧ�ܣ�����ѧ���Ƿ�������ȷ��\n");
  return -1;
  }*/

void administer_function(){
	bool flag=true;
	while(flag){
		int func_code;
		administer_menu();
		scanf("%d",&func_code);
		switch(func_code){
		case 1:
			establish_course();
			break;
		case 2:
			delete_course_info();
			break;
		case 3:
			count_total_courses();
			break;
		case 4:
			count_students_in_course();
			break;
		case 5:
			show_course_info(teacher_root);
			break;
		case 6:
			flag=false;
			break;
		}}
}

int administer_log_in()
{
	char password[10] = "";
	char arr1[] = "usst100093";
	int i = 1;
	//int j = 0;
	for (i = 1; i <= 3; ++i)
	{
		printf("���������Ա����: \n");
		scanf("%s", password);
		if (strcmp(password,arr1)==0)//ʹ�õȺűȽ��ַ��� ����
		{
			printf("��¼�ɹ�!\n");
			return -1;
			
		}
		else
		{
			printf("�����������������!\n");
		}
	}
	printf("������������,����ϵ���񴦣�\n");
	return 0;
}

void teacher_function(){
	int func_code;
	teacher_menu();
	scanf("%d",&func_code);
	switch(func_code){
	case 1:
		search_course_by_id();
		break;
	case 2:
		search_grade_by_course_id();
		break;
	case 3:
		input_student_grade();
		break;
	case 4:
		modify_student_grade();
		break;
	case 5:
		count_students_by_grade();
		break;
		case 6://�˳������˵�
		printf("�����˳�...\n");
		control_panel();
		break;
		
	}
	
}
void student_function(){
	bool flag=true;
	while(flag){
		int func_code;
		student_menu();
		scanf("%d",&func_code);
		switch(func_code){
			case 1://��ѯ�γ���Ϣ
			search_course_by_id();
			break;
			case 2://�����γ�
			enroll_course(now_student);
			break;
			case 3://ȡ�������γ�
			cancel_enrollment(now_student);
			break;
			case 4://��ѯ�γ̳ɼ�
			search_grade_by_course_id();
			break;
			case 5: //������пγ���Ϣ
			//printf("��ʱ����ִ�е��������");
			//display_all_courses(teacher_root);
			browse_all_courses();
			break;
		case 6:
			flag=false;
			break;
			
		}}
}

// �����û������������ļ��в��Ҷ�Ӧ���û���Ϣ
User* find_user(const char* username, const char* password, int code_id) {
	FILE* file;
	if (code_id == 1) { // ѧ�����
		file = fopen("C:\\Users\\qianq\\Desktop\\ѧ���˺�����.txt", "r");
        printf("������������\n");char username[20];int stu_id;
        scanf("%s",username);
        printf("������ѧ�ţ�\n");scanf("%d",&stu_id);
        printf("������绰���룺\n");char stu_tel[20];scanf("%s",stu_tel);
        Student* new_student=createNewStudent(username,stu_id,stu_tel);
        now_student=new_student;    
        appendStudnet(&student_head,new_student);
         
	} else if (code_id == 2) { // ��ʦ���
		file = fopen("C:\\Users\\qianq\\Desktop\\��ʦ�˺�����.txt", "r");
        printf("������������\n");char teacher_name[20];int teacher_id;
        scanf("%s",teacher_name);
        printf("�����빤�ţ�\n");scanf("%d",&teacher_id);
        now_teacher=createNewTeacher(teacher_name,teacher_id);
      
	} else {
		printf("��Ч����ݴ��룡\n");
		return NULL;
	}
	
	if (file == NULL) {
		printf("�޷����û��ļ���\n");
		return NULL;
	}
	
	User* user = NULL;
	User temp;
	while (fscanf(file, "%s %s", temp.username, temp.password) != EOF) {
		if (strcmp(temp.username, username) == 0 && strcmp(temp.password, password) == 0) {
			user = (User*)malloc(sizeof(User));
			strcpy(user->username, temp.username);
			strcpy(user->password, temp.password);
			break;
		}
	}
	fclose(file);
	return user;
}
void user_log_in(int id_code){
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];
	printf("�û���¼\n");
	printf("�������û�����");
	scanf("%s", username);
	printf("���������룺");
	scanf("%s", password);
	User* user = find_user(username, password,id_code);
	if (user != NULL) {
		printf("��¼�ɹ���\n");
		printf("��ӭ��%s��\n", user->username);
		// printf("��ɫ��%s\n", user->role);
		if (id_code == 1) {
			student_function();
		} else if (id_code == 2) {
			teacher_function();
		}
	} else {
		printf("��¼ʧ�ܣ������û��������룡\n");
	}
	
	free(user);
	exit(0);
}
void control_panel(){
	main_menu();
	int role;
	scanf("%d", &role);
	switch (role) {
		case 1:{
		//	administer_log_in();
			int flag=administer_log_in();
			if(flag==-1)
				administer_function();
			else
				return;
			break;
		}
		
	case 2:
		user_log_in(2);
		break;
	case 3:{
		user_log_in(1);//ѧ�����
		break;
		}
	case 4:{
		printf("�����˳���...\n");
		exit(0);
		}
		
	}
//	if(role==4)
	return;
}
int main() {
	while (1) {
		control_panel();
	}
	return 0;
}
