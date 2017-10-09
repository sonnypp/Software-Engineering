#pragma once
#include"function.h"



class match_algorithm
{
public:
	match_algorithm();
	~match_algorithm();
	int day_time(string str);    //时间处理
	int begin_time(string str);   //时间处理开始时间
	int end_time(string str);   //时间处理结束时间
	double match_algorithm_rank(student students, department departments, int k); //匹配  返回rank值
};


