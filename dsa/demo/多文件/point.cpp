#include <iostream>
#include "point.h"

using namespace std;
using namespace MyPoint;
 
// 构造函数 
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

// 成员函数 
void Point::set(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Point::print()
{
	cout << x << " " << y << endl;
}

