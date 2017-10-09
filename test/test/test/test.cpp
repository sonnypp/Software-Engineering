// partment.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "json.h"
#include <fstream>
#include "function.h"
#include "match_program.h"
#include "match_algorithm.h"
#include "DataProduce.h"
using namespace std;
using namespace Json;

int main()
{

	//自动生成input_data.txt文件
	//DataProduce data;
	//data.ToGenerate();


	//计算权值
	match_algorithm test;
	data_output();   //调用function.h中data_output（）函数将txt文件中的json数据存入到结构体中

	for (int i = 0; i < stu_num; i++) {
		for (int j = 0; j < stu[i].appli_dep_num; j++) {
			for (int k = 0; k < dep_num; k++) {
				if (dep[k].department_no == stu[i].applications_department[j]) {
					rank_value[i][k] = test.match_algorithm_rank(stu[i], dep[k], j + 1);
					//cout << rank_value[i][k] << endl;
				}
			}
		}
	}
	match_program match;
	match.match_algorithm();
	data_input();
	return 0;

}

