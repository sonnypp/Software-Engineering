#include "stdafx.h"
#include "DataProduce.h"
#include "DataProduce.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


DataProduce::DataProduce()
{
	/*-1- 初始化时间库*/
	string date[7] =
	{
		"Sun.","Mon.","Tues.","Wen.","Thur.","Fri.","Sat."
	};
	string time[6] =
	{
		"10:30~11:30","12:30~13:30","16:30~17:30","18:00~19:30","20:00~21:00","21:30~22:30"
	};

	int k = 0;

	/*生成空闲时间库*/
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			ft[k] = "\"" + date[i] + time[j] + "\"";
			es[k++] = "\"" + date[i] + time[j] + "\"";
		}
	}
	/*-2- 初始化标签库*/
	tags[0] = "Sports";
	tags[1] = "Football";
	tags[2] = "Basketball";
	tags[3] = "Runnig";
	tags[4] = "Film";
	tags[5] = "Chess";
	tags[6] = "Study";
	tags[7] = "Programing";
	tags[8] = "Math";
	tags[9] = "Computer";
	tags[10] = "Singing";
	tags[11] = "Dancing";
	tags[12] = "Handwriting";
	tags[13] = "Painting";
	tags[14] = "Performing";
	tags[15] = "PhotoShop";
	tags[16] = "Japanese";
	tags[17] = "English";
	tags[18] = "Music";
	tags[19] = "Responsibility";
}


DataProduce::~DataProduce()
{
}


ofstream out("./input_data.txt", ios::in);

template<class RandomAccessIterator>
void random_shuffle(
	RandomAccessIterator _First,
	RandomAccessIterator _Last
);

void DataProduce::Rand(int num_rand)
{
	for (int i = 0; i < num_rand; i++)
	{
		temp.push_back(i);
	}
}


void DataProduce::ToGenerate()
{
	if (out.is_open() == false) {
		out.open("./input_data.txt", ios::_Noreplace);
	}
	/*获取随机数种子，下面要用*/
	srand((unsigned)time(NULL));

	/*定制学生信息，并输出到文件上*/
	if (out.is_open())
	{
		out << "{" << endl << "    \"students\": [" << endl;
	}
	/*是否成功打开文件*/
	else
	{
		cout << "The file does not open!" << endl;
	}

	for (int i = 0; i < num_stu; i++)
	{
		/*调用子方法，定制生成并输出学生数据*/
		CreateStudents(i + 1);
		if (i < num_stu - 1) {
			out << "," << endl;
		}

	}

	/*定制部门信息*/
	if (out.is_open())
	{
		out << endl << "    ]," << endl << "    \"departments\": [" << endl;
	}
	else
	{
		cout << "The file does not open!" << endl;
	}

	for (int i = 0; i < num_dep; i++)
	{
		/*调用子方法，定制生成并输出部门数据*/
		CreateDepartments(i + 1);
		if (i < num_dep - 1) {
			out << "," << endl;
		}

	}

	if (out.is_open())
	{
		out << endl << "    ]" << endl << "}" << endl;
	}
	else
	{
		cout << "The file does not open!" << endl;
	}
}

/*定制学生库*/
void DataProduce::CreateStudents(int n)
{
	//InitFreeTime();
	//InitTags();
	string str_no = "\"031502";  //学生学号，随机产生
	int tmp;
	string str;
	stringstream stream;
	int num;

	/*随机生成学号，变量stream用以将数字转成string字符串*/
	tmp = rand() % 599 + 100 + n;
	stream.clear();
	stream << tmp;
	stream >> str;
	str_no += str;


	if (out.is_open())
	{
		/*-1- 定制空闲时间*/
		/*限定每个人的空闲时间段数量在2-15个*/
		num = rand() % 14 + 2;
		temp.clear();
		Rand(42);
		std::random_shuffle(temp.begin(), temp.end());

		out << "        {" << endl << "            \"free_time\": [" << endl;
		for (int i = 0; i < num - 1; i++)
		{
			out << "                " << ft[temp[i]] << "," << endl;
		}
		out << "                " << ft[temp[num - 1]] << endl;
		out << "            " << "]," << endl;

		/*-2- 定制学生学号*/
		out << "            " << "\"student_no\": " << str_no << "\"," << endl;

		/*-3- 定制部门意愿*/
		out << "            " << "\"applications_department\": [" << endl;
		num = rand() % 5 + 1;
		temp.clear();
		Rand(20);
		std::random_shuffle(temp.begin(), temp.end());

		for (int i = 0; i < num - 1; i++)
		{
			stream.clear();
			stream << (temp[i] + 1);
			stream >> str;
			if (str.size() == 1)
			{
				str = "0" + str;
			}
			out << "                \"D0" << str << "\"," << endl;
		}
		out << "                \"D0" << str << "\"" << endl;
		out << endl;

		/*-4- 定制标签*/
		out << "            ]," << endl
			<< "            " << "\"tags\": [" << endl;

		/*每个人的标签数量在2~10个*/
		num = rand() % 9 + 2;
		temp.clear();
		Rand(20);
		std::random_shuffle(temp.begin(), temp.end());

		for (int i = 0; i<num; i++)
		{
			out << "                \"" << tags[temp[i]] << "\"," << endl;
		}
		out << "                \"" << tags[temp[num - 1]] << "\"" << endl;
		out << "            ]" << endl << "        }";
	}

	else
	{
		cout << "The file does not open!" << endl;
	}
}


/*定制部门库*/
void DataProduce::CreateDepartments(int n)
{
	//InitEventSchedules();
	//InitTags();
	string str_no = "\"D0";
	string str;
	stringstream stream;
	int num;

	/*定制生成部门编号，变量stream用以将数字转化成string字符串*/
	stream.clear();
	stream << n;
	stream >> str;
	if (str.size() == 1)
	{
		str = "0" + str;
	}
	str_no += str;


	if (out.is_open())
	{
		/*-1- 定制部门活动时间2-5个*/
		num = rand() % 4 + 2;
		temp.clear();
		Rand(42);
		std::random_shuffle(temp.begin(), temp.end());

		out << "        {" << endl << "            \"event_schedules\": [" << endl;
		for (int i = 0; i < num - 1; i++)
		{
			out << "                " << es[temp[i]] << "," << endl;
		}
		out << "                " << es[temp[num - 1]] << endl;
		out << "            " << "]," << endl;

		/*-2- 定制限定人数（10~15个）*/
		out << "            " << "\"member_limit\": " << rand() % 6 + 10 << "," << endl;

		/*-3- 定制部门编号*/
		out << "            " << "\"department_no\": " << str_no << "\"," << endl;

		/*-4- 定制标签*/
		out << "            " << "\"tags\": [" << endl;
		num = rand() % 3 + 2;
		temp.clear();
		Rand(20);
		std::random_shuffle(temp.begin(), temp.end());

		for (int i = 0; i < num - 1; i++)
		{
			out << "                \"" << tags[temp[i]] << "\"," << endl;
		}
		out << "                \"" << tags[temp[num - 1]] << "\"" << endl;

		out << "            ]" << endl << "        }";
	}

	else
	{
		cout << "The file does not open!" << endl;
	}
}
