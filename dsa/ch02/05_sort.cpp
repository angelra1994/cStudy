#include "05_sort.h"
/**
 * @brief 逐趟做扫描交换，直至全序（等价于 向量中任何一对相邻 元素都是彼此顺序的）
 * 每一趟扫描交换，都记录下是否存在逆序元素，存在充要条件是此前做过一次交换
 *
 */
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!bubble(lo, hi--))
        ;
}

/**
 * @brief 扫描交换
 * 乱序限于(0, √n)时，仍需O(n^(3/2))时间，按理O(n) 应该已经满足
 */
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
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

void swap(int &x, int &y)
{
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}
