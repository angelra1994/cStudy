#include "stdio.h"

// 全局变量
int g_a, g_b;

// 函数定义
void set(int a, int b)
{
	g_a = a;
	g_b = b;
}

void print()
{
	int a = g_a;
	int b = g_b;
	printf("%d %d\n", a, b);
}