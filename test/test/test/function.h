
#ifndef FUNCTION_H
#define FUNCTION_H
#include "json.h"
#include "stdafx.h"
#include <fstream>
using namespace Json;


/*input student 全局变量声明*/

extern int stu_num;
typedef struct stu_timed {
	string student_no;
	int free_time_num;
	string free_time[305];
	string applications_department[20];
	int appli_dep_num;
	string tags[200];
	int index;
	int tags_num;
	bool flag = false;
}student;
extern student stu[305];
extern student stu2[305];
extern int maybe_luck;
/*input department 全局变量声明*/
extern int dep_num;
typedef struct dep_timed {
	string event_schedules[305];
	string department_no;
	string tags[200];
	int event_schedules_num;
	int index;
	int tag_num;
	int member_limit;
}department;
extern department dep[25];


typedef struct unlucky_student {
	string student_sno;
}unlucky_stu;


typedef struct addmited {
	string department_no;
	int memeber_num = 0;
	string member[20];
}addmit;


typedef struct unlucky_department {
	string department_no;
}unlucky_dep;


extern int wishnum;
typedef struct wish {
	int stu_index;
	int dep_index;
	double value;
}wishStu;
extern wishStu wishtmp[305];

extern unlucky_stu unlucky_student[305];
extern addmit addmitted[25];
extern unlucky_dep unlucky_depa[25];
extern double rank_value[305][25];
extern int unluck_stu_num;
extern int unluck_dep_num;
extern int addmitted_num;
//数据处理  将txt中的json数据存入到结构体中
extern void data_output();

//数据以json的形式 存入txt文件中去
extern void data_input();

//测试
//extern void data_output2();




#endif
