#include <iostream>
#include "point.h"

using namespace std;
using namespace MyPoint;

int main()
{
	Point pt(3, 5);	
	pt.print();

	pt.set(6, 10);
	pt.print();

	return 0;
}
