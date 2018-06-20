#include "quickSort.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int partition(int a[], int start, int end)
{
	int pivot = a[start];
	int fromLeft = start+1;
	int fromRight = end;

	while(fromLeft < fromRight) {
		while(a[fromLeft] < pivot)
			fromLeft++;  //go right ->

		while(a[fromRight] > pivot)
			fromRight--;  //go left <-

		if(fromRight <= fromLeft) {
			swap(a[start], a[fromRight]);
			return fromRight;  //new pivot
		}

		//a[fromLeft] > pivot, a[fromRight] < pivot, so swap two numbers.
		swap(a[fromLeft], a[fromRight]);
	}
}

void quicksort(int a[], int start, int end)
{
	if(end > start) {
		int pivot = partition(a, start, end);
		quicksort(a, start, pivot-1);
		quicksort(a, pivot+1, end);
	}
}



