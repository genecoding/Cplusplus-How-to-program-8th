#include <iostream>
#include <iomanip>
#include <Windows.h>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

enum Direction {N = 0, E, S, W};
enum Heading {right, straight, left, back};
const int ROW_SIZE = 12;
const int COL_SIZE = 12;
const char maze[ROW_SIZE][COL_SIZE] = {{'#','#','#','#','#','#','#','#','#','#','#','#'},
										 {'#','.','.','.','#','.','.','.','.','.','.','#'},
										 {'.','.','#','.','#','.','#','#','#','#','.','#'},
										 {'#','#','#','.','#','.','.','.','.','#','.','#'},
										 {'#','.','.','.','.','#','#','#','.','#','.','.'},
										 {'#','#','#','#','.','#','.','#','.','#','.','#'},
										 {'#','.','.','#','.','#','.','#','.','#','.','#'},
										 {'#','#','.','#','.','#','.','#','.','#','.','#'},
										 {'#','.','.','.','.','.','.','.','.','#','.','#'},
										 {'#','#','#','#','#','#','.','#','#','#','.','#'},
										 {'#','.','.','.','.','.','.','#','.','.','.','#'},
										 {'#','#','#','#','#','#','#','#','#','#','#','#'} };

void mazeTraverse(const char maze[][COL_SIZE], int startX, int startY, Direction dir = N);
void nextMove(int currentX, int currentY, int &nextX, int &nextY, Direction currentDir, Direction &nextDir, Heading go);
bool isValidMove(const char maze[][COL_SIZE], int nextX, int nextY);
void drawMaze(const char maze[][COL_SIZE], int currentRow = 0, int currentCol = 0);

int main()
{
	mazeTraverse(maze, 2, 0);

	return 0;
}

void mazeTraverse(const char maze[][COL_SIZE], int startX, int startY, Direction dir)
{
	int nextX, nextY;
	Direction nextDir;
	Heading go = right;

	//print traverse step by step
	system("CLS");  //clear terminal screen.
	drawMaze(maze, startX, startY);
	cout << endl;
	Sleep(500);  //give a pause to display.
	
	do {  //find way from right first, then straight, left, or back
		nextMove(startX, startY, nextX, nextY, dir, nextDir, go);
		if(isValidMove(maze, nextX, nextY))  //not a wall
			break;
		else
			go = static_cast<Heading>(go + 1);
	} while(1);
	
	if((nextX < 0 || nextX > ROW_SIZE-1) || (nextY < 0 || nextY > COL_SIZE-1))  //next move outside the maze, so now should be at the exit.
		return;
	else
		mazeTraverse(maze, nextX, nextY, nextDir);
}

void nextMove(int currentX, int currentY, int &nextX, int &nextY, Direction currentDir, Direction &nextDir, Heading go)
{
	switch(go) {
	case straight:
		nextDir = currentDir;
		break;
	case right:
		nextDir = static_cast<Direction>((currentDir + 1) % 4);
		break;	
	case back:
		nextDir = static_cast<Direction>((currentDir + 2) % 4);
		break;
	case left:
		nextDir = static_cast<Direction>((currentDir + 3) % 4);
		break;
	default:
		cerr << "Error 01!";
		break;
	}

	switch(nextDir) {
	case N:
		nextX = currentX - 1;
		nextY = currentY;
		break;
	case E:
		nextX = currentX;
		nextY = currentY + 1;
		break;
	case S:
		nextX = currentX + 1;
		nextY = currentY;
		break;
	case W:
		nextX = currentX;
		nextY = currentY - 1;
		break;
	default:
		cerr << "Error 02!";
		break;
	}
}

bool isValidMove(const char maze[][COL_SIZE], int nextX, int nextY)
{
	if((nextX >= 0 && nextX <= ROW_SIZE-1) && (nextY >= 0 && nextY <= COL_SIZE-1)) {
		if(maze[nextX][nextY] == '#')
			return false;
	}

	return true;  //inside the maze and not a wall, or outside the maze(at exit).
}

void drawMaze(const char maze[][COL_SIZE], int currentRow, int currentCol)
{
	for(int row = 0; row < 12; row++) {
		for(int col = 0; col < 12; col++) {
			if(row == currentRow && col == currentCol)
				cout << std::setw(2) << 'x';
			else
				cout << std::setw(2) << maze[row][col];
		}
		cout << endl;
	}
}