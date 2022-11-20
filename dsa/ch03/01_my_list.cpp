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

/**
 *  时间复杂度O(r)
 *  均匀分布时，期望复杂度为 (1+2+3+...+n)/n=O(n)
 */
template <typename T>                // assert: 0 <= r <= size
T &List<T>::operator[](Rank r) const // O(r), 效率低下，只能偶尔使用，
{
    ListNodePosi<T> p = first(); // 从首节点出发
    while (0 < r--)
    {
        p = p->succ; // 顺数第r个节点即是
    }
    return p->data; // 目标节点
} // 任一节点的秩，亦为其前驱的总数

template <typename T>
void List<T>::init()
{                              //初始化，创建列表对象时统一调用
    header = new ListNode<T>;  // 头哨兵
    trailer = new ListNode<T>; // 尾哨兵
    header->succ = trailer;
    header->pred = NULL;
    trailer->prod = header;
    trailer->succ = NULL;
    _size = 0; // 对外可见的成员规模
}

template <typename T> // e当作p的前驱插入
ListNodePosi<T> List<T>::insert(T const &e, ListNodePosi<T> p)
{
    _size++;
    return p->insertAsPred(e);
}

/**
 * 将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头节点header）
 */
template <typename T> //前插入算法（后插入算法完全对称）
ListNodePosi<T> ListNode<T>::insertAsPred(T const &e)
{                                                    // O(1)
    ListNodePosi<T> x = new ListNode(e, pred, this); //创建
    pred->succ = x;
    pred = x; //次序不可颠倒
    return x; //建立链接，返回新节点的位置
} //得益于哨兵，即便this为首节点亦不必特殊处理——此时等效于insertAsFirst(e)



template <typename T> //后插入算法（前插入算法完全对称）
ListNodePosi<T> ListNode<T>::insertAsSucc(T const &e)
{                                                    // O(1)
    ListNodePosi<T> x = new ListNode(e, this, succ); //创建
    succ->pred = x;
    succ = x; //设置逆向链接
    return x; //建立链接，返回新节点的位置
}


template <typename T> //删除合法位置p处节点，返回其数值
T List<T>::remove(ListNodePosi<T> p) // O(1)
{                  
    T e = p->data; //备份待删除节点数值（设类型T可直接赋值）
    p->pred->succ = p->succ;
    p->succ->pred = p->pred; //短路
    delete p;
    _size--;
    return e; //返回备份数值
}

template <typename T>
List<T>::~List() //列表析构
{
    clear();
    delete header;
    delete trailer;
} //清空列表，释放头、尾哨兵节点

template <typename T>
int List<T>::clear()
{ //清空列表
    int oldSize = _size;
    while (0 < _size) //反复删除首节点，O(n) 
    {
        remove(header->succ);
    }
    return oldSize;
} //P(n), 线性正比于列表规格

template <typename T>                             //列表内部方法：复制列表中自位置p起的n项
void List<T>::copyNodes(ListNodePosi<T> p, int n) // p合法，且至少有n-1个真后继节点
{
    init();     //创建头、尾哨兵节点并做初始化
    while (n--) //将起自p的n项依次作为末节点插入
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <typename T>
ListNodePosi<T> List<T>::insertAsFirst(T const &e)
{
    _size++;
    return header->insertAsSucc(e);
} // e当作首节点插入

template <typename T>
ListNodePosi<T> List<T>::insertAsLast(T const &e)
{
    _size++;
    return trailer->insertAsPred(e);
} // e当作末节点插入

template <typename T>
ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, T const &e)
{
    _size++;
    return p->insertAsSucc(e);
} // e当作p的后继插入

template <typename T>
ListNodePosi<T> List<T>::insert(T const &e, ListNodePosi<T> p)
{
    _size++;
    return p->insertAsPred(e);
} // e当作p的前驱插入

/**
 * @brief 在节点p(可能是trailer)的n个(真)前驱中，找到等于e的最后者
 */
template <typename T> // 0  n  rank(p) < _size
ListNodePosi<T> List<T>::find(T const &e, int n, ListNodePosi<T> p) const
{
    while (0 < n--)                   //自后向前
        if (e == (p = p->pred)->data) //逐个比对（假定类型T已重载“==”）
        {
            return p;                 //在p的n个前驱中，等于e的最靠后者
        }
    return NULL; //失败
} // O(n)

/**
 * @brief 剔除无序列表中的重复节点
 */
template <typename T>
int List<T>::deduplicate()
{
    int oldSize = _size;                             // 记录原规格
    ListNodePosi<T> p = first();                     // p从首节点起
    for (Rank r = 0; p != trailer; p = p->succ)      // O(n)
        if (ListNodePosi<T> q = find(p->data, r, p)) // O(n)
        {
            remove(q);
        }
        else
        {
            r++; //无重前缀的长度
        }
    return oldSize - _size; //删除元素总数
}

template <typename T>
void List<T>::traverse(void (*visit)(T &))
{
    for (NodePosi<T> p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit)
{
    for (NodePosi<T> p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}

/**
 * @brief 有序列表唯一化
 */
template <typename T>
int List<T>::uniquify()
{
    if (_size < 2)
    {
        return 0; //平凡列表自然无重复
    }
    int oldSize = _size; //记录原规模
    ListNodePosi<T> p = first();
    ListNodePosi<T> q;               //各区段起点及其直接后继
    while (trailer != (q = p->succ)) //反复考查紧邻的节点对(p,q)
        if (p->data != q->data)
        {
            p = q;                   //若互异，则转向下一对
        }
        else
        {
            remove(q);               //否则（雷同）直接删除后者，不必如向量那样间接地完成删除
        }
    return oldSize - _size;          //规模变化量，即被删除元素总数
} //只需遍历整个列表一趟，O(n)


/**
 * @brief  search(): 在有序列表内节点p的n个（真）前驱中，找到不大于e的最靠后者
 * 最好O(1)，最坏O(n)；等概率时平均O(n)，正比于区间宽度
 * 调用者可通过valid()判断成功与否
 */
template <typename T> //在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
ListNodePosi<T> List<T>::search(T const &e, int n, ListNodePosi<T> p) const
{
    // assert: 0 <= n <= rank(p) < _size
    do
    {
        p = p->pred;
        n--;
    }                                  //从右向左
    while ((-1 < n) && (e < p->data)); //逐个比较，直至命中或越界
    return p;                          //失败时，返回区间左边界的前驱（可能是header）
}

/**
 * @brief 对列表中起始于位置p、宽度为n的区间做选择排序
 */
template <typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n)
{
    ListNodePosi<T> head = p->pred, tail = p;
    for (int i = 0; i < n; i++)
    {
        tail = tail->succ;                //待排序区间为(head, tail)
    }                                     //警告预处理之后 head是[p-1], tail是（p+n） 
    while (1 < n)
    {                                                   //反复从（非平凡）待排序区间内找出最大者，并移至有序区间前端
        insert(remove(selectMax(head->succ, n)), tail); //可能就在原地...
        tail = tail->pred;
        n--; //待排序区间、有序区间的范围，均同步更新
    }
}

template <typename T> //从起始于位置p的n个元素中选出最大者，1 < n
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n)
{                                             //θ(n)
    ListNodePosi<T> max = p;                  //最大者暂定为p
    for (ListNodePosi<T> cur = p; 1 < n; n--) //后续节点逐一与max比较
    {
        // not less than, 即 ≥。当序列中存在重复的元素(多个max)，保证算法的稳定性，最靠后者作为交换的max
        if (!lt((cur = cur->succ)->data, max->data)) // data ≥ max  
        {
            // max会主次递增而不会下降，painter's aglorithms
            max = cur; //则更新最大元素位置记录

        }
    }
    return max; //返回最大节点位置
}

/**
 * @brief 对于列表起始位于p的连续n个元素做插入排序，valid(p) && rank(p) + n <= size
 */
template <typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n)
{
    // r是有序前缀的长度
    for (int r = 0; r < n; r++)
    {                                           //逐一引入各节点，由S(r)得到S(r+1)
        insert(search(p->data, r, p), p->data); //查找 + 插入
        p = p->succ;
        remove(p->pred); //转向下一节点
    }                    // n次迭代，每次O(r + 1)
} //仅使用O(1)辅助空间，属于就地算法 (in-place-aglorithms)
