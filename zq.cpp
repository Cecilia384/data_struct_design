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
	Student* students;//所教授的学生
	Teacher* left;
	Teacher* right;
	Course* courses;//所教授的课程
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

// 用户结构体
typedef struct {
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];
	char role[MAX_LENGTH];
} User;

Teacher* teacher_root=NULL;//教师根节点
Student* student_head=NULL;//学生链表头节点
Student* now_student=NULL;//当前登录的学生
Teacher* now_teacher=NULL;//当前登录的教师
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
	printf("欢迎使用课程管理信息系统！\n");
	printf("---------------------------\n");
	printf("请选择您的身份：\n");
	printf("1. 管理员\n");
	printf("2. 教师\n");
	printf("3. 学生\n");
	printf("4. 退出\n");
	printf("---------------------------\n");
}

void administer_menu() {
	printf("[管理员] 请选择操作：\n");
	printf("1. 创建计算机专业课程信息\n");
	printf("2. 删除计算机专业课程信息\n");
	printf("3. 统计计算机专业开设课程的总数\n");
	printf("4. 查询每门课程修课人数\n");
	printf("5. 浏览计算机专业的课程信息\n");
	printf("6. 退出\n");
}

void teacher_menu() {
	printf("[教师] 请选择操作：\n");
	printf("1. 查看所教授的课程信息\n");
	printf("2. 查询所教授的学生的信息\n");
	printf("3. 输入课程成绩\n");
	printf("4. 修改课程成绩\n");
	printf("5. 统计成绩信息(统计90分以上、80~90分、60~80分、60分以下的人数)\n");
	printf("6. 退出\n");
}

void student_menu() {
	printf("[学生] 请选择操作：\n");
	printf("1. 查询课程信息\n");
	printf("2. 报名课程\n");
	printf("3. 取消课程报名\n");
	printf("4. 查询成绩\n");
	printf("5. 浏览所有课程信息\n");
	printf("6. 退出\n");
}
//管理员功能集合


// 创建课程信息
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
	printf("课程号：");
	scanf("%d", &course_id);
	printf("课程名：");
	scanf("%s", course_name);
	printf("课程学分：");


	scanf("%d", &course_credit);
	char teacher_name[20];
	int teacher_id;


	printf("请输入任课教师的姓名：");

	scanf("%s", teacher_name);
	//Teacher* teacher;


	printf("请输入任课教师的工号：");
	scanf("%d", &teacher_id);
	Teacher* new_teacher = new_teacher_node(teacher_id, teacher_name);
	new_course = new_course_node(course_id, course_name, course_credit, course_time, course_place, new_teacher);
	new_teacher->courses=new_course;
	teacher_root=new_teacher_insert(teacher_root, new_teacher);
	printf("成功创建课程信息%s-%d！\n", course_name, course_id);
	course_num++;
}

// 删除课程信息
void delete_course_info() {
	int course_id;
	printf("请输入课程号:\n");
	scanf("%d",&course_id);
	int removed_index = -1;
	for (int i = 0; i < course_num; i++) {
		if (courses[i].course_id == course_id) {
			removed_index = i;
			break;
		}
	}
	if (removed_index == -1) {
		printf("未找到课程号为 %d 的课程信息！\n", course_id);
		return;
	}
	// 删除该课程
	for (int i = removed_index+1; i < course_num; i++) {
		courses[i-1] = courses[i];
	}
	course_num--;
	
	printf("成功删除课程号为 %d 的课程信息！\n", course_id);
	course_num--;
}
// 统计计算机开设课程总数
void count_total_courses() {
	int total_courses = course_num;
	printf("计算机开设课程总数：%d\n", total_courses);
}
//每门课修课人数
void count_students_in_course() {
	int course_id;
	printf("请输入课程号:\n");
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
	printf("该门课修课人数为:  %d",count);
	return;
}

//
// 查询课程成绩
void search_grade_by_course_id() {
	int course_id;
	printf("请输入课程号:\n");
	scanf("%d",&course_id);
	for (int i = 0; i < course_num; i++) {
		if (courses[i].course_id == course_id) {
			printf("课程ID：%d\n", courses[i].course_id);
			printf("课程名称：%s\n", courses[i].course_name);
			printf("课程教师：%s\n", courses[i].course_teacher);
			printf("课程学分：%d\n", courses[i].course_credit);
			printf("已选该课程学生及成绩：\n");
			selected_course* current_course = students[0].student_course;
			while (current_course != NULL) {
				if (current_course->course_id == course_id) {
					printf("学生姓名：%s\t成绩：%d\n", current_course->student_name, current_course->course_grade);
				}
				current_course = current_course->next;
			}
			return;
		}
	}
	printf("未找到该课程！\n");
}

// 根据学号查询课程信息
void search_courses_by_student_num() {
	int student_num;
	printf("请输入学号:\n");
	scanf("%d",&student_num);
	Student* current_student = NULL;
	for (int i = 0; i < num_students; i++) {
		if (students[i].student_num == student_num) {
			current_student = &students[i];
			break;
		}
	}
	
	if (current_student == NULL) {
		printf("未找到该学生！\n");
		return;
	}
	
	printf("学生姓名：%s\n", current_student->student_name);
	
	selected_course* current_course = current_student->student_course;
	if (current_course == NULL) {
		printf("该学生未选择任何课程！\n");
		return;
	}
	
	printf("已选课程信息：\n");
	while (current_course != NULL) {
		int course_id = current_course->course_id;
		for (int i = 0; i < course_num; i++) {
			if (courses[i].course_id == course_id) {
				printf("课程ID：%d\n", courses[i].course_id);
				printf("课程名称：%s\n", courses[i].course_name);
				printf("课程教师：%s\n", courses[i].course_teacher);
				printf("课程学分：%d\n", courses[i].course_credit);
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
	return NULL; // 如果找不到对应课程，返回NULL
}
void search_course_by_id(){
	int course_id;
	printf("请输入课程号：\n");
	scanf("%d",&course_id);
	Course* course = find_course_by_id(course_id); // 根据课程号123查询课程信息
	if (course != NULL) {
		// 处理课程信息
		printf("课程名称：%s\n", course->course_name);
		printf("学分：%d\n", course->course_credit);
		// 其他课程信息
	} else {
		printf("未找到对应课程！\n");
	}
}

void count_students_by_grade() {
	int course_id;
	printf("请输入课程号:\n");
	scanf("%d",&course_id);
	int count_90_above = 0;
	int count_80_to_90 = 0;
	int count_60_to_80 = 0;
	int count_below_60 = 0;
	// 遍历所有学生
	for (int i = 0; i < num_students; i++) {
		Student* current_student = &students[i];
		
		// 检查学生是否选修了指定课程
		for (int j = 0; j < current_student->num_enrolled_courses; j++) {
			int enrolled_course_id = current_student->enrolled_courses[j];
			if (enrolled_course_id == course_id) {
				// 获取该学生的成绩
				int grade = current_student->student_course->course_grade;
				
				// 根据成绩范围进行判断和统计
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
	// 打印统计结果
	printf("90分以上的人数：%d\n", count_90_above);
	printf("80-90分的人数：%d\n", count_80_to_90);
	printf("60-80分的人数：%d\n", count_60_to_80);
	printf("60分以下的人数：%d\n", count_below_60);
}

void input_student_grade() {
	int student_num;
	int course_id;
	printf("请输入学生学号:\n");
	scanf("%d",&student_num);
	printf("请输入课程号:\n");
	scanf("%d",&course_id);
	bool found_student = false;
	bool found_course = false;
	// 遍历学生数组
	for (int i = 0; i < num_students; i++) {
		Student* current_student = &students[i];
		// 找到匹配学号的学生
		if (current_student->student_num == student_num) {
			found_student = true;
			
			// 检查学生的选课记录
			selected_course* current_course = current_student->student_course;
			while (current_course != NULL) {
				// 找到匹配课程ID的选课记录
				if (current_course->course_id == course_id) {
					found_course = true;
					
					// 提示输入课程成绩
					printf("请输入学生 %s 的课程成绩：", current_student->student_name);
					int grade;
					scanf("%d", &grade);
					
					// 更新选课记录中的成绩
					current_course->course_grade = grade;
					
					printf("已成功输入学生 %s 的课程成绩。\n", current_student->student_name);
					break;
				}
				
				current_course = current_course->next;
			}
			
			// 如果没有找到匹配的选课记录
			if (!found_course) {
				printf("该学生未选修该门课程。\n");
			}
			
			break;
		}
	}
	// 处理输入异常情况
	if (!found_student) {
		printf("学号 %d 不存在。\n", student_num);
	}
}

void modify_student_grade() {
	int student_num;
	int course_id;
	printf("请输入学生学号:\n");
	scanf("%d",&student_num);
	printf("请输入课程号:\n");
	scanf("%d",&course_id);
	bool found_student = false;
	bool found_course = false;
	
	// 遍历学生数组
	for (int i = 0; i < num_students; i++) {
		Student* current_student = &students[i];
		
		// 找到匹配学号的学生
		if (current_student->student_num == student_num) {
			found_student = true;
			
			// 检查学生的选课记录
			selected_course* current_course = current_student->student_course;
			while (current_course != NULL) {
				// 找到匹配课程ID的选课记录
				if (current_course->course_id == course_id) {
					found_course = true;
					
					// 提示输入新的课程成绩
					printf("请输入学生 %s 的新课程成绩：", current_student->student_name);
					int grade;
					scanf("%d", &grade);
					
					// 更新选课记录中的成绩
					current_course->course_grade = grade;
					
					printf("已成功修改学生 %s 的课程成绩。\n", current_student->student_name);
					break;
				}
				current_course = current_course->next;
			}
			// 如果没有找到匹配的选课记录
			if (!found_course) {
				printf("该学生未选修该门课程。\n");
			}
			
			break;
		}
	}
	
	// 处理输入异常情况
	if (!found_student) {
		printf("学号 %d 不存在。\n", student_num);
	}
}

// 中序遍历树，按课程号升序输出
Teacher* inorder_traversal(Teacher* teacher_root) {
	if (teacher_root != NULL) {
		inorder_traversal(teacher_root->left);
		Course* temp=teacher_root->courses;
		printf("  课程名称:%s  课程号:%d\t",temp->course_name,temp->course_id);
		printf("  老师:%s      工号:%d\n",teacher_root->name,teacher_root->id);
		inorder_traversal(teacher_root->right);
	}
	return teacher_root;
}
Teacher* show_course_info(Teacher* root){
	printf("\t\t当前课程总数为:%d\n",course_num );
	if(root!=NULL){
		inorder_traversal(root->left);
		Course* temp=root->courses;
		printf("\n\t\t课程名称:%s\t课程号:%d\t课程学分:%d\n",temp->course_name,temp->course_id,temp->course_credit);
		printf("\t\t任课老师:%s\t老师工号:%d\t课程上课时间:%s\n",temp->course_teacher,root->id,temp->course_time);
		show_course_info(root->right);
	}else{
		printf("当前课程为空！请先新建课程!\n");
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
		printf("\t\t课程名称:%s\t课程号:%d\t",temp->course_name,temp->course_id);
		printf("\t\t老师:%s\t工号:%d\n",teacher_root->name,teacher_root->id);
		inorder_traversal_teacher(teacher_root->right, id);
	}
}

// 学生选课
void enroll_course(Student* student ) {
	int course_id;
	printf("请输入选课的课程号:\n");
	scanf("%d",&course_id);
	if (student->num_enrolled_courses >= MAX_COURSES) {
		printf("%s 学生选课已达上限，无法再选！\n", student->student_name);
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
		printf("未找到课程号为 %d 的课程信息！\n", course_id);
		return;
	}
	
	if (selected_course->class_remain_num <= 0) {
		printf("%s 课程名额已满，无法选课！\n", selected_course->course_name);
		return;
	}
	
	int enrolled_course_index = student->num_enrolled_courses;
	student->enrolled_courses[enrolled_course_index] = course_id;
	student->num_enrolled_courses++;
	selected_course->class_remain_num--;
	printf("%s 学生成功选修 %s 课程！\n", student->student_name, selected_course->course_name);
}

// 取消选课
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
		printf("%s 未选修课程号为 %d 的课程！\n", student->student_name, course_id);
		return;
	}
	
	// 更新学生的选课信息
	for (int i = removed_index+1; i < student->num_enrolled_courses; i++) {
		student->enrolled_courses[i-1] = student->enrolled_courses[i];
	}
	student->num_enrolled_courses--;
	
	// 更新课程的名额
	Course* removed_course = NULL;
	for (int i = 0; i < course_num; i++) {
		if (courses[i].course_id == course_id) {
			removed_course = &courses[i];
			break;
		}
	}
	removed_course->class_remain_num++;
	
	printf("%s 成功取消选修课程 %s (课程号：%d)！\n", student->student_name, removed_course->course_name, course_id);
}
// 查询成绩
void search_grade_by_student_id(int student_id) {
	Student* current_student = now_student;
	while (current_student != NULL) {
		if (current_student->student_num == student_id) {
			printf("学号：%d\n", current_student->student_num);
			printf("姓名：%s\n", current_student->student_name);
			printf("电话：%s\n", current_student->student_tel);
			printf("已选课程及成绩：\n");
			selected_course* current_course = current_student->student_course;
			while (current_course != NULL) {
				printf("课程：%s\t成绩：%d\n", current_course->course_name, current_course->course_grade);
				if(current_course->next!=NULL)
					current_course = current_course->next;
			}
			return;
		}
		// current_student->class_next = current_student;
	}
	printf("未找到该学生！\n");
}

// 浏览所有课程信息
void browse_all_courses() {
	printf("所有课程信息：\n");
	for (int i = 0; i < course_num; i++) {
		printf("课程ID：%d\n", courses[i].course_id);
		printf("课程名称：%s\n", courses[i].course_name);
		printf("课程教师：%s\n", courses[i].course_teacher);
		printf("课程学分：%d\n", courses[i].course_credit);
		printf("课程上课时间：%s\n", courses[i].course_time);
		printf("课程上课地点：%s\n", courses[i].course_place);
		printf("剩余名额：%d\n", courses[i].class_remain_num);
		printf("\n");
	}
}
void display_all_courses(Teacher* teacher_root) {
	if (teacher_root != NULL) {
		display_all_courses(teacher_root->left);
		Course* temp = teacher_root->courses;
		while (temp != NULL) {
			printf("课程名称：%s\t课程号：%d\t老师：%s\t工号：%d\n",
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
  printf("请输入学号：");
  scanf("%d", &student_num);
  for (int i = 0; i < student_count; i++) {
  if (student_num == students[i].student_num) {
  return i;
  }
  }
  printf("登录失败，请检查学号是否输入正确！\n");
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
		printf("请输入管理员密码: \n");
		scanf("%s", password);
		if (strcmp(password,arr1)==0)//使用等号比较字符串 错误
		{
			printf("登录成功!\n");
			return -1;
			
		}
		else
		{
			printf("密码错误，请重新输入!\n");
		}
	}
	printf("您已输入三次,请联系教务处！\n");
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
		case 6://退出到主菜单
		printf("正在退出...\n");
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
			case 1://查询课程信息
			search_course_by_id();
			break;
			case 2://报名课程
			enroll_course(now_student);
			break;
			case 3://取消报名课程
			cancel_enrollment(now_student);
			break;
			case 4://查询课程成绩
			search_grade_by_course_id();
			break;
			case 5: //浏览所有课程信息
			//printf("此时正在执行第五个功能");
			//display_all_courses(teacher_root);
			browse_all_courses();
			break;
		case 6:
			flag=false;
			break;
			
		}}
}

// 根据用户名和密码在文件中查找对应的用户信息
User* find_user(const char* username, const char* password, int code_id) {
	FILE* file;
	if (code_id == 1) { // 学生身份
		file = fopen("C:\\Users\\qianq\\Desktop\\学生账号密码.txt", "r");
        printf("请输入姓名：\n");char username[20];int stu_id;
        scanf("%s",username);
        printf("请输入学号：\n");scanf("%d",&stu_id);
        printf("请输入电话号码：\n");char stu_tel[20];scanf("%s",stu_tel);
        Student* new_student=createNewStudent(username,stu_id,stu_tel);
        now_student=new_student;    
        appendStudnet(&student_head,new_student);
         
	} else if (code_id == 2) { // 教师身份
		file = fopen("C:\\Users\\qianq\\Desktop\\教师账号密码.txt", "r");
        printf("请输入姓名：\n");char teacher_name[20];int teacher_id;
        scanf("%s",teacher_name);
        printf("请输入工号：\n");scanf("%d",&teacher_id);
        now_teacher=createNewTeacher(teacher_name,teacher_id);
      
	} else {
		printf("无效的身份代码！\n");
		return NULL;
	}
	
	if (file == NULL) {
		printf("无法打开用户文件！\n");
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
	printf("用户登录\n");
	printf("请输入用户名：");
	scanf("%s", username);
	printf("请输入密码：");
	scanf("%s", password);
	User* user = find_user(username, password,id_code);
	if (user != NULL) {
		printf("登录成功！\n");
		printf("欢迎，%s！\n", user->username);
		// printf("角色：%s\n", user->role);
		if (id_code == 1) {
			student_function();
		} else if (id_code == 2) {
			teacher_function();
		}
	} else {
		printf("登录失败，请检查用户名和密码！\n");
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
		user_log_in(1);//学生身份
		break;
		}
	case 4:{
		printf("正在退出中...\n");
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
