/**
 * 大O记号
 */

/**
 * 常数O(1) (constant function)
 * "常数时间复杂度算法"(constant-time algorithm)。此类算法已是最理想的
 * 仅需O(1)辅助空间的算法，亦称作就地算法(in-place algorithm)
 
 ordinaryElement(S[], n)  //从n ≥ 3个互异整数中，除最大、最小者以外，任取一个"常规元素"
    任取三个元素x,y,z ∈ S; // 返回三个元素亦必互异
    通过比较，对它们做排序; // 设经排序后，依次重命名为：a < b < c
    输出b
算法：取非极端元素
T(n)=常数=O(1)=Ω(1)=θ(1)
 */

/**
 * @param x 
 * @param y 
 * 
int   a：一个int类型，名称叫a
int*  a：一个整形的指针，名称叫a（a是一个整型的指针）
int  *a：一个指向整型的地址，名称叫a（一级指针，表示a所指向的地址里面存放的是一个int类型的值，a地址指向的类型是整型）
int **a：二级指针，表示a所指向的地址里面存放的是一个指向int类型的指针（即a指向的地址里面存放的是一个指向int的一级指针）
int & a：声明一个int引用类型，名称叫a

int &b=a;    //这个声明语句中的&是一个引用
int *p=&b;   //这个指针初始化语句中的&是取地址运算符
 */
void swap(int &x, int &y) {
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}


/**
 * @brief 起泡算法：给定n个整数，按(非降)序排列
 * 观察：有序/无序序列中，任意/总有一对相邻元素顺序/逆序
 */
void bubblesort1A(int A[], int n) { // 起泡排序算法(版本1A)：0 <= n
    for (bool sorted = false; sorted =!sorted; n--) {
        for (int i = 0; i < n; i++) { // 自左向右逐对检查当前范围A[0, n)内的各相邻元素
            if(A[i-1] > A[i]) {  // 逆序则交换
                swap(A[i-1], A[i]);
                sorted = false;
            }
        }
        n--;
    }
} // 借助布尔型标志位sorted. 可及时提前退出，而不是总是蛮力地做n - 1 趟扫描交换
// 经过k轮扫描交换后，最大的k个元素已经就位，因此问题规模缩减为n-k


/**
 * @brief 对数O(logn^c)，对数多项式(ploy-log function) 无限接近于O(1)
 * 
 * 整数二进制展开中，数为1的总数统计
 */
int countOnes(unsigned int n) {
    int ones;
    while (0<n) {
        ones += (1 & n); // 检查最低位，若为1则计数
        n >> 1;
    }
    return ones;
} // 等效于glibc的内置函数int __builtin_popcount(unsigned int n)

/**
 * @brief 多项式O(polynomial(n)),这类算法的效率已经可以令人满意了
 * 线性O(n),(linear function), 所有的O(n)类函数
 * 
 * 数组元素求和算法sum_0(), 数组求和迭代版，减而治之
 */
int sum_0(int A[], int n) {
    int sum = 0;
    for (int i = 0;i <n; i++) {
        sum += A[i];
    }
    return sum;
} // T(n) = O(1) + O(n) × O(1) + O(1) = O(n+2) = O(n)
// 空间复杂度，除了输入以外，额外申请的空间O(2)

/**
 * @brief 指数O(2^n) exponential function
 * 增长及其之快，认为是不可以忍受的
 * 
 * 从O(n^c)到O(2^n), 是从有效算法到无效算法的分水岭
 * 
 * 幂函数算法（蛮力迭代版）
 * 
 * 
 * "message": "'__int64' does not name a type; did you mean '__divtc3'?",
 * It looks like you you are trying to use MSVC specific __int64 type with GCC. That does not work, use long long instead.
 */
long long power2BF_1(int n) {
    long long pow = 1;  // O(1): 累积器初始化为2^0
    while(0 < n--) {  // 迭代n轮，每轮都需要迭代
        pow << 1;     // O(1)：将累积器翻倍
    }
    return pow;
} // O(n) = O(2^r), r为输入指数n的比特位数

/**
 * @brief 2-Subset
 * S包含n个正整数，ΣS=2m
 * S是否存在子集T，满足ΣT=m
 * 
 * 直觉算法：逐一枚举S的每一个子集，并统计其中元素总和。枚举规模 |2^S|=2^|S=2^n
 * 定理：2-Subset is NP-complete
 * 就目前的计算模型来看，不存在可在多项式时间内回答此问题的算法，即直觉算法已属最优
 */

/**
 * @brief 典型的复杂度层级包括
 * O(1)、O(log*n)、O(loglogn)、O(logn)、O(sqrt(n))、O(n)、O(nlog*n)、O(nloglogn)、O(nlogn)、O(n^2)、O(n^3)、O(n^c)、O(2^n)
 * 
 */

/**
 * @brief Back-Of-The-Envelope-Calculation
 * 封底估计，不用纸笔
 * 复杂度计算  10^9 约等于 1秒 假定计算机是1GHz的主频
 * 10^5秒大致就是一天，一天是86400秒
 * 10^10秒大约就是三生三世， 3个世纪
 * 2^32 是 4G
 * 
 * 级数 series
 * 迭代 iteration
 */

/*#############################################################*/

/**
 * @brief 迭代与递归
 * 
 * 减而治之 Decrease-and-conquer：划分为一个平凡，一个规模缩减的两个子问题
 * 递归的求解规模缩减的问题，直到足够小成为一个平凡的子问题(递归基)，再由子问题的解，得到原问题的解
 */

/**
 * <b>减而治之</b>
 * 
 * @brief Linear Recursion：线性递归
 * 递归跟踪（Recursion Trace）：绘出计算过程中出现的所有递归实例（及其调用关系）
 * 它们各自所需的时间的总和（调用语句本身，计入对应的子实例），即为整体运行时间
 * 在分析复杂度的时候，调用语句本身抹掉，即sum(A, n-1)调用的消耗是O(1)，计入由它产生的递归实例中
 * 当sum(A, n)调用sum(A, n-1)时，sum(A, n)函数中的数据以"函数帧"的形式被压入一个栈中，并没有处于执行状态
 * 
 * 共计n+1个递归实例，各自只需O(1)时间，T(n)=O(1)×(n+1)=O(n)
 */
int sum_1(int A[], int n) {
    return (n<1) ? 0 : sum_1(A, n-1) + A[n-1];
}

/**
 * @brief 数组A[0, n),将其前后颠倒
 * 接口: void reverse(int *A, int lo, int hi);
 */

/**
 * @brief 递归形式，在线型递归算法中，若递归调用在递归实例中恰好以最后一步操作的形式出现，则称为尾递归(tail recursion)
 * 属于尾递归形式的算法，均可以简捷地转换为等效的迭代版本
 * 递归版本
 * 
 * O(hi - lo + 1) = O(n)
 */
void reverse_1(int *A, int lo, int hi) {
    if (lo < hi) { // 规模问题的奇偶性不变，需要两个递归基(问题规模缩减为0或者1的时候，停止递归)
        swap(A[lo], A[hi]);
        reverse_1(A, lo+1, hi-1);
    }
    // else return; // base case 两种情况，区间宽度最小的奇数和最小的偶数
}

/**
 * @brief 迭代原始版本
 * O(hi - lo + 1) = O(n)
 */
void reverse_0(int *A, int lo, int hi) {
    next:
    if (lo < hi) { // 规模问题的奇偶性不变，需要两个递归基(问题规模缩减为0或者1的时候，停止递归)
        swap(A[lo], A[hi]);
        lo++;
        hi--;
        goto next;
    }
}

/**
 * @brief 迭代精简版本
 */
void reverse_0(int *A, int lo, int hi) {
    while (lo < hi) {
        swap(A[lo++], A[hi--]);
    }
}




/**
 * @brief 迭代与递归
 * 
 * 分而治之 Divide-and-Conquer：为求解一个大规模的问题，可以将其划分为若干子问题（通常两个，且规模大体相当）
 * 分别求解子问题，由子问题的解。合并得到原问题的解
 */


/**
 * @brief 数组A[0, n),将其求和
 * 接口: void sum(int *A, int lo, int hi);
 */
/**
 * @brief 分而治之
 * Binary Recursion
 * 
 * 递归跟踪： T(n) = 各层递归实例所需时间之和 
 *                = O(1) × (2^0 + 2^1 + ... + 2^logn)
 *                = O(1) × (2^(1+logn) - 1) = O(n)     // 几何级数
 * 递推方程： T(n) = 2 × T(n/2) + 1
 *           T(1) = 1 // base: sum(A, k, k)
 *           T(n) = 4 × T(n/4) + 3 = 8 × T(n/8) + 7 = n × T(1) + O(n-1) 
 *                = O(2n-1) = T(n)
 * 
 */

int sum_2 ( int A[], int lo, int hi ) { //数组求和算法（二分递归版，入口为sum(A, 0, n)）
    if (hi - lo < 2) {
        return A[lo]; //递归基：区间宽度不足2
    }
    int mi = ( lo + hi ) >> 1; //（否则）均分原区间
    return sum_2 ( A, lo, mi ) + sum_2 ( A, mi, hi ); //递归求和，然后合计
} //O(hi - lo)，线性正比于区间的长度



#include <iostream>
#include <stdio.h>
using namespace std;
int main(int argc, char const *argv[])
{
    cout << "before reverse" << endl;
    int a[5] = {1,2,3,4,5};
    int len = sizeof(a)/sizeof(a[0]);
    for (size_t i = 0; i < len; i++) {
        printf("a[%d] is %d \n", i,  a[i]);
    }
    reverse_0(a, 1, 3);
    cout << "after reverse" << endl;
    for (size_t i = 0; i < len; i++) {
        printf("a[%d] is %d \n", i,  a[i]);
    }

    int a1 = 1;
    int a2 = 2;
    printf("a1 is %d \n", a1);
    printf("a2 is %d \n", a2);
    swap(a1, a2);
    printf("a1 is %d \n", a1);
    printf("a2 is %d \n", a2);
    
    return 0;
}



