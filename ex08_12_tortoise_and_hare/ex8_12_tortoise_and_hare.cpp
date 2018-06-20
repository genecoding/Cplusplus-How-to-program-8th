#include <iostream>
#include <ctime>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;

enum TortoiseMoveType {fastPlod, slip, slowPlod};
enum HareMoveType {sleep, bigHop, bigSlip, smallHop, smallSlip};

void tortoiseHareRace();
void drawRace(int *pos_T, int *pos_H);
void moveTortoise(int *pos_T);
void moveHare(int *pos_H);

int main()
{
	srand(time(0));

	tortoiseHareRace();

	return 0;
}

void tortoiseHareRace()
{
	int pos_Hare = 1;
	int pos_Tortoise = 1;

	cout << "BANG!!!!" << endl
		 << "AND THEY'RA OFF!!!!" << endl;

	do {
		moveTortoise(&pos_Tortoise);
		moveHare(&pos_Hare);
		drawRace(&pos_Tortoise, &pos_Hare);
		
		Sleep(10);  //10ms
	} while(pos_Hare < 70 && pos_Tortoise < 70);

	for(int i = 1; i <= 80; i++)
		cout << i % 10;
	cout << endl;

	if(pos_Hare >= 70 && pos_Tortoise >= 70)
		cout << "It's a tie";
	else if(pos_Hare >= 70)
		cout << "Hare win!!";
	else
		cout << "Tortoise win!!";

	cout << " T@" << pos_Tortoise << ", H@" << pos_Hare << endl;
}

void drawRace(int *pos_T, int *pos_H)
{
	for(int i = 1; i <= 78; i++) {  //69+9 = 78
		if(*pos_T == i && *pos_H == i)
			cout << "OUCH!";
		else if(*pos_T == i)
			cout << "T";
		else if(*pos_H == i)
			cout << "H";
		else
			cout << " ";
	}
	cout << endl;
}

void moveTortoise(int *pos_T)
{
	int move_T = (rand() % 10) + 1;

	if(move_T >= 1 && move_T <= 5)  //fast plod, 50%
		*pos_T += 3;
	else if(move_T >=6 && move_T <=7)   //slip, 20%
		*pos_T = (*pos_T-6 > 0) ? *pos_T-6 : 1;
	else  //slow plod, 30%
		*pos_T += 1;
}

void moveHare(int *pos_H)
{
	int move_H = (rand() % 10) + 1;

	if(move_H >= 1 && move_H <=2)  //big hop, 20%
		*pos_H += 9;
	else if(move_H == 3)  //big slip, 10%
		*pos_H = (*pos_H-12 > 0) ? *pos_H-12 : 1;
	else if(move_H >= 4 && move_H <= 6)  //small hop, 30%
		*pos_H += 1;
	else if(move_H >=7 && move_H <= 8)  //small slip, 20%
		*pos_H = (*pos_H-1 > 0) ? *pos_H-1 : 1;
	else  //sleep, 20%
		; 
}