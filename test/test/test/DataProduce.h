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
	/*���Ƴ������*/
	void ToGenerate();

	/*����ѧ����*/
	void CreateStudents(int n);

	/*�������ɲ�����Ϣ*/
	void CreateDepartments(int n);

	/*�������ظ��������*/
	void Rand(int num_rand);

private:
	/*ѧ������*/
	int num_stu = 300;

	/*����ʱ������*/
	int num_ft = 42;
	/*����ʱ���*/
	string ft[50];

	/*��������*/
	int num_dep = 20;

	/*���Żʱ������*/
	int num_es = 42;

	/*Ԥ��Ĳ���ʱ���*/
	string es[50];

	/*Ԥ�貿�ű�ǩ*/
	string tags[20];

	/*�������*/
	vector<int>temp;

};

