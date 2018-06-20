#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void selectionSortRecur(int a[], int start, int end);
void printArray(int a[]);

const int SIZE = 10;

int main()
{
	int a[SIZE] = {4, 35, 6, 18, 75445, 74, 29, 355, 1, 64};

	cout << "before sorting: ";
	printArray(a);
	selectionSortRecur(a, 0, SIZE);
	cout << "\nafter sorting: ";
	printArray(a);

	cout << endl << endl;
	return 0;
}

void selectionSortRecur(int a[], int start, int end)
{
	if(start == end)
		return;
	else {
		int temp;
		for(int i = start+1; i < end; i++) {
			if(a[i] < a[start]) {
				temp = a[start];
				a[start] = a[i];
				a[i] = temp;
			}
		}
		selectionSortRecur(a, start+1, end);
	}
}

void printArray(int a[])
{
	for(int i = 0; i < SIZE; i++)
		cout << a[i] << ' ';
}