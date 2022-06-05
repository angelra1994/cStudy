/**
 * @file 04_Fibonacci.cpp
 * @brief Dynamic programming
 * Fibonacci
 * fib(n) = f(n-1) + f(n-2): {0, 1, 1, 2, 3, 5, 8, 13, 21, ...}
 */

/**
 * @brief 二分递归版本
 * fib(n) = f(n-1) + f(n-2): {0, 1, 1, 2, 3, 5, 8, 13, 21, ...}
 * 
 * 复杂度: T(0) = T(1) = 1; T(n) = T(n-1) + T(n-2) + 1, n>1 (计算出fib(n-1)和fib(n-2)花费的时间，之后使用O(1)时间将二者合并)
 * S(n) = [T(n) + 1] / 2
 * S(0) = 1 = fib(1), S(1) = 1 = fib(2)
 * S(n) = S(n-1) + S(n-2) = fib(n+1)     // Φ = (1+√5) / 2 = 1.61803
 * T(n) = 2 × S(n) - 1 = 2 × fib(n+1) - 1 = O(fib(n+1)) = O(Φ^n) = O(2^n)
 * 
 * 
 * 估算， Φ^36 ≈ 2^25  Φ^5 ≈ 10
 * fib(43) 需要1秒      Φ^43 ≈ 2^30 ≈ 10^9 flo = 1 sec
 * fib(67) 需要1天      Φ^67 ≈ 10^14 flo = 10^5 sec ≈ 1 day
 * fib(92) 需要300年    Φ^92 ≈ 10^19 flo = 10^10 sec ≈ 10^5 day ≈ 3 century   三生三世
 * 结论 算法不好
 * 递归版fib()低效的根源在于，各递归实例均被大量地重复调用
 * 先后出现的递归实例，共计O(Φ^n)个；而去除重复之后，总共不过O(n)种

 */
long long fib1(long long n) { //计算Fibonacci数列的第n项（二分递归版）：O(2^n)
    if (2 > n) {
        return n;             //若到达递归基，直接取值
    }
    return fib1(n-1) + fib1(n-2);  // 递归的计算前两项，求其和
}

/**
 * @brief Memoization 已经计算的递归实例制表进行查找
 */
long long fib2(long long n, long long& prev) {  //计算Fibonacci数列第n项（线性递归版）：入口形式fib(n, prev)
    if ( 0 == n ) { //若到达递归基，则
        prev = 1;
        return 0; 
    } //直接取值：fib(-1) = 1, fib(0) = 0
    else { //否则
        long long prevPrev;
        prev = fib2 ( n - 1, prevPrev ); //递归计算前两项
        return prevPrev + prev; //其和即为正解
    }
} //用辅助变量记录前一项，返回数列的当前项，T(n)=O(n), 空间也是O(n)

/**
 * @brief fibonacci相邻的两项，滚动的交替计算
 */
long long fib3(long long n) {
    long long f = 1;  // fib(-1)  设计辅助变量
    long long g = 0;  // fib(0)
    while (1 < n--) {
        g += f; 
        f = g - f;
    }//依据原始定义，通过n次加法和减法计算fib(n)
    return g; //返回
}// T(n) =O(n), 仅需O(1)空间


#include <iostream>
#include <stdio.h>
long long fib1(long long n);
long long fib2(long long n, long long& prev);
long long fib3(long long n);
using namespace std;
int main(int argc, char const *argv[]) {
    long long res;
    for (size_t i = 0; i < 6; i++) {
        res = fib1(i);
        cout << "fib(" << i << ")=" << res<<endl;
    }
    // 当i<36 循环用时 3.3s
    // 当i<46 循环用时 104.187s

    long long prev;
    for (size_t i = 0; i < 16; i++) {
        res = fib2(i, prev);
        cout << "fib(" << i << ")=" << res<<endl;
    }
    // 当i<46 循环用时 2.945s

    
    for (size_t i = 0; i < 16; i++) {
        res = fib3(i);
        cout << "fib(" << i << ")=" << res<<endl;
    }
    // 当i<46 循环用时 2.945s
    return 0;
}

