#include"stdafx.h"
#include "function.h"

student stu[305];
department dep[25];
int stu_num = 0;
int dep_num = 0;


int unluck_stu_num = 0;     //没选重部门的学生
int unluck_dep_num = 0;    //部门没选中人的数目
int addmitted_num = 0;   //部门数目
unlucky_stu unlucky_student[305];
addmit addmitted[25];
unlucky_dep unlucky_depa[25];
double rank_value[305][25];
int wishnum = 0;
wishStu wishtmp[305];





//解析 txt 文件中 json数据 存储在结构体中去
void data_output() {
	memset(stu, 0, sizeof(stu));

	Reader reader;
	Value root;
	//从文件中读取数据
	ifstream is;
	is.open("./input_data.txt", ios::binary);
	if (reader.parse(is, root)) {
		//读取根节点 student
		stu_num = root["students"].size();
		for (int i = 0; i < root["students"].size(); i++) {
			//sno
			stu[i].index = i;
			stu[i].student_no = root["students"][i]["student_no"].asString();
			//free-time
			stu[i].free_time_num = root["students"][i]["free_time"].size();
			for (int j = 0; j < root["students"][i]["free_time"].size(); j++) {
				stu[i].free_time[j] = root["students"][i]["free_time"][j].asString();
			}
			//applications_department
			stu[i].appli_dep_num = root["students"][i]["applications_department"].size();
			for (int j = 0; j < root["students"][i]["applications_department"].size(); j++) {
				stu[i].applications_department[j] = root["students"][i]["applications_department"][j].asString();
			}
			//tags
			stu[i].tags_num = root["students"][i]["tags"].size();
			for (int j = 0; j < root["students"][i]["tags"].size(); j++) {
				stu[i].tags[j] = root["students"][i]["tags"][j].asString();
			}
		}
		dep_num = root["departments"].size();
		addmitted_num = dep_num;
		//读取根节点 departments
		for (int i = 0; i < root["departments"].size(); i++) {
			//department_no
			dep[i].index = i;
			dep[i].department_no = root["departments"][i]["department_no"].asString();
			//member_limit
			dep[i].member_limit = root["departments"][i]["member_limit"].asInt();
			//event_schedules
			dep[i].event_schedules_num = root["departments"][i]["event_schedules"].size();
			for (int j = 0; j < root["departments"][i]["event_schedules"].size(); j++) {
				dep[i].event_schedules[j] = root["departments"][i]["event_schedules"][j].asString();
			}
			//tags
			dep[i].tag_num = root["departments"][i]["tags"].size();
			for (int j = 0; j < root["departments"][i]["tags"].size(); j++) {
				dep[i].tags[j] = root["departments"][i]["tags"][j].asString();
			}
		}
	}
	is.close();
}




/*数据输出到控制台  以及到文件中去*/
void data_input() {
	//根节点
	Value root;
	//unlucky_student
	for (int i = 0; i < unluck_stu_num; i++) {
		root["unlucky_student"].append(unlucky_student[i].student_sno);
	}
	//addmitted
	Value addmit;
	//子节点属性
	for (int i = 0; i < addmitted_num; i++) {
		Value root1;
		root1["department_no"] = addmitted[i].department_no;
		for (int j = 0; j < addmitted[i].memeber_num; j++) {
			root1["member"].append(addmitted[i].member[j]);
		}
		if (addmitted[i].memeber_num == 0) {
			root1["member"].resize(0);
		}
		addmit.append(root1);
	}

	root["addmitted"] = Value(addmit);

	//unlucky_department
	for (int i = 0; i < unluck_dep_num; i++) {
		root["unlucky_department"].append(unlucky_depa[i].department_no);
	}
	if (unluck_dep_num == 0) {
		root["unlucky_department"].resize(0);
	}


	StyledWriter sw;
	//输出到控制台
	//cout << sw.write(root) << endl;

	//输入文件
	ofstream os;
	os.open("output_data.txt");
	os << sw.write(root);
	os.close();
}


//测试
/*
void data_output2() {
Reader reader;
Value root;
//从文件中读取数据
ifstream is;
is.open("output_data.txt", ios::binary);
if (reader.parse(is, root)) {
unluck_stu_num = root["unlucky_student"].size();
for (int i = 0; i < root["unlucky_student"].size(); i++) {
unlucky_student[i].student_sno = root["unlucky_student"][i].asString();
//cout << unlucky_student[i].student_sno << endl;
}

//cout << "------------------------" << endl;
addmitted_num = root["addmitted"].size();
for (int i = 0; i < root["addmitted"].size(); i++) {
addmitted[i].department_no = root["addmitted"][i]["department_no"].asString();
//cout << addmitted[i].department_no << ":";
addmitted[i].memeber_num = root["addmitted"][i]["member"].size();
for (int j = 0; j < root["addmitted"][i]["member"].size(); j++) {
addmitted[i].member[j] = root["addmitted"][i]["member"][j].asString();
//cout << addmitted[i].member[j] << "|";
}
//cout << endl;
//cout << endl;
}
//cout << "------------------------" << endl;
unluck_dep_num = root["unlucky_department"].size();
for (int i = 0; i < root["unlucky_department"].size(); i++) {
unlucky_depa[i].department_no = root["unlucky_department"][i].asString();
//cout << unlucky_depa[i].department_no << endl;
}
//cout << endl;
}
}*/
