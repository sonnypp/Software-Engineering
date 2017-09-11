// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sudokulib.h"

int main(int argc, char* argv[])
{
	if (strcmp(argv[1], "-c") != 0) {
		cout << "Please input the right data:number" << endl;
	}
	else {
		int len = strlen(argv[2]);
		bool str = true;
		for (int i = 0; i < len; i++) {
			if (argv[2][i] < '0' || argv[2][i] > '9') {
				str = false;
				break;
			}
		}
		if (str) {
			sudokulib sudoku;
			sudoku.get_num(argv[2]);
			sudoku.iosout.open("sudoku.txt");
			sudoku.backdate(0, 0);
			sudoku.iosout.close();
		}
		else {
			cout << "Please input the right data:number" << endl;
		}
		
	}
    return 0;
}

