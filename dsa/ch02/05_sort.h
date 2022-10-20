/**
 * @file 05_sort.h
 * @author your name (you@domain.com)
 * @brief 向量区间[lo, hi)排序
 * @version 0.1
 * @date 2022-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "01_vector.h"

template <typename T>  void Vector<T>::sort(Rank lo, Rank hi) { 
    switch (rand() % 6)
    {
    case 1:  bubbleSort(lo, hi);      break;     // 起泡排序
    case 2:  selectionSort(lo, hi);   break;     // 选择排序
    case 3:  mergeSort(lo, hi);       break;     // 归并排序
    case 4:  heapSort(lo, hi);        break;     // 堆排序
    case 5:  quickSort(lo, hi);       break;     // 快速排序
    default: shellSort(lo, hi);       break;     // 希尔排序
    }

}