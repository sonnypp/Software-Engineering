#pragma once
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class DataProduce
{
public:
	DataProduce();
	~DataProduce();
public:
	/*定制程序入口*/
	void ToGenerate();

	/*定制学生库*/
	void CreateStudents(int n);

	/*定制生成部门信息*/
	void CreateDepartments(int n);

	/*产生不重复的随机数*/
	void Rand(int num_rand);

private:
	/*学生数量*/
	int num_stu = 300;

	/*空闲时间数量*/
	int num_ft = 42;
	/*空闲时间段*/
	string ft[50];

	/*部门数量*/
	int num_dep = 20;

	/*部门活动时间数量*/
	int num_es = 42;

	/*预设的部门时间段*/
	string es[50];

	/*预设部门标签*/
	string tags[20];

	/*随机数组*/
	vector<int>temp;

};

