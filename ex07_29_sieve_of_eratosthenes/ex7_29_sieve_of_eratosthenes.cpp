#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void sieveOfEratosthenes();

int main()
{
	sieveOfEratosthenes();

	cout << endl;
	return 0;
}

void sieveOfEratosthenes()
{
	bool n[1000];
	
	//default array
	for(int i = 0; i < 1000; i++)
		n[i] = true;

	for(int i = 2; i < 1000; i++) {
		if(n[i] == true) {
			for(int j = i+1; j < 1000; j++)
				if(j % i == 0)
					n[j] = false;
		}
	}

	//print the result
	for(int i = 2; i < 1000; i++) {
		if(n[i])
			cout << i << " is prime." << endl;
	}
}

