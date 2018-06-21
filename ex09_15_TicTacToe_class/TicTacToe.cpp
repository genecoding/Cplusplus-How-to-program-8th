#include "TicTacToe.h"
#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;

TicTacToe::TicTacToe(void)
{
	reset();
}

TicTacToe::~TicTacToe(void)
{
}

void TicTacToe::reset()
{
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			board[i][j] = 0;
	
	for(int i = 0; i < 8; i++)
		p1Occupied[i] = 0;
}

void TicTacToe::playWithMan()
{
	int counter = 0;
	Gamer player = player1;
	Result result = draw;  

	do{
		placeMark(player);
		counter++;
		display();
		result = judgeGame(player);
		player = (player == player1) ? player2 : player1;  //change player
	} while(counter < 9 && result == draw);  //draw = no one win yet.

	showResult(player2, result);  //player2 = play with human.
}

void TicTacToe::playWithCom()
{
	int counter = 0;
	Gamer player = player1;
	Result result = draw;

	do{
		if(player == player1)
			placeMark(player);
		else {  //play by computer
			if(counter == 1)
				firstMove();
			else
				afterwardMove();

			Sleep(500);  //give a pause to show com's move.
		}
		counter++;
		display();
		result = judgeGame(player);
		player = (player == player1) ? computer : player1;  //change player
	} while(counter < 9 && result == draw);  //draw = no one win yet.

	showResult(computer, result);  //play with computer.
}

void TicTacToe::firstMove()
{  //There are only 3 patterns of p1's first move: center, corner or edge, 
   //and the computer should just respond to it accordingly.
	if(p1TakesCorner())
		board[1][1] = 2;  //computer should take center.
	else  //p1 takes center or edge
		toTakeCorner();  //computer should take corner.
}

void TicTacToe::afterwardMove()
{  //respond as following order.
	if(toWin())
		;
	else if(toBlock())
		;
	else if(toFork())  //make self two in a line to win.
		;
	else {  //when come to here, the game is draw.
		if(takeEmptyCorner())
			;
		else
			takeEmptySide();
	}
}

bool TicTacToe::toWin()
{
	int xx, yy;
	for(int i = 0; i < 8; i++) {
		if(p1Occupied[i] == false) {  //there is no player1 mark in the line
			if(isTwoInLine(2, i, xx, yy, &TicTacToe::isPlaceFree)) {  //there are already two com marks in the line
				board[yy][xx] = 2;
				return true;
			}
		}
	}

	return false;
}

bool TicTacToe::toBlock()
{
	int xx, yy;
	for(int i = 0; i < 8; i++) {
		if(p1Occupied[i]) {  //there is (at least one) player1 mark in the line
			if(isTwoInLine(1, i, xx, yy, &TicTacToe::isPlaceFree)) {  //there are already two player1 marks in the line
				board[yy][xx] = 2;
				return true;
			}
		}
	}

	return false;
}

bool TicTacToe::toFork()
{
	int xx, yy;
	int col;
	for(int i = 0; i < 8; i++) {
		col = i-3;
		if(p1Occupied[i] == false) {  //there is no player1 mark in the line
			if(isTwoInLine(0, i, xx, yy, &TicTacToe::isPlaceByCom)) {  //there are one computer marks and two blanks in the line
				switch(i) {
				case 0:
				case 1:
				case 2:
					for(int j = 0; j < 3; j++) {
						if(j != xx && isPlaceFree(j, i)) {
							board[i][j] = 2;
							return true;
						}
					}
					break;
				case 3:
				case 4:
				case 5:
					for(int j = 0; j < 3; j++) {
						if(j != yy && isPlaceFree(col, j)) {
							board[j][col] = 2;
							return true;
						}
					}
					break;
				case 6:  //diagonal \.
					for(int j = 0; j < 3; j++) {
						if(j != xx && j != yy && isPlaceFree(j, j)) {
							board[j][j] = 2;
							return true;
						}
					}
					break;
				case 7:  //anti diagonal
					for(int j = 0, k =3; j < 3, k > 0; j++, k--) {
						if(j != xx && k != yy && isPlaceFree(j, k)) {
							board[j][k] = 2;
							return true;
						}
					}
					break;
				}  //end switch
			}
		}
	}  //end for

	return false;
}

bool TicTacToe::isTwoInLine(int symbol, int lineNo, int &xx, int &yy, Check_pfn checkTheLast)
{  //check if there are two symbols in the assigned line.
   //lineNo from 0~8, which are r1-r3, cl-c3, diagonal, anti diagonal
	int p = symbol;  //1 = player1, 2 = computer, 0 = blank.
	int col = lineNo-3;

	switch(lineNo) {
	case 0:
	case 1:
	case 2:
		if(board[lineNo][0] == p && board[lineNo][1] == p && (this->*checkTheLast)(2, lineNo)) {
			xx = 2;
			yy = lineNo;
			return true;
		} else if(board[lineNo][1] == p && board[lineNo][2] == p && (this->*checkTheLast)(0, lineNo)) {
			xx = 0;
			yy = lineNo;
			return true;
		} else if(board[lineNo][0] == p && board[lineNo][2] == p && (this->*checkTheLast)(1, lineNo)) {
			xx = 1;
			yy = lineNo;
			return true;
		} else {
			xx = -1;
			yy = -1;
			return false;
		}
		break;
	case 3:
	case 4:
	case 5:
		if(board[0][col] == p && board[1][col] == p && (this->*checkTheLast)(col, 2)) {
			xx = col;
			yy = 2;
			return true;
		} else if(board[1][col] == p && board[2][col] == p && (this->*checkTheLast)(col, 0)) {
			xx = col;
			yy = 0;
			return true;
		} else if(board[0][col] == p && board[2][col] == p && (this->*checkTheLast)(col, 1)) {
			xx = col;
			yy = 1;
			return true;
		} else {
			xx = -1;
			yy = -1;
			return false;
		}
		break;
	case 6:  //check diagonal \.
		if(board[0][0] == p && board[1][1] == p && (this->*checkTheLast)(2, 2)) {
			xx = 2;
			yy = 2;
			return true;
		} else if(board[1][1] == p && board[2][2] == p && (this->*checkTheLast)(0, 0)) {
			xx = 0;
			yy = 0;
			return true;
		} else if(board[0][0] == p && board[2][2] == p && (this->*checkTheLast)(1, 1)) {
			xx = 1;
			yy = 1;
			return true;
		} else {
			xx = -1;
			yy = -1;
			return false;
		}
		break;
	case 7:  //check anti diagonal /
		if(board[0][2] == p && board[1][1] == p && (this->*checkTheLast)(0, 2)) {
			xx = 0;
			yy = 2;
			return true;
		} else if(board[1][1] == p && board[2][0] == p && (this->*checkTheLast)(2, 0)) {
			xx = 2;
			yy = 0;
			return true;
		} else if(board[0][2] == p && board[2][0] == p && (this->*checkTheLast)(1, 1)) {
			xx = 1;
			yy = 1;
			return true;
		} else {
			xx = -1;
			yy = -1;
			return false;
		}
		break;
	}  //end switch
}

bool TicTacToe::takeEmptyCorner()
{
	if(isPlaceFree(0, 0)) {
		board[0][0] = 2;
		return true;
	} else if(isPlaceFree(2, 0)) {
		board[0][2] = 2;
		return true;
	} else if(isPlaceFree(0, 2)) {
		board[2][0] = 2;
		return true;
	} else if(isPlaceFree(2, 2)) {
		board[2][2] = 2;
		return true;
	}
	else
		return false;
}

bool TicTacToe::takeEmptySide()
{
	if(isPlaceFree(0, 1)) {
		board[1][0] = 2;
		return true;
	} else if(isPlaceFree(1, 0)) {
		board[0][1] = 2;
		return true;
	} else if(isPlaceFree(1, 2)) {
		board[2][1] = 2;
		return true;
	} else if(isPlaceFree(2, 1)) {
		board[1][2] = 2;
		return true;
	} else
		return false;
}

void TicTacToe::toTakeCorner()
{
	int n = rand() % 4;
	switch(n) {
	case 0:
		board[0][0] = 2;
		break;
	case 1:
		board[2][0] = 2;
		break;
	case 2:
		board[0][2] = 2;
		break;
	case 3:
		board[2][2] = 2;
		break;
	}
}

void TicTacToe::placeMark(Gamer player)
{
	int xx, yy;
	bool isValidMove = false;
	int p = (player == player1) ? 1 : 2;  //player1 = 1, player2 = 2. 

	do{
		do{
			cout << printPlayer(player) << ": ";
			cin >> xx >> yy;

			if((xx < 1 || xx > 3) || (yy < 1 || yy > 3))  //check it's inside the 3x3 board.
				cout << "Invalid input, enter again!" << endl;
		} while((xx < 1 || xx > 3) || (yy < 1 || yy > 3));

		if(!(isValidMove = isPlaceFree(xx-1, yy-1)))  //check the place is not taken.
			cout << "Invalid input, enter again!" << endl;
	} while(!isValidMove);

	if(player == player1)
		p1OccupiedLines(xx-1, yy-1);  //used for playWithCom();

	board[yy-1][xx-1] = p;
}

void TicTacToe::p1OccupiedLines(int xx, int yy)
{
	p1Occupied[yy] = 1;  //occupy row;
	p1Occupied[xx+3] = 1;  //occupy col;

	if((yy == 0 && xx == 0) || (yy == 1 && xx == 1) || (yy == 2 && xx == 2))  //occupy diagonal 
		p1Occupied[6] = 1;

	if((yy == 2 && xx == 0) || (yy == 1 && xx == 1) || (yy == 0 && xx == 2))  //occupy anti-diagonal 
		p1Occupied[7] = 1;
}

Result TicTacToe::judgeGame(Gamer player)
{
	int p = (player == player1) ? 1 : 2;  //player1 = 1, player2/computer = 2.

	for(int i = 0; i < 3; i++) {
		if(board[i][0] == p && board[i][1] == p && board[i][2] == p)  //check vertical line
			return static_cast<Result>(p);
		if(board[0][i] == p && board[1][i] == p && board[2][i] == p)  //check horizontal line
			return static_cast<Result>(p);
	}

	//check diagonal line
	if((board[0][0] == p && board[1][1] == p && board[2][2] == p) 
		|| (board[2][0] == p && board[1][1] == p && board[0][2] == p))
		return static_cast<Result>(p);

	return draw;
}

void TicTacToe::showResult(Gamer player, Result result)
{
	switch(result) {
	case p1Win:
		cout << "Player 1 WINS!" << endl;
		break;
	case p2Win:
		if(player == computer)
			cout << "COMPUTER WINS!" << endl;
		else
			cout << "Player 2 WINS!" << endl;
		break;
	case draw:
		cout << "DRAW!" << endl;
		break;
	}
}

string TicTacToe::printPlayer(Gamer player)
{
	if(player == player1)
		return "Player 1";
	else if(player == player2)
		return "Player 2";
	else if(player == computer)
		return "Computer";
}

void TicTacToe::display()
{
	int boardCtr = 0;
	for(int row = 0; row < GRID_ROW; row++) {
		for(int col = 0; col < GRID_COL; col++) {
			if(row%2 == 0 && col%4 == 1)  //print symbols
				cout << board[0][boardCtr++];
			else
				cout << GRID[row][col];
		}
		cout << endl;
	}
	cout << endl;
}