#include "myRectangle.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	char plane[HEIGHT][WIDTH];
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++)
			plane[i][j] = ' ';

	myRectangle r1;
	r1.setFillCharacter('@');
	r1.setPerimeterCharacter('#');
	cout << "length is " << r1.getLength() << endl
		 << "width is " << r1.getWidth() << endl
		 << "area is " << r1.calArea() << endl
		 << "perimeter is " << r1.calPerimeter() << endl
		 << "it's " << (r1.isSquare() ? "" : "not") << " a square.";
	
	r1.draw(plane);

	cout << endl;
	return 0;

	try {
		myRectangle r1, r2(10, 12); 
		myRectangle r3(33, 6);
		cout << "r1 length: " << r1.getLength() << ", width: " << r1.getWidth() << endl
			 << "r2 length: " << r2.getLength() << ", width: " << r2.getWidth() << endl
			 << "r3 length: " << r3.getLength() << ", width: " << r3.getWidth() << endl;
	} catch(std::invalid_argument &ia) {
		std::cerr << "error message: " << ia.what() << endl;
	} 

	cout << endl;
	return 0;
}

