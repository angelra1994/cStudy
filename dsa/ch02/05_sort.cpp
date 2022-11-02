#include "05_sort.h"
/**
 * @brief 逐趟做扫描交换，直至全序（等价于 向量中任何一对相邻 元素都是彼此顺序的）
 * 每一趟扫描交换，都记录下是否存在逆序元素，存在充要条件是此前做过一次交换
 *
 */
template <typename T>
void bubbleSort0(Rank lo, Rank hi)
{
    while (!bubble0(lo, hi--))
        ;
}

/**
 * @brief 扫描交换
 * 乱序限于(0, √n)时，仍需O(n^(3/2))时间，按理O(n) 应该已经满足
 */
template <typename T>
bool bubble0(Rank lo, Rank hi)
{
    // 整体有序的标志
    bool sorted = true;
    while (++lo < hi) // 从左向右逐一检查各相邻元素
    {
        if (_elem[lo - 1] > _elem[lo]) // 若逆序，则说明整体无序
        {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]); // 需要交换，之后局部有序
        }
    }
    return sorted;
}


/**
 * @brief 逐趟扫描交换，直到全序
 */
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (lo <= (hi = bubble(lo, hi)))
        ;
}

template <typename T>
Rank Vector<T>::bubble(Rank lo, Rank hi)
{
    Rank last = lo;   // 右侧逆袭对初始化为[lo - 1, lo]
    while (++lo < hi) // 自左向右，逐一检查各对相邻元素
    {
        if (_elem[lo - 1] > _elem[lo]) // 若逆序
        {
            last = lo;                      // 更新最右侧逆序对位置
            swap(_elem[lo - 1], _elem[lo]); // 并交换
        }
    }
    return last; // 返回最右侧的逆序对位置
}

/**
 * @brief 基础版本
 */
template <typename T>
void bubbleSort1(Rank lo, Rank hi)
{
    while (lo < --hi)
    {                                         //逐趟起泡扫描
        for (Rank i = lo; i < hi; i++)        //逐对检查相邻元素
        {
            if (_elem[i] > _elem[i + 1])      //若逆序
            {
                swap(_elem[i], _elem[i + 1]); //则交换
            }
        }
    }
}


/**
 * @brief 提前终止版
 */
template <typename T>
void bubbleSort2(Rank lo, Rank hi)
{
    for (bool sorted = false; sorted = !sorted; hi--)
    {
        for (Rank i = lo + 1; i < hi; i++)
        {
            if (_elem[i - 1] > _elem[i])
            {
                swap(_elem[i - 1], _elem[i]);
                sorted = false;
            }
        }
    }
}

/**
 * @brief 跳跃版
 */
template <typename T>
void bubbleSort3(Rank lo, Rank hi)
{
    for (Rank last; lo < hi; hi = last)
    {
        for (Rank i = (last = lo) + 1; i < hi; i++)
        {
            if (_elem[i - 1] > _elem[i])
            {
                swap(_elem[i - 1], _elem[last = i]);
            }
        }
    }
}

template <typename T>
void mergeSort(Rank lo, Rank hi)
{
    if (hi - lo < 2) {  //单元素区间自然有序，否则...
        return
    }
    int mi = lo + (hi - lo) >> 1; //以中点为
    mergeSort(lo, mi);  //对前半段排序
    mergeSort(mi, hi); //对后半段排序
    merge(lo, mi, hi); //归并
}

/**
 * @brief [lo, mi) 和 [mi, hi) 各自有序
 */
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
    Rank i = 0;
    T *A = _elem + lo; // A = _elem[lo, hi)，就

    Rank j = 0;
    Rank lb = mi - lo;
    T *B = new T[lb]; // B[0, lb) <-- _elem[lo, mi) B需要另外开辟空间

    for (Ran i = 0; i < lb; i++)
    {
        B[i] = A[i];
    }
    Rank k = 0;
    Rank lc = hi - mi;
    T *C = _elem + mi; // C[0, lc] = _elem[mi, hi)，就地

    while ((j < lb) && (K < lc))
    {
        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
    }
    while (j < lb) //若C先耗尽，则
    {
        A[i++] = B[j++]; //将B残余的后缀归入A中
    }
    delete [] B;
}

void swap(int &x, int &y)
{
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}
