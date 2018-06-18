#include "stdafx.h"
#include <iostream>
#include <limits.h>  //INT_MIN
using std::cin;
using std::cout;
using std::endl;

void findTheLargest();
void findTwoLargests();

int main()
{
	findTheLargest();
	findTwoLargests();

	return 0;
}

void findTheLargest()
{
	int counter = 0;
	int largest = INT_MIN;
	int number;

	while(counter < 10) {
		cout << "enter a number: ";
		cin >> number;

		if(number > largest)
			largest = number;

		counter++;
	}

	cout << "\nThe largest number is " << largest << endl;
}

void findTwoLargests()
{
	int counter = 0;
	int largest, sec_largest;
	int number;
	largest = sec_largest = INT_MIN;

	while(counter < 10) {
		cout << "enter a number: ";
		cin >> number;

		if(number > largest) {
			sec_largest = largest;
			largest = number;
		} else if(number > sec_largest) {
			sec_largest = number;
		}

		counter++;
	}

	cout << "\nThe largest number is " << largest << endl
		 << "The second largest number is " << sec_largest << endl;
}
