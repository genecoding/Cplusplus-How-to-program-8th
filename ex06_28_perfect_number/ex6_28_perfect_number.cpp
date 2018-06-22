#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

void isPerfect(int n);

int main()
{
	for(int i = 1; i <= 1000; i++) {
		(isPerfect(i))
	}

	return 0;
}

void isPerfect(int n)
{
	int factors[1001] = {0};
	int rootOfN = (std::sqrt(static_cast<double>(n)));  //find factors of n from rootOfN to 1.

	//find all factors of n
	for(int i = rootOfN; i >= 1; i--) {
		if(n % i == 0) {
			factors[i] = 1;
			factors[(n/i)] = 1;
		}
	}

	//check if n is a perfect number
	int perfect = 0;
	for(int i = 1; i < n; i++) {
		if(factors[i] == 1)
			perfect += i;
	}

	//print out
	if(perfect == n) {
		cout << n << ", ";
		for(int i = 1; i < n; i++) {
			if(factors[i] == 1)
				cout << i << ' ';
		}
		cout << endl;
	}

	return;  
}
