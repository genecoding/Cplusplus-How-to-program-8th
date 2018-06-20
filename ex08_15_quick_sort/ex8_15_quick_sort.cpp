#include "quickSort.h"
#include <iostream>

using std::cout;
using std::endl;

void printArray(int a[]);

const int SIZE = 10;

int main()
{
	int a[] = {37, 2, 6, 4, 89, 8, 10, 12, 68, 45};

	printArray(a);
	quicksort(a, 0, SIZE-1);
	printArray(a);

	cout << endl;
	return 0;
}

void printArray(int a[])
{
	for(int i = 0; i < SIZE; i++)
		cout << a[i] << ' ';
	cout << endl;
}