/**
 * 二分查找版本A转向左、右分支的关键码的关键码比较次数不等，但是递归深度相同
 * 递归深度的不均衡，对转向成本的不均衡实现补偿
 * 若 n = fib(k) - 1,则可取 mi = fib(k-1) - 1,此时的前后向量长度分别为fib(k-1)-1 和 fib(k-2)-1
 */

#include "01_vector.h"
#include "04_fib.h"

// Fibonacci查找算法（版本A）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
template <typename T> // 0 <= lo <= hi <= _size
static Rank fibSearch(T *S, T const &e, Rank lo, Rank hi)
{
     //用O(log_phi(n = hi - lo)时间创建Fib数列  
    for (Fib fib(hi - lo); lo < hi;)
    { // Fib数列制表备查；此后每步迭代仅一次比较、两个分支
        while (hi - lo < fib.get())
        {
            fib.prev(); //自后向前顺序查找轴点（分摊O(1)）
        }
        Rank mi = lo + fib.get() - 1; //确定形如Fib(k) - 1的轴点
        if (e < S[mi])
        {
            hi = mi; //深入前半段[lo, mi)
        }
        else if (S[mi] < e)
        {
            lo = mi + 1; //深入后半段(mi, hi)
        }
        else
        {

            return mi; //命中
        }
    }
    return -1; //失败
}//有多个命中元素时，不能保证返回秩最大者；失败时，简单地返回-1，而不能指示失败的位置
