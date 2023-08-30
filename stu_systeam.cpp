#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int MAX=110;
int course_num=0;   //课程数量
bool id_status[MAX]; //学生id是否注册
typedef struct Student{
    int student_id;
    char student_name[20];
    char student_tel[20];
    int student_score;
    struct Student* next; //指向下一个学生
    struct Student* same_class_student; //指向同班学生的下一个  
    struct Stu_view_course* stu_course;//学生所选的课程
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
typedef struct Stu_view_course{  //学生能看到课程信息
    char course_name[20];
    int course_id;          //课程号
    int course_credit;      //学分
    char course_teacher[20];
     int teacher_id;
    struct stu_view_course* next;    //指向下一个课程
}Stu_view_course;

typedef struct Teacher{
    char teacher_name[20];
    int teacher_id;
    Course* course;
    struct Student* student_list;
    struct Teacher* left;
    struct Teacher* right;
}Teacher;

Teacher* root=NULL;
Student* studentList=NULL;
Student* student_now=NULL;      //正在使用系统的学生
void showMenu();
void menu_fun();


void showMenu()
{
    printf("\t\t******************************************\n");
    printf("\t\t**\t                        \t**\n");
    printf("\t\t**\t 学生选课系统  \t**\n");
    printf("\t\t**\t                        \t**\n");
    printf("\t\t**\t*  请选择用户权限 *\t**\n");
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
    printf("\t\t**\t*  [6].浏览计算机专业的课程信息  *\t**\n");
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
    Course* new_course=(Course*)malloc(sizeof(Course));
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
    Teacher* new_teacher=(Teacher*)malloc(sizeof(Teacher));
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
        printf("课程名称:%s\t课程号:%d\t",temp->course_name,temp->course_id);
        printf("老师:%s\t工号:%d\n",root->teacher_name,root->teacher_id);
        inorder_Teacher_Node(root->right);
    }
    return root;
}
//展示选课界面(中序遍历一次)
Teacher* show_course_info(Teacher* root){
    printf("当前课程总数为:%d\n",course_num );
     if(root!=NULL){
        inorder_Teacher_Node(root->left);
        Course* temp=root->course;
        printf("\n课程名称:%s\t课程号:%d\t课程学分:%d\t课程容量:%d\t课程剩余容量:%d\n",temp->course_name,temp->course_id,temp->course_credit,temp->course_capacity,temp->course_remain);
        printf("课程任课老师:%s\t老师工号:%d\t课程上课时间:%s\n",temp->course_teacher,root->teacher_id,temp->course_time);
        inorder_Teacher_Node(root->right);
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
        printf("请输入需要添加的课程信息\n");
        printf("\n课程名: ");    char course_name[20];      scanf("%s",course_name);
        printf("\n课程号: ");    int course_id;             scanf("%d",&course_id);
        printf("\n学分: ");      int course_credit;         scanf("%d",&course_credit);
        printf("\n总容量: ");    int course_capacity;       scanf("%d",&course_capacity);
        printf("\n任课老师: ");  char course_teacher[20];   scanf("%s",course_teacher);
        printf("\n老师工号: ");  int teacher_id;            scanf("%d",&teacher_id);
        printf("\n上课时间:");   char course_time[20];      scanf("%s",course_time);
        Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id);
        Course* new_course=createNewCourse(course_name,course_id,course_credit,course_capacity,course_teacher,course_time);
        new_teacher->course=new_course;
        course_num++;
        root=insert_Teacher_Node(root,new_teacher); //插入老师结点
        printf("\n课程%s-%d信息录入成功!\n",course_name,course_id );
}
void admin_delete_course(){

}
void admin_create_course(){
    printf("请输入要创建的课程总数:");
    int course_num;
    scanf("%d",&course_num);
    while(course_num--){
        printf("请输入课程信息\n");
        printf("\n课程名: ");    char course_name[20];      scanf("%s",course_name);
        printf("\n课程号: ");    int course_id;             scanf("%d",&course_id);
        printf("\n学分: ");      int course_credit;         scanf("%d",&course_credit);
        printf("\n总容量: ");    int course_capacity;       scanf("%d",&course_capacity);
        printf("\n任课老师: ");  char course_teacher[20];   scanf("%s",course_teacher);
        printf("\n老师工号: ");  int teacher_id;            scanf("%d",&teacher_id);
        printf("\n上课时间:");   char course_time[20];      scanf("%s",course_time);
        Teacher* new_teacher=createNewTeacher(course_teacher,teacher_id);
        Course* new_course=createNewCourse(course_name,course_id,course_credit,course_capacity,course_teacher,course_time);
        new_teacher->course=new_course;
        course_num++;
        root=insert_Teacher_Node(root,new_teacher); //插入老师结点
        printf("\n课程%s-%d信息录入成功!\n",course_name,course_id );
        printf("还需创建%d门课程\n",course_num );
    }
    
}
void admin_count_course(){
    printf("当前课程总数为:%d\n",course_num );
}
void admin_count_student(){
    system("cls");
    printf("当前开设的课程有:\n");
    inorder_Teacher_Node(root);
    printf("请输入要查询课程的老师工号\n");
    int teacher_id;scanf("%d",&teacher_id);
    Teacher *find_teacher=search_Teacher_Node(root,teacher_id);
    if(find_teacher==NULL){
        printf("未找到该老师,请重新输入\n");
        return;
    }
    else{
        printf("该老师开设的课程为:%s\t",find_teacher->course->course_name);
        printf("学生人数为%d:\n",find_teacher->course->course_selected);
    }
}
void admin_output_all_courses(){
    system("cls");
    printf("当前开设的课程有:\n");
    inorder_Teacher_Node(root);
}

void teacher_course_info(){

}
void teacher_student_in_class(){

}
void teacher_input_student_course_score(){

}
void teacher_change_student_course_score(){

}
void teacher_count_student_score(){
    //+,90,80,60,-
}

Student* createNewStudent(int student_id,char student_name[20],char student_tel[20],int student_score){
    Student* new_student=(Student*)malloc(sizeof(Student));
    new_student->student_id=student_id;
    strcpy(new_student->student_name,student_name);
    strcpy(new_student->student_tel,student_tel);
    new_student->student_score=student_score;
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
        printf("学生姓名:%s\t学号:%d\t电话:%s\t成绩:%d\n",temp->student_name,temp->student_id,temp->student_tel,temp->student_score);
    }
}

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
// 输出学生选择的课程
void PrintCoures(Student* StudentList){
    Student* temp=StudentList;
    while(temp!=NULL){
        printf("课程名称:%s\t课程号:%d\t",temp->stu_course->course_name,temp->stu_course->course_id);
        printf("老师:%s\t工号:%d\n",temp->stu_course->course_teacher,temp->stu_course->teacher_id);
    }
}
void student_course_info(){
    system("cls");
    printf("\t\t当前可选课程有:\n");
    show_course_info(root);
}
void student_select_course(){
    system("cls");
    printf("\t\t请输入您要选择的课程对应的老师工号:");
    int teacher_id;scanf("%d",&teacher_id);
    Teacher* find_teacher=search_Teacher_Node(root,teacher_id);
    if(find_teacher==NULL){
        printf("未找到该老师,请重新输入\n");
        return;
    }
    else{
        printf("该老师开设的课程为:%s\t",find_teacher->course->course_name);
        printf("总容量为%d\t",find_teacher->course->course_capacity);
        printf("剩余容量为%d\n",find_teacher->course->course_remain);
        if(find_teacher->course->course_remain>=find_teacher->course->course_capacity){
            printf("该课程已满,请选择其他课程!\n");
        }else{
            find_teacher->course->course_remain--;
            find_teacher->course->course_selected++;
            addStudentToCourse(find_teacher,student_now);
            printf("选课成功!\n");
        }
    }
}
void student_cancel_course(){

}
void student_query_score(){

}
void student_output_all_courses(){

}

void admin_fun(){
     while(1)
    {
    	system("cls");
        system("COLOR fd");
        showMenu_Adimn();
        int select;
        scanf("%d",&select);
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
            printf("您已退出管理员系统\n");
            return ;//退出系统
        default:
            printf("输入值无效,请重新输入\n~");
            continue;
        }
        
    }
   
    menu_fun();
}
void teacher_fun(){
    system("cls");
    printf("\t\t请输入您的工号:");
    int teacher_id;scanf("%d",&teacher_id);
    while(1){
        system("cls");
        system("COLOR fd");
        showMenu_teacher();
        int select;
        scanf("%d",&select);
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
            printf("您已退出老师系统\n");
            return ;//退出系统
        default:
            printf("输入值无效,请重新输入\n~");
            continue;
        }
    }
    menu_fun();
}
void student_fun(){
    system("cls");
    printf("\t\t请输入您的学号:");
    int student_id;scanf("%d",&student_id) ;
   
    if(id_status[student_id]==false){
        printf("您还未注册,请完善信息之后重新登入\n");
        printf("请输入您的姓名:");
        char student_name[20];scanf("%s",student_name);
        printf("请输入您的电话:");char student_tel[20];scanf("%s",&student_tel); 
        appendStudnet(&studentList,createNewStudent(student_id,student_name,student_tel,0));
        id_status[student_id]=true;  
        printf("注册成功!\n");
        return;
    }else{
        student_now=FindStudent(studentList,student_id);
    }
    while(1){
        system("cls");
        system("COLOR fd");
        showMenu_student();
        int select;
        scanf("%d",&select);
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
            printf("您已退出学生系统\n");
            return ;//退出系统
        default:
            printf("输入值无效,请重新输入\n~");
            continue;
        }
    }
    menu_fun();
}
void menu_fun(){
	 while(1)
    {
        system("COLOR fd");
        showMenu();
        int select;
        scanf("%d",&select);
        switch(select)
        {
        case 1:
        	admin_fun(); 
            break; 
        case 2:
            teacher_fun();
            break;  
        case 3:
            student_fun();
            break;
        case 4 :
            printf("您已退出学生管理系统\n");
            system("pause");
            return ;
        default:
            printf("输入值无效,请重新输入\n~");
            continue;
        }
        system("pause");
        // 会暂停程序的执行，等待用户按下任意键后继续执行
        system("cls");	//清空控制台窗口中的所有内容。 
    }
    system("pause");
}

int main(){
    
    menu_fun();
    return 0;

}