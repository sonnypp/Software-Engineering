#include "stdafx.h"
#include "match_algorithm.h"


extern int stu_num;
match_algorithm::match_algorithm()
{
}

match_algorithm::~match_algorithm()
{
}





//ʱ�䴦�����

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


//ʱ�䴦�����


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




//ʱ�䴦�����


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


//ѧ������ƥ����� ����Ȩֵ


double match_algorithm::match_algorithm_rank(student students, department departments, int k) {
	int stu_begin[305];  //ѧ��free_time ��ʼʱ��
	int stu_end[305];//ѧ��free_time ����ʱ��
	int dep_begin[305];//����event_time��ʼʱ��
	int dep_end[305];//����event_time����ʱ��


	memset(stu_begin, 0, sizeof(stu_begin));
	memset(stu_end, 0, sizeof(stu_end));
	memset(dep_begin, 0, sizeof(dep_begin));
	memset(dep_end, 0, sizeof(dep_end));

	//ʱ�䶼ת���ɷ�����
	int stu_free_num = students.free_time_num;
	//ѧ��ʱ���
	for (int i = 0; i < stu_free_num; i++) {
		string str = students.free_time[i];

		stu_begin[i] = day_time(str) + begin_time(str);
		stu_end[i] = day_time(str) + end_time(str);

	}


	int dep_event_num = departments.event_schedules_num;


	//����ʱ���
	for (int i = 0; i < dep_event_num; i++) {
		dep_begin[i] = day_time(departments.event_schedules[i]) + begin_time(departments.event_schedules[i]);
		dep_end[i] = day_time(departments.event_schedules[i]) + end_time(departments.event_schedules[i]);
	}



	/*
	����Ȩֵ��

	���Ⱦ��Ǹ���־Ը  ѧ����־Ը��Ӱ�쵽 ���Ŷ�ѧ����ӡ��Ȼ��Ӱ�쵽Ȩֵ
	��Σ����Ǹ���ѧ������ʱ�䣬����ʱ��Խ�࣬���ŶԸ�ѧ��Ҳ��Խϲ����
	�����Ǹ���ѧ����Ȥ���ñ�ǩ���Ͳ���Խƥ�䣬����Խϲ����

	���Լ���Ȩֵ��ʽΪ

	��Ϊѧ����������5��־Ը

	rank1 = 3/��k*appli_num) * 10 + 3.33
	���� k����ڼ�־Ը��appli_num�����ѧ����־Ը��Ŀ   ����ѧ��־Ը  3.33 ֻ��һ��������Ŀ  ������� 33.33

	rank2 =  tim/deparment_time * 33.33
	����ѧ������ʱ�� ����ʱ��Խ�࣬rankֵԽ��  timѧ���ܲμӻ�Ĵ���   deparment_time ���žٰ��Ĵ���

	rank3 =  match_tags/dep_tags * 33.33
	����ѧ����Ȥ���벿�ű�ǩ��ռ�ȣ��������ķ����� match_tagsƥ�䵽�ı�ǩ��Ŀ  dep_tags������ӵ�еı�ǩ��Ŀ


	��� rank = rank1 + rank2 + rank3


	*/

	// ��������Ȩֵ
	double rank1 = 0, rank2 = 0, rank3 = 0;
	/*
	rank1 = 3/��k*appli_num) * 10 + 3.33
	���� k����ڼ�־Ը��appli_num�����ѧ����־Ը��Ŀ   ����ѧ��־Ը  3.33 ֻ��һ��������Ŀ  ������� 33.33
	*/
	//��֤��ĸ��Ϊ0
	if (students.appli_dep_num != 0) {
		rank1 = double(3 * 1.0 / (k*students.appli_dep_num) * 10 + 3.33);
	}


	int times = 0, match_tags = 0;   //timesָ���ǺͲ���ʱ��ƥ�伸��  match_tagsָ���Ǳ�ǩƥ����


	for (int i = 0; i < dep_event_num; i++) {
		int mark = 0;   //��Ǹò��Żʱ�� ��ѧ���ܷ���ʱ�� �μӸû
		int event_total_time = dep_end[i] - dep_begin[i];  //���ſ�չ���ʱ��
		int free_total_time = 0;   //��ѧ���ܲμӻ����ʱ��
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
		}   //ʱ��ռ���Żʱ�䳬���ٷ�֮��ʮ ����ƥ��
	}

	/*  rank2 =  tim/deparment_time * 33.33
	����ѧ������ʱ�� ����ʱ��Խ�࣬rankֵԽ��  timѧ���ܲμӻ�Ĵ���   deparment_time ���žٰ��Ĵ���
	*/

	//��֤��ĸ��Ϊ0
	if (departments.event_schedules_num != 0) {
		rank2 = double(1.0*times / (departments.event_schedules_num) * 33.33);
	}

	/*
	rank3 =  match_tags/dep_tags * 33.33
	����ѧ����Ȥ���벿�ű�ǩ��ռ�ȣ��������ķ����� match_tagsƥ�䵽�ı�ǩ��Ŀ  dep_tags������ӵ�еı�ǩ��Ŀ
	*/
	for (int i = 0; i < departments.tag_num; i++) {
		for (int j = 0; j < students.tags_num; j++) {
			if (departments.tags[i] == students.tags[j]) {
				match_tags++;
			}
		}
	}

	//��֤��ĸ��Ϊ0
	if (departments.tag_num != 0) {
		rank3 = double(1.0*match_tags / departments.tag_num * 33.33);
	}
	return rank1 + rank2 + rank3;

}

