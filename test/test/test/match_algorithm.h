#pragma once
#include"function.h"



class match_algorithm
{
public:
	match_algorithm();
	~match_algorithm();
	int day_time(string str);    //ʱ�䴦��
	int begin_time(string str);   //ʱ�䴦��ʼʱ��
	int end_time(string str);   //ʱ�䴦�����ʱ��
	double match_algorithm_rank(student students, department departments, int k); //ƥ��  ����rankֵ
};


