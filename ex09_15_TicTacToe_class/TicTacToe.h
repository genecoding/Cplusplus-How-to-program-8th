#pragma once
#include <string>
using std::string;

const int GRID_ROW = 5;
const int GRID_COL = 11;
const char GRID[GRID_ROW][GRID_COL] = 
{{' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' '},
 {'-', '-', '-', '+', '-', '-', '-', '+', '-', '-', '-'},
 {' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' '},
 {'-', '-', '-', '+', '-', '-', '-', '+', '-', '-', '-'},
 {' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' '}};
enum Gamer {player1, player2, computer};
enum Result {draw, p1Win, p2Win};

class TicTacToe
{
public:
	TicTacToe(void);
	~TicTacToe(void);
	void setSymbol1(char s1 = '1')
	{
		symb1 = s1;
	}
	void setSymbol2(char s2 = '2')
	{
		symb2 = s2;
	}
	void reset();
	void playWithMan();
	void playWithCom();
	void display();
private:
	int board[3][3];
	char symb1, symb2;
	bool p1Occupied[8];  //lines occupied by p1, 0~8 correspond to r1r2r3(up to down), clc2c3(left to right), d1d2(diagonal \ & anti diagonal /)
	typedef bool (TicTacToe::*Check_pfn)(int, int);
	void placeMark(Gamer player);
	bool isPlaceFree(int xx, int yy)
	{
		return board[yy][xx] == 0;
	}
	bool isPlaceByCom(int xx, int yy)
	{
		return board[yy][xx] == 2;
	}
	Result judgeGame(Gamer player);
	void showResult(Gamer player, Result result);
	string printPlayer(Gamer player);
	void firstMove();
	void afterwardMove();
	bool p1TakesCorner()
	{
		return board[0][0] || board[2][0] || board[0][2] || board[2][2];
	}
	void toTakeCorner();
	void p1OccupiedLines(int xx, int yy);
	bool toWin();
	bool toBlock();
	bool toFork();
	bool takeEmptyCorner();
	bool takeEmptySide();
	bool isTwoInLine(int symbol, int lineNo, int &xx, int &yy, Check_pfn checker);
};

