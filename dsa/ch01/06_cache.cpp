/**
 * @file 06_cache.cpp
 * 
 * 
 */


/**
 * @brief 就地循环移位
 * 仅用O(1)辅助空间，将数组A[0, n)的中的元素向左循环k个单元
 * void shift(int *A, int n, int k);
 */
void shfit0(int *A, int n, int k) {
    // 反复以1为间距循环左移
    while (k -- ) {
        shfit(A, n, 0, 1); // 共迭代k次, O(n·k)
    }
    
}

/**
 * @brief 
 * O(n/ GCD(n,k))   GCD 最大公约数
 */
int shfit(int *A, int n, int s, int k) {
    int b = A[s];
    int i = s;
    int j = (s + k) % n;
    int mov = 0;  // mov 记录移动次数
    while (s != j) { // 从A[s]出发，以k为间隔，依次左移k位
        A[i] = A[j];
        i = j;
        j = (j + k) % n;
        mov++;
    }
    A[i] = b;  // 最后起始元素转入对应位置
    return mov + 1;
}//[0, n)由关于k的g=GCD(n,k)个同余类组成， shift(s, k)能够且只能够使其中之一就位


/**
 * @brief 迭代版
 * 经多轮迭代，实现数组循环左移k位
 */
void shfit1(int *A, int n, int k) {
    // O(g) = O(GCD(n, k))
    for (int s = 0, mov = 0; mov < n; s++) {
        mov += shfit(A, n, s, k);
    }
}



/**
 * @brief 倒置版
 * 借助倒置算法，将数组循环左移k位
 * O(3n), 计算机会在访问的数据，取一个 连续的 page 放到一个高速缓存中，避免类io操作（在内存中取数）
 * reverse的操作是在连续的数据上
 */
void shfit2(int *A, int n, int k) {
    reverse(A, 0, k);     //O(3k/2)
    reverse(A, k, n-k);   //O(3(n-k)/2)
    reverse(A, 0, n);     //O(3n/2)
}

void reverse(int *A, int lo, int hi) {
    if (lo < hi) { // 规模问题的奇偶性不变，需要两个递归基(问题规模缩减为0或者1的时候，停止递归)
        swap(A[lo], A[hi]);
        reverse(A, lo+1, hi-1);
    }
    // else return; // base case 两种情况，区间宽度最小的奇数和最小的偶数
}


void swap(int &x, int &y) {
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}
