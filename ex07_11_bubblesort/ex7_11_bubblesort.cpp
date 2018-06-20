#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void bubbleSort(int list[], int size);
void bubbleSortEn(int list[], int size);
void printArray(int list[], int size);

int main()
{
	const int SIZE = 10;
	int a[SIZE] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 1};

	cout << "before sort: " << endl;
	printArray(a, SIZE);
	cout << endl;

	bubbleSort(a, SIZE);
	
	//-----
	int b[SIZE] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 1};
	
	cout << endl << "before sort: " << endl;
	printArray(b, SIZE);
	cout << endl;
	
	bubbleSortEn(b, SIZE);

	return 0;
}

void bubbleSort(int list[], int size)
{
	int temp;
	int count = 0;
	for(int i = 0; i < size-1; i++) {
		for(int j = 0; j < size-1; j++) {
			count++;
			if(list[j] > list[j+1]) {
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}

		printArray(list, size);
	}

	cout << count << " comparisons" << endl;
}

void bubbleSortEn(int list[], int size)
{
	int temp;
	int count = 0;
	bool swap;

	for(int i = 0; i < size-1; i++) {
		swap = false;
		for(int j = 0; j < size-1-i; j++) {  //enhancement (a)
			count++;
			if(list[j] > list[j+1]) {
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
				swap = true;
			}
		}
		
		printArray(list, size);

		if(!swap)  //enhancement (b)
			break;
	}

	cout << count << " comparisons" << endl;
}

void printArray(int list[], int size) {
	for(int i = 0; i < size; i++)
		cout << list[i] << ' ';
	cout << endl;
}