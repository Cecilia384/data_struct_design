#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Teacher{
	char teacher_name[20];
	int teacher_id;
	course_attribute* course;
    stu_attribute* next;
	Teacher* left;
	Teacher* right;
}Teacher;
typedef struct course_attribute{
    int num_attri;
    char string_attri;
    course_attribute* next;
    
}course_attribute;
typedef struct stu_attribute{
    int num_attri;
    char string_attri;
    stu_attribute* next;
}stu_attribute;
typedef struct Student{
	int student_id;
	char student_name[20];
	char student_tel[20];
	struct Student* next; //ָ����һ��ѧ��
	struct Student* same_class_student; //ָ��ͬ��ѧ������һ��  
	struct Stu_self_course* stu_course;//ѧ����ѡ�Ŀγ�
}Student;