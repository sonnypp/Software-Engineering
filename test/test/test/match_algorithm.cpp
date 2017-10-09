#include "stdafx.h"
#include "match_algorithm.h"


extern int stu_num;
match_algorithm::match_algorithm()
{
}

match_algorithm::~match_algorithm()
{
}





//时间处理代码

int match_algorithm::day_time(string str) {
	string tmp = "";
	for (int i = 0; i < str.find('.'); i++) {
		tmp += str[i];
	}
	if (tmp == "Mon") return 0 * 24 * 60;
	else if (tmp == "Tues") return 1 * 24 * 60;
	else if (tmp == "Wed") return 2 * 24 * 60;
	else if (tmp == "Thur") return 3 * 24 * 60;
	else if (tmp == "Fri") return 4 * 24 * 60;
	else if (tmp == "Sat") return 5 * 24 * 60;
	else if (tmp == "Sun") return 6 * 24 * 60;
	else return 0;
}


//时间处理代码


int match_algorithm::begin_time(string str) {
	int index1 = str.find('.');

	int index2 = str.find('~');
	int index3 = str.find_first_of(":");
	int tmp = 0;
	string hour = "";
	for (int i = index1 + 1; i < index3; i++) {
		hour += str[i];
	}
	tmp += atoi(hour.c_str()) * 60;
	string minute = "";
	for (int i = index3 + 1; i < index2; i++) {
		minute += str[i];
	}
	tmp += atoi(minute.c_str());
	return tmp;
}




//时间处理代码


int match_algorithm::end_time(string str) {
	int index = str.find('~');
	int index1 = str.find_last_of(":");
	int tmp = 0;
	string hour = "";
	for (int i = index + 1; i < index1; i++) {
		hour += str[i];
	}
	tmp += atoi(hour.c_str()) * 60;
	string minute = "";
	for (int i = index1 + 1; i < str.length(); i++) {
		minute += str[i];
	}
	tmp += atoi(minute.c_str());
	return tmp;
}


//学生部门匹配程序 返回权值


double match_algorithm::match_algorithm_rank(student students, department departments, int k) {
	int stu_begin[305];  //学生free_time 开始时间
	int stu_end[305];//学生free_time 结束时间
	int dep_begin[305];//部门event_time开始时间
	int dep_end[305];//部门event_time结束时间


	memset(stu_begin, 0, sizeof(stu_begin));
	memset(stu_end, 0, sizeof(stu_end));
	memset(dep_begin, 0, sizeof(dep_begin));
	memset(dep_end, 0, sizeof(dep_end));

	//时间都转化成分钟算
	int stu_free_num = students.free_time_num;
	//学生时间表
	for (int i = 0; i < stu_free_num; i++) {
		string str = students.free_time[i];

		stu_begin[i] = day_time(str) + begin_time(str);
		stu_end[i] = day_time(str) + end_time(str);

	}


	int dep_event_num = departments.event_schedules_num;


	//部门时间表
	for (int i = 0; i < dep_event_num; i++) {
		dep_begin[i] = day_time(departments.event_schedules[i]) + begin_time(departments.event_schedules[i]);
		dep_end[i] = day_time(departments.event_schedules[i]) + end_time(departments.event_schedules[i]);
	}



	/*
	计算权值：

	首先就是根据志愿  学生的志愿会影响到 部门对学生的印象，然后影响到权值
	其次，就是根据学生课余时间，课余时间越多，部门对该学生也会越喜欢嘛
	最后就是根据学生兴趣爱好标签，和部门越匹配，部门越喜欢。

	所以计算权值公式为

	因为学生最多可以填5个志愿

	rank1 = 3/（k*appli_num) * 10 + 3.33
	其中 k代表第几志愿，appli_num代表该学生的志愿数目   根据学生志愿  3.33 只是一个多余数目  这个最多就 33.33

	rank2 =  tim/deparment_time * 33.33
	根据学生课余时间 课余时间越多，rank值越大  tim学生能参加活动的次数   deparment_time 部门举办活动的次数

	rank3 =  match_tags/dep_tags * 33.33
	根据学生兴趣，与部门标签的占比，觉得最后的分数。 match_tags匹配到的标签数目  dep_tags部门所拥有的标签数目


	最后 rank = rank1 + rank2 + rank3


	*/

	// 分三段算权值
	double rank1 = 0, rank2 = 0, rank3 = 0;
	/*
	rank1 = 3/（k*appli_num) * 10 + 3.33
	其中 k代表第几志愿，appli_num代表该学生的志愿数目   根据学生志愿  3.33 只是一个多余数目  这个最多就 33.33
	*/
	//保证分母不为0
	if (students.appli_dep_num != 0) {
		rank1 = double(3 * 1.0 / (k*students.appli_dep_num) * 10 + 3.33);
	}


	int times = 0, match_tags = 0;   //times指的是和部门时间匹配几次  match_tags指的是标签匹配数


	for (int i = 0; i < dep_event_num; i++) {
		int mark = 0;   //标记该部门活动时间 该学生能否有时间 参加该活动
		int event_total_time = dep_end[i] - dep_begin[i];  //部门开展活动总时间
		int free_total_time = 0;   //该学生能参加活动的总时间
		for (int j = 0; j < stu_free_num; j++) {
			if (stu_begin[j] <= dep_begin[i] && stu_end[j] <= dep_end[i] || free_total_time >= event_total_time) {
				mark = 1;
				break;
			}
			else if (stu_begin[j] >= dep_begin[i] && stu_end[j] >= dep_end[i]) {
				if (stu_begin[j] < dep_end[i]) free_total_time += dep_end[i] - stu_begin[j];
				else  continue;
			}
			else if (stu_end[j] <= dep_end[i] && stu_begin[j] <= dep_begin[i]) {
				if (stu_end[j] <= dep_begin[i]) { continue; }
				else free_total_time += stu_end[j] - dep_begin[i];
			}
			else {
				free_total_time += stu_end[i] - stu_begin[i];
			}
		}
		if (mark == 1) {
			times++;
		}
		else if ((double)(free_total_time*1.0 / event_total_time) > 0.5) {
			times++;
		}   //时间占部门活动时间超过百分之五十 就算匹配
	}

	/*  rank2 =  tim/deparment_time * 33.33
	根据学生课余时间 课余时间越多，rank值越大  tim学生能参加活动的次数   deparment_time 部门举办活动的次数
	*/

	//保证分母不为0
	if (departments.event_schedules_num != 0) {
		rank2 = double(1.0*times / (departments.event_schedules_num) * 33.33);
	}

	/*
	rank3 =  match_tags/dep_tags * 33.33
	根据学生兴趣，与部门标签的占比，觉得最后的分数。 match_tags匹配到的标签数目  dep_tags部门所拥有的标签数目
	*/
	for (int i = 0; i < departments.tag_num; i++) {
		for (int j = 0; j < students.tags_num; j++) {
			if (departments.tags[i] == students.tags[j]) {
				match_tags++;
			}
		}
	}

	//保证分母不为0
	if (departments.tag_num != 0) {
		rank3 = double(1.0*match_tags / departments.tag_num * 33.33);
	}
	return rank1 + rank2 + rank3;

}

