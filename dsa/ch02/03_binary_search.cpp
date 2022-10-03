#include "01_vector.h"

/**
 * 二分查找(版本A): 在有序向量的区间[lo, hi)内查找元素e, 0≤lo≤hi≤_size
 * 有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地返回-1，而不能指示失败的位置
 * 线性“递归”：T(n) = T(n/2)+O(1)=O(logn), 大大优于顺序查找
 * “递归”跟踪：轴点总能取到中点，递归深度 O(logn) ；各递归实例仅耗时O(1)
 * 版本A的平均查找长度(需分别针对成功与失败查找，从最好、最坏、平均等角度评估，比较的次数)，大约为O(1.50logn)
 */
template <typename T>
static Rank binSearchA(T *S, T const &e, Rank lo, Rank hi)
{
    while (lo < hi) //每步迭代可能要做两次比较判断，有三个分支
    {
        //以中点为轴点（区间宽度的折半，等效于宽度之数值表示的右移）
        Rank mi = (lo + hi) >> 1;
        if (e < S[mi])
        {
            hi = mi; //深入前半段[lo, mi)继续查找
        }
        else if (S[mi] < e)
        {
            lo = mi + 1; //深入后半段(mi, hi)继续查找
        }
        else
        {
            return mi; //在mi处命中，此时区间宽度时0 lo=hi=mi
        }
    }
    return -1;
}

/**
 * 版本A的二分查找：转向左(+1)、右分支(+2)前的关键码比较次数不等，而递归深度却相同。
 * 越是成本低的转向越希望走，越是成本高的越少走 -> fib_search
 * 
 * 也可直接解决，每次迭代仅做1次关键码比较；如此，所有分支只有2个方向，而不再是3个
 */

/**
 * 轴点mi取作中点，则查找每深入一层，问题规模依然会缩减一半
 * - e < x：则深入左侧的[lo, mi)
 * - x <= e：则深入右侧的[mi, hi)
 * 直到 hi - lo = 1，才明确判断是否命中
 */
template <typename T>
static Rank binSearchB(T *S, T const &e, Rank lo, Rank hi)
{
    while (1 < hi - lo)
    {                             //有效查找区间的宽度缩短至1时，算法才终止
        Rank mi = (lo + hi) >> 1; //以中点为轴点，经比较后确定深入[lo, mi)或[mi, hi)
        e < S[mi] ? hi = mi : lo = mi;
    } //出口时hi = lo + 1，查找区间仅含有一个元素A[lo]
    return e == S[lo] ? lo : -1;
}// 相较于版本A，最好(坏)情况下更坏(好)；各种情况下的SL更加接近，整体性能更趋稳定

/**
 * 不变性：A[0, lo) ≤ e < A[hi, n)
 * 初始时，lo=0，hi=n，A[0, lo) = A[hi, n) = ∅，自然成立
 *  A[lo-1] 总是（截至当前已确认的）不大于e的最大者（m）
 *  A[hi] 总是（截至当前已确认的）大于e的最小者（M）
 * 当算法终止时，A[lo-1] = A[hi-1]即是（全局）不大于e的最大者
 */ 
template <typename T>
static Rank binSearchC(T *S, T const &e, Rank lo, Rank hi)
{
    while (lo < hi)
    { //不变性：A[0, lo) <= e < A[hi, n)
        Rank mi = (lo + hi) >> 1;
        e < S[mi] ? hi = mi : lo = mi + 1; //[lo, mi)或(mi, hi)，A[mi]或被遗漏？
    }                                      //出口时，区间宽度缩短至0，且必有S[lo = hi] = M
    return lo - 1;                         //故，S[lo-1] = m
} 

/**
* 版本A和B都是，对于查找失败返回，-1。A的最优时间复杂度为O(1),B的最优时间复杂度是O(log_2n)
* 版本C无论成功与否，返回的秩必然会严格地符合接口的语义约定...
*/
