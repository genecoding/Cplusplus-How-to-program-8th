#include <iostream>

using std::cout;
using std::cin;
using std::endl;

enum Direction{N, E, S, W};
const int MAX_X = 20;
const int MAX_Y = 20;

void turtleGo(const int command[], int commandAmount);
void moveForward(bool floor[][MAX_Y], int paces, Direction current_dir, int &current_x, int &current_y, bool draw);
void printFloor(bool floor[][MAX_Y], int current_x, int current_y);

int main()
{
	int command[] = {2, 5, 12, 3, 5, 12, 3, 5, 12, 3, 5, 12, 1, 6, 9};
	int amount = 15;

	turtleGo(command, amount);

	return 0;
}

void turtleGo(const int command[], int commandAmount)
{
	int counter = 0;
	bool draw = false;
	bool endGame = false;
	bool floor[MAX_X][MAX_Y] = {0};
	Direction current_dir = N;
	int current_x = 0;
	int current_y = 0;

	do {
		switch(command[counter++]) {
		case 1:  //pen up
			draw = false;
			break;
		case 2:  //pen down
			draw = true;
			break;
		case 3:  //turn right
			current_dir = static_cast<Direction>((current_dir + 1) % 4);
			break;
		case 4:  //turn left
			current_dir = static_cast<Direction>((current_dir + 3) % 4);
			break;
		case 5:  //move forward n spaces
			moveForward(floor, command[counter++], current_dir, current_x, current_y, draw);
			break;
		case 6:  //print the 20*20 array
			printFloor(floor, current_x, current_y);
			break;
		case 9:  //end of game
			endGame = true;
			break;
		default:
			break;
		}
	} while(!endGame && counter != commandAmount);
}

void moveForward(bool floor[][MAX_Y], int paces, Direction current_dir, int &current_x, int &current_y, bool draw)
{
	int new_x, new_y;
	switch(current_dir) {
	case N:
		new_y = (current_y + paces > MAX_Y-1) ? MAX_Y-1 : current_y + paces;
		if(draw) {
			for(int i = current_y; i <= new_y; i++)
				floor[current_x][i] = true;
		}
		current_y = new_y;
		break;
	case E:
		new_x = (current_x + paces > MAX_X-1) ? MAX_X-1 : current_x + paces;
		if(draw) {
			for(int i = current_x; i <= new_x; i++)
				floor[i][current_y] = true;
		}
		current_x = new_x;
		break;
	case S:
		new_y = (current_y - paces < 0) ? 0 : current_y - paces;
		if(draw) {
			for(int i = current_y; i > new_y; i--)
				floor[current_x][i] = true;
		}
		current_y = new_y;
		break;
	case W:
		new_x = (current_x - paces < 0) ? 0 : current_x - paces;
		if(draw) {
			for(int i = current_x; i > new_x; i--)
				floor[i][current_y] = true;
		}
		current_x = new_x;
		break;
	default:
		break;
	}
}

void printFloor(bool floor[][MAX_Y], int current_x, int current_y)
{
	for(int i = MAX_Y-1; i >= 0; i--) {
		for(int j= 0; j < MAX_X; j++) {
			if(i == current_x && j == current_y)
				cout << '@';  //turtle
			else if(floor[i][j])
				cout << '*';  //trace
			else
				cout << '.';  //blank, where turtle had never been
		}
		cout << endl;
	}
	cout << endl;
}