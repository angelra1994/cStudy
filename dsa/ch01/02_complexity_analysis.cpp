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

void swap(int x, int y) {
    x = x ^ y;
    y = x ^ y;
    y = x ^ y;
}

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
 */
__int64 power2BF_1(int n) {
    __int64 pow = 1;  // O(1): 累积器初始化为2^0
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
 * 
 * 级数 series
 * 迭代 iteration
 */

/**
 * @brief 迭代与递归
 * 
 * （迭代）减而治之 Decrease-and-conquer：划分为一个平凡，一个规模缩减的两个子问题
 * 递归的求解规模缩减的问题，直到足够小成为一个平凡的子问题(递归基)，再由子问题的解，得到原问题的解
 */

/**
 * @brief Linear Recursion：线性递归
 * 递归跟踪（Recursion Trace）：绘出计算过程中出现的所有递归实例（及其调用关系）
 * 它们各自所需的时间的总和（调用语句本身，计入对应的子实例），即为整体运行时间
 * 在分析复杂度的时候，调用语句本身抹掉，即sum(A,n - 1)调用的消耗是O(1)，计入由它产生的递归实例中
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
 * 
 */
void reverse_1(int *A, int lo, int hi) {
    if (lo < hi) { // 规模问题的奇偶性不变，需要两个递归基(问题规模缩减为0或者1的时候，停止递归)
        swap(A[lo], A[hi])；
        reverse_1(A, lo+1, hi-1);

    }
}