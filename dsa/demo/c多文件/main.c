#include <stdio.h>
#include "point.h"

int main()
{
	// 宏调用
	printf("%d\n", PARA); 
	
	// 函数调用 
	set(3, 5);
	print();
	
	// 结构体定义 
	struct Point myPoint;
	myPoint.x = 3;
	myPoint.y = 5;
	printf("%d %d\n", myPoint.x, myPoint.y);
	
	// 结构体2定义 
	Node myNode;
	myNode.x = 3;
	printf("%d\n", myNode.x);   
	
	// 结构体指针定义 
	//pNode my_pNode = &myNode;
	pNode my_pNode = new Node();
	my_pNode->x = 5;
	printf("%d\n", my_pNode->x); 
	
	return 0;
}
