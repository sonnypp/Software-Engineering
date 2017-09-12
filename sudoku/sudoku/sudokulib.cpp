#include "stdafx.h"
#include "sudokulib.h"


sudokulib::sudokulib()
{
	memset(sudoku_tmp, 0, sizeof(sudoku_tmp));
	memset(flag, false, sizeof(flag));
	memset(row_mark, 0, sizeof(row_mark));
	memset(col_mark, 0, sizeof(col_mark));
	memset(J_Gong_mark, 0, sizeof(J_Gong_mark));
	sudoku_tmp[0][0] = 5;   // 因为学号后俩位为31   故第一个数为5
	cnt = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (sudoku_tmp[i][j]) {
				if (sudoku_tmp[i][j]) {
					flag[i][j] = true; sudoku_tmp[i][j]--;  //下标从0-8 
					row_mark[i][sudoku_tmp[i][j]] = 1;   //该行中该数字存在 
					col_mark[j][sudoku_tmp[i][j]] = 1;   //该列中该数字存在 
					J_Gong_mark[3 * (i / 3) + (j / 3)][sudoku_tmp[i][j]] = 1; //该小九宫格中该数字存在   其中3*(i/3)+j/3表示小九宫格的位置 
				}
				else {
					flag[i][j] = false, sudoku_tmp[i][j] = -1;
				}
			}
		}
	}
}
//输入一个数字    即打印几种解法
void sudokulib::get_num(char* str) {
	int len = strlen(str);
	int res = 0, tmp = 1;
	for (int i = len-1; i >= 0 ; i--) {
		res += (str[i] - '0')*tmp;
		tmp *= 10;
	}
	N = res;
}


//打印数独棋盘
void sudokulib::print() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			iosout << sudoku_tmp[i][j] + 1 << " ";
		}
		iosout << endl;
	}
	iosout << endl ;
	return;
}


//进行回溯 加 遍历
void sudokulib::backdate(int x, int y) {
	if (y == 9) x++, y = 0;
	while (flag[x][y] && x <= 8) {
		y++;
		if (y == 9) {
			x++, y = 0;
		}
	}
	if (x > 8) {
		print();
		if (++cnt == N) {
			exit(-1);
		}
	}
	while ((sudoku_tmp[x][y] = get_next_num(x, y, sudoku_tmp[x][y] + 1)) != -1) {
		row_mark[x][sudoku_tmp[x][y]] = 1;
		col_mark[y][sudoku_tmp[x][y]] = 1;
		J_Gong_mark[3 * (x / 3) + (y / 3)][sudoku_tmp[x][y]] = 1;   //说明该数字可以用 
		backdate(x, y + 1);
		row_mark[x][sudoku_tmp[x][y]] = 0;
		col_mark[y][sudoku_tmp[x][y]] = 0;
		J_Gong_mark[3 * (x / 3) + (y / 3)][sudoku_tmp[x][y]] = 0;   //说明该数字不能用  还原到前一个状态 
	}
}

//获取下一个位置可用数字
int sudokulib::get_next_num(int x, int y, int s) {

	for (int i = s; i < 9; i++)
		if (!row_mark[x][i] && !col_mark[y][i] && !J_Gong_mark[3 * (x / 3) + (y / 3)][i]) return i;    //判断数字在该行 该列或者该小九宫格中是否存在 
	return -1;
}

sudokulib::~sudokulib()
{
}
