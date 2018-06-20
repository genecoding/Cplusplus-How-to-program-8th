#include <iostream>
#include <ctime>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void airlineBooking(bool seat_taken[], int seat_n);
int seatGen(bool seat_taken[], int lowerbound, int upperbound);
int numberGen(int lowerbound, int upperbound);
bool seatIsFull(bool seat_taken[], int lowerbound, int upperbound);
int assignSeat(bool seat_taken[], int lowerbound, int upperbound);

int main()
{
	const int SEAT_NUM = 10;
	bool seat_taken[SEAT_NUM] = {0};
	srand(time(0));

	for(int i = 0; i <= 10; i++) {  //test 11 times
		airlineBooking(seat_taken, SEAT_NUM);
	}

	return 0;
}

void airlineBooking(bool seat_taken[], int seat_n)
{
	int option;
	bool FC_isFull = false;
	bool E_isFull = false;
	bool planeIsFull = false;
	bool bookingSuccessful = false;
	bool cancelBooking = false;
	char rearrange = 'n';
	int seatNum;
	
	cout << "Please type 1 for \"First Class\", type 2 for \"Economy\": ";
	cin >> option;

	do {
		switch(option) {
		case 1:  //First Class
			if((seatNum = seatGen(seat_taken, 1, 5)) == -1)
				FC_isFull = true;
			else {
				bookingSuccessful = true;
				break;
			}
			break;
		case 2:  //Economy
			if((seatNum = seatGen(seat_taken, 6, 10)) == -1)
				E_isFull = true;
			else {
				bookingSuccessful = true;
				break;
			}
			break;
		default:
			cerr << "Invalid option!";
			break;
		}

		if(!bookingSuccessful)  //change class
		{  
			if(FC_isFull && E_isFull) {  //already change class, but still full
				planeIsFull = true;
			} else {  //change class first time
				if(FC_isFull)
					cout << "The FC is full. Is it acceptable to be replaced in Economy? (Y/N): ";
				else if(E_isFull) 
					cout << "The E is full. Is it acceptable to be replaced in First Class?  (Y/N): ";
			
				cin >> rearrange;
				if(rearrange == 'Y' || rearrange == 'y') {
					(option == 1) ? option = 2 : option = 1;
				} else {
					cout << "Cancel Booking." << endl;
					cancelBooking = true;
				}
			}
		}
	} while(!planeIsFull && !bookingSuccessful && !cancelBooking);

	if(planeIsFull)
		cout << "The flight is full. Next flight leaves in 3 hours." << endl;
	else if(cancelBooking)
		cout << "Next flight leaves in 3 hours." << endl;
	else {  //booking successful
		cout << "Your seat is ";
		if(option == 1)
			cout << "First Class, ";
		else 
			cout << "Economy, ";
		cout << "No. " << seatNum << endl;
	}
}

int seatGen(bool seat_taken[], int lowerbound, int upperbound)
{
	int seatNum;

	//assign seat randomly at first time
	seatNum = numberGen(lowerbound, upperbound);
	if(seat_taken[seatNum-1] == false) {
		seat_taken[seatNum-1] = true;
		return seatNum;
	}

	//if seat taken, assign to an empty seat sequentially 
	if(seatIsFull(seat_taken, lowerbound, upperbound))
		return -1;
	else {
		seatNum = assignSeat(seat_taken, lowerbound, upperbound);
		seat_taken[seatNum-1] = true;
		return seatNum;
	}
}

int numberGen(int lowerbound, int upperbound) {
	int range = std::abs(upperbound-lowerbound) + 1;
	return (rand() % range) + lowerbound;
}

bool seatIsFull(bool seat_taken[], int lowerbound, int upperbound)
{
	for(int i = lowerbound-1; i <= upperbound-1; i++)
		if(seat_taken[i] == false)
			return false;

	return true;
}

int assignSeat(bool seat_taken[], int lowerbound, int upperbound)
{
	for(int i = lowerbound-1; i <= upperbound-1; i++) {
		if(seat_taken[i] == false) {
			seat_taken[i] = true;
			return i+1;
		} 
	}
}