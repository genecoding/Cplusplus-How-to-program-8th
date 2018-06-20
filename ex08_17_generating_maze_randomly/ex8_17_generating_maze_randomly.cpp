#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

const int ROW_SIZE = 12;
const int COL_SIZE = 12;

//maze traversal
enum Direction {N = 0, E, S, W};
enum Heading {right, straight, left, back};
void mazeTraverse(const char maze[][COL_SIZE], int startX, int startY);
void goMazeTraverse(const char maze[][COL_SIZE], int startX, int startY, Direction dir);
void nextMove(int currentX, int currentY, int &nextX, int &nextY, Direction currentDir, Direction &nextDir, Heading go);
bool isValidMove(const char maze[][COL_SIZE], int nextX, int nextY);
void drawMaze(const char maze[][COL_SIZE], int currentRow = 0, int currentCol = 0);

//generate maze
void genMazeRand(char maze[][COL_SIZE], int &enterRow, int &enterCol);
bool selectAWall(char maze[][COL_SIZE], int currentRow, int currentCol, int &wallRow, int &wallCol);
bool isAWall(char maze[][COL_SIZE], int row, int col);
bool isOuterWall(int row, int col);
void selectAOuterWall(int &row, int &col);
void repairOuterWall(char maze[][COL_SIZE], int enterRow, int enterCol, int exitRow, int exitCol);
void setMesh(char maze[][COL_SIZE]);

/*************
wall order
  0
3   1
  2
*************/

int main()
{
	srand(time(0));
	char maze[ROW_SIZE][COL_SIZE];
	int enterRow, enterCol;

	genMazeRand(maze, enterRow, enterCol);
	mazeTraverse(maze, enterRow, enterCol);

	return 0;
}

void genMazeRand(char maze[][COL_SIZE], int &enterRow, int &enterCol)
{
	int exitRow, exitCol;
	int wallRow, wallCol;
	int noWallToErase = false;

	setMesh(maze);
	
	//traversal all blanks(holes) of the mesh and erase one of enclosing walls randomly for each blank,
	//do not erase outer wall.
	for(int row = 1; row < ROW_SIZE; row += 2) {
		for(int col = 1; col < COL_SIZE; col += 2) {
			if(maze[row][col] == '.') {
				noWallToErase = selectAWall(maze, row, col, wallRow, wallCol);

				if(!noWallToErase)
					maze[wallRow][wallCol] = '.';
			}
		}
	}

	//set an entrance and an exit, and make entrance and exit different
	selectAOuterWall(enterRow, enterCol);
	do {
		selectAOuterWall(exitRow, exitCol);
	} while(enterRow == exitRow && enterCol == exitCol);
	maze[enterRow][enterCol] = '.';
	maze[exitRow][exitCol] = '.';

	//if wall size is even, repair the outer wall except for entrance and exit.
	repairOuterWall(maze, enterRow, enterCol, exitRow, exitCol);

	drawMaze(maze, enterRow, enterCol);
}

bool selectAWall(char maze[][COL_SIZE], int currentRow, int currentCol, int &wallRow, int &wallCol)
{
	int dir;
	bool fourWalls[4] = {0};

	do{
		dir = rand() % 4;

		//checked all enclosing walls and there is no wall to erase.
		if(fourWalls[0] && fourWalls[1] && fourWalls[2] && fourWalls[3]) {
			wallRow = wallCol = -1;
			return true;
		}

		if(dir == 0) {
			wallRow = currentRow -1;
			wallCol = currentCol;
			fourWalls[0] = true;
		} else if(dir == 1) {
			wallRow = currentRow;
			wallCol = currentCol +1;
			fourWalls[1] = true;
		} else if(dir == 2) {
			wallRow = currentRow +1;
			wallCol = currentCol;
			fourWalls[2] = true;
		} else {//dir == 3
			wallRow = currentRow;
			wallCol = currentCol -1;
			fourWalls[3] = true;
		}

	} while(isOuterWall(wallRow, wallCol) || !isAWall(maze, wallRow, wallCol));  //it's should be a wall and not a outer wall.

	return false;
}

bool isAWall(char maze[][COL_SIZE], int row, int col)
{
	if(maze[row][col] == '#')
		return true;
	else
		return false;
}

bool isOuterWall(int row, int col)
{
	if(row == 0 || row >= ROW_SIZE-1 || col == 0 || col >= COL_SIZE-1)
		return true;

	return false;
}

void selectAOuterWall(int &row, int &col)
{
	int dir = rand() % 4;
	int col_size = (COL_SIZE % 2 == 0) ? COL_SIZE-1 : COL_SIZE;  //avoid corner when COL_SIZE is even.
	int row_size = (ROW_SIZE % 2 == 0) ? ROW_SIZE-1 : ROW_SIZE;  //avoid corner when ROW_SIZE is even.

	switch(dir) {
	case 0:
		row = 0;
		col = ((rand() % (col_size/2)) * 2) + 1;  //avoid corner & wall
		break;
	case 1:
		row = ((rand() % (row_size/2)) * 2) + 1;  //avoid corner & wall
		col = COL_SIZE -1;
		break;
	case 2:
		row = ROW_SIZE -1;
		col = ((rand() % (col_size/2)) * 2) + 1;  //avoid corner & wall
		break;
	case 3:
		row = ((rand() % (row_size/2)) * 2) + 1;  //avoid corner & wall
		col = 0;
		break;
	default:
		cerr << "Error @selectOuterWallPoint.";
		break;
	}
}

void repairOuterWall(char maze[][COL_SIZE], int enterRow, int enterCol, int exitRow, int exitCol)
{
	//if row size is even, repair the bottom wall
	if(ROW_SIZE % 2 == 0) {
		for(int col = 0; col < COL_SIZE; col++) {
			if((ROW_SIZE-1 == enterRow && col == enterCol) || (ROW_SIZE-1 == exitRow && col == exitCol))
				continue;
			else
				maze[ROW_SIZE-1][col] = '#';
		}
	}

	//if col size is even, repair the rightmost wall
	if(COL_SIZE % 2 == 0) {
		for(int row = 0; row < ROW_SIZE; row++) {
			if((COL_SIZE-1 == enterCol && row == enterRow) || (COL_SIZE-1 == exitCol && row == exitRow))
				continue;
			else
				maze[row][COL_SIZE-1] = '#';
		}
	}

}

void setMesh(char maze[][COL_SIZE])
{
	for(int row = 0; row < ROW_SIZE; row++) {
		for(int col = 0; col < COL_SIZE; col++) {
			if((row % 2 == 0) || (col % 2 == 0))
				maze[row][col] = '#';
			else
				maze[row][col] = '.';
		}
	}
}

//maze traversal
void mazeTraverse(const char maze[][COL_SIZE], int startX, int startY)
{
	Direction dir;

	//decide initial direction
	if(startX == 0)  //entrance is on north side, so go down
		dir = S;  
	else if(startX == ROW_SIZE-1)  //entrance is on south side, so go up
		dir = N;
	else if(startY == 0)  //entrance is on west side, so go right
		dir = E;
	else if(startY == COL_SIZE-1) //entrance is on east side, so go right
		dir = W;
	else
		cerr << "Error @mazeTraverse!";

	goMazeTraverse(maze, startX, startY, dir);
}

void goMazeTraverse(const char maze[][COL_SIZE], int startX, int startY, Direction dir)
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
		goMazeTraverse(maze, nextX, nextY, nextDir);
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

	return true;  //inside the maze and not a wall, or outside the maze.
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