#pragma once

namespace MyPoint
{
	// 类的定义
	class Point
	{
	private:
		int x, y;
	public:
		// 构造函数
		Point();
		Point(int x, int y);
	
		// 成员函数
		void set(int x, int y);
		void print();
	};
} 
