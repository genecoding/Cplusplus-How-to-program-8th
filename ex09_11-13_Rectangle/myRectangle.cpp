#include "myRectangle.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;

myRectangle::myRectangle(double length, double width)
{
	set4Points();
	reorderPoints();
	setLength(calLength());
	setWidth(calWidth());
	setPerimeterCharacter();
	setFillCharacter();
}

myRectangle::~myRectangle(void)
{
}

void myRectangle::setLength(double l)
{
	if(l > 0 && l < 20)
		length = l;
	else
		throw std::invalid_argument("invalid length");
}

void myRectangle::setWidth(double w)
{
	if(w > 0 && w < 20)
		width = w;
	else
		throw std::invalid_argument("invalid width");
}

void myRectangle::set4Points()
{
	int row, col;
	bool isRect = false;

	cout << "enter 4 points(row and col in order)" << endl;
	do {	
		for(int i = 0; i < 4; i++) {
			do {
				cout << "enter point" << i+1 << " row pos: ";
				cin >> row;
				cout << "enter point" << i+1 << " col pos: ";
				cin >> col;

				if((row < 0 || row > 20) || (col < 0 || col > 20))
					cout << "invalid point, enter again!" << endl;
			} while((row < 0 || row > 20) || (col < 0 || col > 20));

			p_row[i] = row;
			p_col[i] = col;
		}

		if(!(isRect = isRectangle()))
			cout << "It's not a rectangle, enter 4 points again!" << endl;
	} while(!isRect);
}

//find the center of mass of corner points: cx=(x1+x2+x3+x4)/4, cy=(y1+y2+y3+y4)/4
//test if square of distances from center of mass to all 4 corners are equal
bool myRectangle::isRectangle()
{
	double cx, cy;
	double dd1, dd2, dd3, dd4;

	cx = static_cast<double>(p_row[0]+p_row[1]+p_row[2]+p_row[3]) / 4;
	cy = static_cast<double>(p_col[0]+p_col[1]+p_col[2]+p_col[3]) / 4;

	dd1 = disSq(cx, cy, p_row[0], p_col[0]);
	dd2 = disSq(cx, cy, p_row[1], p_col[1]);
	dd3 = disSq(cx, cy, p_row[2], p_col[2]);
	dd4 = disSq(cx, cy, p_row[3], p_col[3]);

	return dd1 == dd2 && dd1 == dd3 && dd1 == dd4;
}

double myRectangle::calLength()
{  //there are width, length and diagonal, and length side is the middle one.
	double d1, d2, d3;
	d1 = sqrt(disSq(p_row[0], p_col[0], p_row[1], p_col[1]));
	d2 = sqrt(disSq(p_row[0], p_col[0], p_row[2], p_col[2]));
	d3 = sqrt(disSq(p_row[0], p_col[0], p_row[3], p_col[3]));

	return d1+d2+d3 - std::max(d1, std::max(d2, d3)) - std::min(d1, std::min(d2, d3));
}

double myRectangle::calWidth()
{
	double d1, d2, d3;
	d1 = sqrt(disSq(p_row[0], p_col[0], p_row[1], p_col[1]));
	d2 = sqrt(disSq(p_row[0], p_col[0], p_row[2], p_col[2]));
	d3 = sqrt(disSq(p_row[0], p_col[0], p_row[3], p_col[3]));

	return std::min(d1, std::min(d2, d3));
}

void myRectangle::reorderPoints()
{  //reorder points that makes p0p1 a width side, p1p2 a diagonal, p1p3 a length side.
	int pWid;
	double wid, diag;

	wid = disSq(p_row[0], p_col[0], p_row[1], p_col[1]);
	pWid = 1;
	for(int i = 2; i < 4; i++) {		
		if(wid > disSq(p_row[0], p_col[0], p_row[i], p_col[i])) {
			wid = disSq(p_row[0], p_col[0], p_row[i], p_col[i]);
			pWid = i;
		}
	}
	if(pWid != 1) {
		swap(p_row[1], p_row[pWid]);
		swap(p_col[1], p_col[pWid]);
	}

	diag = disSq(p_row[0], p_col[0], p_row[2], p_col[2]);		
	if(diag < disSq(p_row[0], p_col[0], p_row[3], p_col[3])) {
		swap(p_row[2], p_row[3]);
		swap(p_col[2], p_col[3]);
	}
}

void myRectangle::swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void myRectangle::draw(char plane[HEIGHT][WIDTH])
{
	int x1, y1, x2, y2;
	for(int i = 0; i < 4; i++) {
		x1 = p_row[i];
		y1 = p_col[i];
		x2 = p_row[(i+1)%4];
		y2 = p_col[(i+1)%4];
		plane[y1][x1] = periChar;  //mark 4 corners
		tessellate(x1, y1, x2, y2, plane); //draw lines
	}

	fillRect(plane);
	display(plane);
}

void myRectangle::fillRect(char plane[HEIGHT][WIDTH])
{  //fill a rect = fill all dots between 2 periChars(because they're inside the rect) for every row.
	bool aRowToFill;
	int p[2];

	for (int yy = 0; yy < HEIGHT; ++yy) {
		aRowToFill = true;
		p[0] = p[1] = -1;
		for (int xx = 0; xx < WIDTH; ++xx) {
			if(plane[yy][xx] == periChar) {
				aRowToFill = !aRowToFill;
				p[0] = p[1];
				p[1] = xx;
			}
		}
		if(aRowToFill) 
			fillTheRow(plane, p, yy);
	}
}

void myRectangle::fillTheRow(char plane[HEIGHT][WIDTH], int p[], int yy)
{
	for(int xx = p[0]+1; xx < p[1]; xx++) {
		if(plane[yy][xx] != periChar)  //it's not a dot on the perimeter.
			plane[yy][xx] = fillChar;
	}
}

// Connect two points
void myRectangle::tessellate(int x1, int y1, int x2, int y2, char plane[HEIGHT][WIDTH])
{
    if ( std::abs( x1 - x2 ) < 2 && std::abs( y1 - y2 ) < 2 )
        // Nothing else left to do, two points are next to each other:
        return;

    // find center
    int cx = ( x1 + x2 )/2;
    int cy = ( y1 + y2 )/2;

    // mark center
    plane[cy][cx] = periChar;

    // recurse and repeat
    tessellate( x1, y1, cx, cy, plane );
    tessellate( x2, y2, cx, cy, plane );
}

void myRectangle::display(char plane[HEIGHT][WIDTH])
{
	cout << endl;
	for(int i = 0; i <= WIDTH; i++)
		cout << i % 10;
	cout << endl;

    for (int yy = 1; yy < HEIGHT; ++yy) {
        for (int xx = 0; xx < WIDTH; ++xx) {
            cout << plane[yy][xx];
		}
		cout << yy % 10;
		cout << endl;
	}
}