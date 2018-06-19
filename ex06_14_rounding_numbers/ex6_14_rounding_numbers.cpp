#include <math.h>  //floor
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

double roundToInteger(double);
double roundToTenths(double);
double roundToHundredths(double);
double roundToThousandths(double);

int main()
{
	double num;
	cout << "enter a number: ";
	cin >> num;
	cout << num << endl
		 << "round to integer is " << roundToInteger(num) << endl
		 << "round to tenths is " << roundToTenths(num) << endl
		 << "round to hundredths is " << roundToHundredths(num) << endl
		 << "round to thousandths is " << roundToThousandths(num) << endl;

	return 0;
}

double roundToInteger(double num)
{
	return floor( num + .5 );
}

double roundToTenths(double num)
{
	return floor( num * 10 + .5 ) / 10;
}

double roundToHundredths(double num)
{
	return floor( num * 100 + .5 ) / 100;
}

double roundToThousandths(double num)
{
	return floor( num * 1000 + .5 ) / 1000;
}

