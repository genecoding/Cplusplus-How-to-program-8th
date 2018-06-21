#pragma once

const int HEIGHT = 25;
const int WIDTH = 25;

class myRectangle
{
public:
	myRectangle(double length = 1, double width = 1);
	~myRectangle(void);
	double calPerimeter()
	{
		return (length + width) * 2;
	}
	double calArea()
	{
		return length * width;
	}
	double calLength();
	double calWidth();
	double getLength()
	{
		return length;
	}
	double getWidth()
	{
		return width;
	}
	void setLength(double length);
	void setWidth(double width);
	void set4Points();
	bool isSquare()
	{
		return length == width;  //you have to check whether it's a rectangle first.
	}
	void draw(char plane[HEIGHT][WIDTH]);
	void setFillCharacter(char c = ' ')
	{
		fillChar = c;
	}
	void setPerimeterCharacter(char c = '*')
	{
		periChar = c;
	}
private:
	double length;
	double width;
	int p_row[4];
	int p_col[4];
	char fillChar;
	char periChar;
	double disSq(double p1row, double p1col, double p2row, double p2col)
	{
		return (p1row - p2row) * (p1row - p2row) + (p1col - p2col) * (p1col - p2col);
	}
	bool isRectangle();
	void reorderPoints();  //to make draw easier, reorder points in advanced.
	void swap(int &a, int &b);
	void tessellate(int x1, int y1, int x2, int y2, char plane[HEIGHT][WIDTH]);
	void fillRect(char plane[HEIGHT][WIDTH]);
	void fillTheRow(char plane[HEIGHT][WIDTH], int p[], int yy);
	void display(char plane[HEIGHT][WIDTH]);
};

