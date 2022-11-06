#include "01_list.h"
/**
 * @file 01_my_list.cpp
 * @brief 重载下标操作符，模仿向量的循秩访问
 *
 * 向量支持循秩访问（call-by-rank）：根据元素的秩，可在O(1)时间内直接确定其物理地址
 *         V[i]的物理地址 = V + i × s, s为党元素占用的空间量。 效率极高
 * 对于列表而言，寻秩访问成本过高，应改用循位置访问（call-by-position）的方式
 * 转而利用节点之间的相互引用，找到特定的节点
 * 
 */

template <typename T> // assert: 0 <= r <= size
T& List<T>::operator[] ( Rank r ) const  // O(r), 效率低下，只能偶尔使用，
{
    ListNodePosi<T> p = first(); // 从首节点出发
    while (0 < r--)
    {
        p = p->succ;   // 顺数第r个节点即是
    }
    return p->data;  // 目标节点
}// 任一节点的秩，亦为其前驱的总数

template <typename T>
void List<T>::init()
{ //初始化，创建列表对象时统一调用
    header = new ListNode<T>;   // 头哨兵
    trailer = new ListNode<T>;  // 尾哨兵
    header->succ = trailer;
    header->pred = NULL;
    trailer->prod = header;
    trailer->succ = NULL;
    _size = 0;                 // 对外可见的成员规模
}