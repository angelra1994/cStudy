/**
 * 过直线上定点作直�?
 * 
 * 埃及人的十二节十字形绳索
 * perpendicular(l, A)
 * 输入: 直线l及其上面的一点A
 * 输出: 经过A且垂直于l的直�?
 * 
 * 1. �?12段等长绳�?，依次�?�尾连接成环（十字形），连接处称�?"�?"，顺时针编号�?0,1, ... 11
 * 2. 奴隶A看�??0号结，将其固定在A�?
 * 3. 奴隶B牵动4号结，将十字形绳索沿直线l方向都尽�?能拉�?
 * 4. 奴隶C牵动9号结，将绳索尽可能拉�?
 * 5. 经过0号和9号结，绘制一条直�?
 * 
 * 勾股定理3+4+5
 * 
 */

/**
 * 三等分给定线�?
 * 欧几里得尺�??
 * tripartition(AB)
 * 输入：线段AB
 * 输出：将AB三等分的两个点C和D
 * 
 * 1. 从A发出一条与AB不重合的射线p
 * 2. 任取p上的三点C'、D'和B'，使|AC'|=|C'D'|=|D'B'|
 * 3. 连接B'B，做平�?�线D'D和C'C
 * 
 */

/**
 * 效率：速度尽可能快；存储空间尽�?能少
 */

/**
 * 有穷性：Hailstone序列
 * 
 *                 |  {1}                       n�?1
 * Hailstone(n) =  |  {n} �?  Hailstone(n/2)    n�?偶数
 *                 |  {n} �?  Hailstone(3n+1)   n�?奇数
 * 
 * Hailstone(42) = {42,21,64,32...1}
 * 计算序列Hailstone(n) 长度
 */
int hailstone(int n) {
    int len =1;
    while ( 1 < n ) {
        if ( n % 2 == 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
        len ++;
    }
    return len;
}


#include <iostream>
#include <stdio.h>
using namespace std;
int main(int argc, char const *argv[])
{
    int n = 42;
    cout << "abc" <<endl;

    int res = hailstone(n);
    printf("length of hailstone(%d) is %d\n", n, res);
    cout << "你好 c++";
    return 0;
}
