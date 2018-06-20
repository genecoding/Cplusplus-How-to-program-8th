#include <iostream>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void eightQueens(int board[][8], int startRow, int startCol);
void updateTaken(bool taken[][8], int row, int col);
void findValidLowestElimination(bool taken[][8], int &nextRow, int &nextCol);
bool isAllBlocksTaken(bool taken[][8]);
void printBoard(int board[][8]);
void resetBoard(int board[][8]);

const int ELIMINATION[8][8] = { {22, 22, 22, 22, 22, 22, 22, 22},
								{22, 24, 24, 24, 24, 24, 24, 22},
								{22, 24, 26, 26, 26, 26, 24, 22},
								{22, 24, 26, 28, 28, 26, 24, 22},
								{22, 24, 26, 28, 28, 26, 24, 22},
								{22, 24, 26, 26, 26, 26, 24, 22},
								{22, 24, 24, 24, 24, 24, 24, 22},
								{22, 22, 22, 22, 22, 22, 22, 22} };

int main()
{
	int board[8][8] = {0};

	//test, starting from every square
	for(int col = 0; col < 8; col++) {
		for(int row = 0; row < 8; row++) {
			eightQueens(board, row, col);
			resetBoard(board);
		}
	}

	return 0;
}

void eightQueens(int board[][8], int startRow, int startCol)
{
	bool taken[8][8] = {0};
	int counter = 1;
	bool noWayToMove = false;
	int nextRow, nextCol;

	board[startRow][startCol] = counter++;
	updateTaken(taken, startRow, startCol);

	do {
		findValidLowestElimination(taken, nextRow, nextCol);
		updateTaken(taken, nextRow, nextCol);
		board[nextRow][nextCol] = counter++;
	} while(!isAllBlocksTaken(taken));

	printBoard(board);
	cout << "final move: " << counter-1 << endl << endl;
}

void updateTaken(bool taken[][8], int row, int col)
{
	for(int i = 0; i < 8; i++) {
		taken[i][col] = true;  //take the same row
		taken[row][i] = true;  //take the same col
	}

	//take the cross(x)
	int diagStartX, diagStartY;  //diagonal, top left to bottom right
	int cDiagStartX, cDiagStartY;  //counter diagonal
	diagStartX = row - std::min(row, col);
	diagStartY = col - std::min(row, col);
	cDiagStartX = (row+col <= 7) ? row + col : 7;
	cDiagStartY = (row+col <= 7) ? 0 : col - (7-row);

	for(int i = diagStartX, j = diagStartY; i < 8 && j < 8; i++, j++)
		taken[i][j] = true;  //take the diagonal

	for(int i = cDiagStartX, j = cDiagStartY; i > 0 && j < 8; i--, j++)
		taken[i][j] = true;  //take the counter diagonal
}

void findValidLowestElimination(bool taken[][8], int &nextRow, int &nextCol)
{
	int minElim = 30;  //largest valid elimination is 28.
	int minElimRow = -1;
	int minElimCol = -1;

	for(int col = 0; col < 8; col++) {
		for(int row = 0; row < 8; row++) {
			if(ELIMINATION[row][col] < minElim && !taken[row][col]) {  //find the lowest elimination.
				minElim = ELIMINATION[row][col];
				minElimRow = row;
				minElimCol = col;
			}
		}
	}

	if(minElimRow != -1 && minElimCol != -1) {
		nextRow = minElimRow; 
		nextCol = minElimCol;
	} else
		cerr << "error!";
}

bool isAllBlocksTaken(bool taken[][8])
{
	for(int col = 0; col < 8; col++) {
		for(int row = 0; row < 8; row++)
			if(!taken[row][col])
				return false;
	}

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
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++)
			board[j][i] = 0;
	}
}