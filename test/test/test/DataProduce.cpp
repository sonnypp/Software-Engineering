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
	/*-1- ��ʼ��ʱ���*/
	string date[7] =
	{
		"Sun.","Mon.","Tues.","Wen.","Thur.","Fri.","Sat."
	};
	string time[6] =
	{
		"10:30~11:30","12:30~13:30","16:30~17:30","18:00~19:30","20:00~21:00","21:30~22:30"
	};

	int k = 0;

	/*���ɿ���ʱ���*/
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			ft[k] = "\"" + date[i] + time[j] + "\"";
			es[k++] = "\"" + date[i] + time[j] + "\"";
		}
	}
	/*-2- ��ʼ����ǩ��*/
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
	/*��ȡ��������ӣ�����Ҫ��*/
	srand((unsigned)time(NULL));

	/*����ѧ����Ϣ����������ļ���*/
	if (out.is_open())
	{
		out << "{" << endl << "    \"students\": [" << endl;
	}
	/*�Ƿ�ɹ����ļ�*/
	else
	{
		cout << "The file does not open!" << endl;
	}

	for (int i = 0; i < num_stu; i++)
	{
		/*�����ӷ������������ɲ����ѧ������*/
		CreateStudents(i + 1);
		if (i < num_stu - 1) {
			out << "," << endl;
		}

	}

	/*���Ʋ�����Ϣ*/
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
		/*�����ӷ������������ɲ������������*/
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

/*����ѧ����*/
void DataProduce::CreateStudents(int n)
{
	//InitFreeTime();
	//InitTags();
	string str_no = "\"031502";  //ѧ��ѧ�ţ��������
	int tmp;
	string str;
	stringstream stream;
	int num;

	/*�������ѧ�ţ�����stream���Խ�����ת��string�ַ���*/
	tmp = rand() % 599 + 100 + n;
	stream.clear();
	stream << tmp;
	stream >> str;
	str_no += str;


	if (out.is_open())
	{
		/*-1- ���ƿ���ʱ��*/
		/*�޶�ÿ���˵Ŀ���ʱ���������2-15��*/
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

		/*-2- ����ѧ��ѧ��*/
		out << "            " << "\"student_no\": " << str_no << "\"," << endl;

		/*-3- ���Ʋ�����Ը*/
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

		/*-4- ���Ʊ�ǩ*/
		out << "            ]," << endl
			<< "            " << "\"tags\": [" << endl;

		/*ÿ���˵ı�ǩ������2~10��*/
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


/*���Ʋ��ſ�*/
void DataProduce::CreateDepartments(int n)
{
	//InitEventSchedules();
	//InitTags();
	string str_no = "\"D0";
	string str;
	stringstream stream;
	int num;

	/*�������ɲ��ű�ţ�����stream���Խ�����ת����string�ַ���*/
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
		/*-1- ���Ʋ��Żʱ��2-5��*/
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

		/*-2- �����޶�������10~15����*/
		out << "            " << "\"member_limit\": " << rand() % 6 + 10 << "," << endl;

		/*-3- ���Ʋ��ű��*/
		out << "            " << "\"department_no\": " << str_no << "\"," << endl;

		/*-4- ���Ʊ�ǩ*/
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
