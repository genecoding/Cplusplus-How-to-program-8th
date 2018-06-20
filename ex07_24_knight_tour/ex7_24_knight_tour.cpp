#include <iostream>
#include <ctime>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

const int horizontal[8] = { 2,  1, -1, -2, -2, -1, 1, 2};
const int vertical[8]   = {-1, -2, -2, -1,  1,  2, 2, 1};
const int accessibility[8][8] = { {2, 3, 4, 4, 4, 4, 3, 2},
								  {3, 4, 6, 6, 6, 6, 4, 3},
								  {4, 6, 8, 8, 8, 8, 6, 4},
								  {4, 6, 8, 8, 8, 8, 6, 4},
								  {4, 6, 8, 8, 8, 8, 6, 4},
								  {4, 6, 8, 8, 8, 8, 6, 4},
								  {3, 4, 6, 6, 6, 6, 4, 3},
								  {2, 3, 4, 4, 4, 4, 3, 2} };

void knightTour(int board[][8], int currentRow, int currentCol);
bool isValidStep(int board[][8], int row, int col);
void printBoard(int board[][8]);
void resetBoard(int board[][8]);
int randNum(bool reset);

// ex7.24c
void knightTourWithAccess(int board[][8], int currentRow, int currentCol);
void copyAccess(int copy[][8]);
int findLowestValidAccess(int access[][8], int currentRow, int currentCol);
bool isValidAccess(int access[][8], int row, int col);
void updateAccess(int access[][8], int row, int col);

int main()
{
	int board[8][8] = {0};
	srand(time(0));

	//test, starting from every square
	for(int col = 6; col < 8; col++) {
		for(int row = 0; row < 8; row++) {
			//knightTour(board, row, col);
			knightTourWithAccess(board, row, col);			
			resetBoard(board);
		}
	}

	return 0;
}

void knightTour(int board[][8], int currentRow, int currentCol)
{
	int moveNum;  //0~7, there are 8 possible moves knight can take.
	int counter = 1;
	bool noWayToGo = false;
	int newRow, newCol;
	
	board[currentRow][currentCol] = counter++;

	do {
		moveNum = randNum(true);
		while (moveNum != -1) {
			newRow = currentRow + horizontal[moveNum];
			newCol = currentCol + vertical[moveNum];
			if(isValidStep(board, newRow, newCol)) {
				currentRow = newRow;
				currentCol = newCol;
				board[currentRow][currentCol] = counter++;
				break;
			} else
				moveNum = randNum(false);
		}

		if(moveNum == -1)
			noWayToGo = true;

	} while(!noWayToGo);

	printBoard(board);
	cout << "final move: " << counter-1 << endl << endl;
}

bool isValidStep(int board[][8], int row, int col)
{
	if(row > 7 || row < 0)
		return false;
	if(col > 7 || col < 0)
		return false;
	if(board[row][col] != 0)
		return false;

	return true;
}

void printBoard(int board[][8])
{
	for(int col = 0; col < 8; col++) {
		for(int row = 0; row < 8; row++)
			cout << std::setw(3) << board[row][col];

		cout << endl;
	}
}

void resetBoard(int board[][8])
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			board[i][j] = 0;
}

int randNum(bool reset)
{  //generate a random number in a range without repeat.
	static bool repeat[8] = {0};
	int n;
	int counter = 0;
	int tryTimes = 8 * 100;

	if(reset) {
		for(int i = 0; i < 8; i++)
			repeat[i] = false;
	}

	while(counter < tryTimes) {
		n = rand() % 8;
		if(repeat[n] == false) {
			repeat[n] = true;
			return n;
		} 
		counter++;
	}

	return -1;  //all numbers in the range have been used.
}

void knightTourWithAccess(int board[][8], int currentRow, int currentCol)
{
	int moveNum;  //0~7, there are 8 possible moves knight can take.
	int counter = 1;
	bool noWayToGo = false;
	int access[8][8];

	copyAccess(access);

	do {
		updateAccess(access, currentRow, currentCol);
		board[currentRow][currentCol] = counter++;

		moveNum = findLowestValidAccess(access, currentRow, currentCol);
		if(moveNum != -1) {
			currentRow += horizontal[moveNum];
			currentCol += vertical[moveNum];
		} else
			noWayToGo = true;

	} while(!noWayToGo);

	printBoard(board);
	cout << "final move: " << counter-1 << endl << endl;
}

void copyAccess(int copy[][8])
{
	for(int col = 0; col < 8; col++)
		for(int row = 0; row < 8; row++)
			copy[row][col] = accessibility[row][col];
}

int findLowestValidAccess(int access[][8], int currentRow, int currentCol)
{
	int lowestAccessibility = 9;  //valid largest accessibility is 8.
	int lowestAccessMove = -1;  //valid move is 0~7
	int newRow, newCol;

	for(int move = 0; move < 8; move++) {  //check all possible moves
		newRow = currentRow + horizontal[move];
		newCol = currentCol + vertical[move];
		if(isValidAccess(access, newRow, newCol)) {
			if(access[newRow][newCol] < lowestAccessibility) {  //and take the move of lowest accessibility.
				lowestAccessibility = access[newRow][newCol];
				lowestAccessMove = move;
			}
		}
	}
	
	return lowestAccessMove;
}

bool isValidAccess(int access[][8], int row, int col)
{
	if(row < 0 || row > 7)
		return false;
	if(col < 0 || col > 7)
		return false;
	if(access[row][col] == -1)
		return false;

	return true;
}

void updateAccess(int access[][8], int row, int col)
{
	access[row][col] = -1;  //it should be -1, not 0, for the last move.

	int newRow, newCol;
	for(int move = 0; move < 8; move++) {  //update accessibility related to this square(move).
		newRow = row + horizontal[move];
		newCol = col + vertical[move];
		if(isValidAccess(access, newRow, newCol))
			access[newRow][newCol]--;
	}
}