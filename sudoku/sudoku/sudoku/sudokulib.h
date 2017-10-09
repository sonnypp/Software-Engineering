#pragma once
const int MAX_SIZE = 15;
class sudokulib
{
private:
	int N;
	int cnt;
	int sudoku_tmp[MAX_SIZE][MAX_SIZE];
	int row_mark[MAX_SIZE][9];
	int col_mark[MAX_SIZE][9];
	int J_Gong_mark[MAX_SIZE][9];
	bool flag[MAX_SIZE][MAX_SIZE];
public:
	ofstream iosout;
	sudokulib();
	~sudokulib();
	void get_num(char* str);
	int get_next_num(int x, int y, int s);
	void backdate(int x, int y);
	void print();

};

