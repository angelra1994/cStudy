#ifndef __POINT_H__
#define __POINT_H__

// 宏定义
#define PARA 35
 
// 全局变量声明
extern int g_a, g_b;

// 函数声明
extern void set(int a, int b);
extern void print();

// 结构体声明
struct Point{
	int x, y;
};  

// 结构体声明2 
typedef struct NODE{
	int x;
}Node, *pNode;  
 
#endif
