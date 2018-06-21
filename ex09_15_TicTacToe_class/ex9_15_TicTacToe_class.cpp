#include "TicTacToe.h"
#include <iostream>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	srand(time(0));
	TicTacToe t1;
	int sel;

	cout << "1) play with human, 2) play with computer: ";
	cin >> sel;

	while(1) {
		if(sel == 1)
			t1.playWithMan();
		else if(sel == 2)
			t1.playWithCom();

		t1.reset();
	}

	return 0;
}

