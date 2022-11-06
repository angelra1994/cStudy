# 向量 Vector


$$
sequence \begin{cases} Vector\\ List\end{cases}
$$

$$
ADT/implementation\\
Algorithms \begin{cases} searching\\ sorting\end{cases}
$$



c/c++ 语言中，数组A[]中的元素与[0, n) 内的编号一一对应 （类似的高级语言中，数组是一段连续的内存空间）。
每一个元素均由（非负）编号唯一指代，可直接访问  A[i] 的物理地址 = A + i × s， s为单个元素占用的空间量，称之为线性组。

​		向量是数组的抽象与泛化，由一组元素按线性次序封装而成，各元素与[0, n)内的秩(rank)一一对应（call-by-rank  循秩访问），元素的类型不限于基本类型，操作、管理维护更加简化、统一和安全。可以更便捷的参与复杂数据结构的定制和实现。

**向量ADT接口**

|                                           操作 | 功能                               | 使用对象      |
| ---------------------------------------------: | ---------------------------------- | ------------- |
|                                         size() | 报告向量当前的规模（元素总数）     | 向量          |
|                                         get(r) | 获取秩为r的元素                    | 向量          |
|                                      put(r, e) | 用e替换秩为r元素的数值             | 向量          |
|                                   insert(r, e) | e作为秩为r元素插入，原后继依次后移 | 向量          |
|                                      remove(r) | 删除秩为r的元素，返回该元素原值    | 向量          |
|           disordered()    返回相邻逆序对的个数 | 判断所有元素是否已按非降序排列     | 向量          |
|                                         sort() | 调整各元素的位置，使之按非降序排列 | 向量          |
| find(e)         返回 -1 非法rank，表示查找失败 | 查找目标元素e                      | 向量          |
|                                      search(e) | 查找e，返回不大于e且秩最大的元素   | 有序向量      |
|                      deduplicate(), uniquify() | 剔除重复元素                       | 向量/有序向量 |
|                                     traverse() | 遍历向量并统一处理所有元素         | 向量          |



平均（average complexity）：根据各种操作出现概率的分布，将对应的成本加权平均

分摊（amortized complexity）：连续实施的足够多次操作，所需总体成本摊还至单次操作



- V.get(r)和V.put(r,e)不够便捷、直观，可否沿用数组的访问方式V[r]？
  可以！比如，通过**重载**下标操作符“[]”

```c++
//可作为左值：V[r] = (T) (2*x + 3)  因为接口的返回值是一个引用，可以作为左值
template <typename T> T & Vector<T>::operator[]( Rank r ) {
    return _elem[ r ]; 
}

//仅限于右值：T x = V[r] + U[s] * W[t]   进行运算，将计算结果赋给左值
template <typename T> const T & Vector<T>::operator[]( Rank r ) const {
    return _elem[ r ]; 
}
```

- 重载了下标操作符“[]”，对外的V[r] 即对应 内部的 V._elem[r]
- 这里采用了简易的方式处理意外和错误（比如，入口参数约定：0 <= r < _size



## 有序向量

- 无序向量：元素之间能比较是否相等，比对操作
- 有序向量：元素谁大谁小，比较大小
- 无序向量经过预处理转换为有序向量之后，相关算法多可优化



## 有序向量的查找

- 通用策略：在任何区间[0,n)内，总是选取[$\lambda$·n]作为轴点，0≤$\lambda$≤1；二分查找对应的λ是0.5，Fibonacci查找对应的λ=φ$\lambda=\phi=0.6180339...$
- 在[0,1)内，$\lambda$如何取值才能达到最优？设平均查找长度为$\alpha(\lambda)·log_2n=O(logn)$，常系数$\alpha(\lambda)$何时达到最小。
- 递推式：$\alpha(\lambda)·log_2n = \lambda·[1+\alpha(\lambda)·log_2(\lambda n)]+(1-\lambda )·[2+\alpha(\lambda)·log_2((1-\lambda )n)]$
- 整理得：$\cfrac{-ln2}{\alpha(\lambda)} = \cfrac{\lambda · ln\lambda + (1-\lambda )·ln(1-\lambda )}{2-\lambda }$
- 当 $\lambda = \phi = (\sqrt5 - 1)/2时，\alpha(\lambda)=1.440420...$达到最小

![image-20221003155505169](assets\image-20221003155505169.png)



二分查找以及fib查找均为严格兑现search()接口的语义约定：返回 **不大于e的最后一个元素的秩**

只有兑现这一约定，才能有效的支持相关算法，比如：V.insert(1+V.search(e), e)

- 当有多个命中元素时，必须返回最靠后（秩最大）者
- 失败时，应返回小于e的最大者（含哨兵[lo - 1]）



## 起泡排序

```c++
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
```



![image-20221022222506282](assets\image-20221022222506282.png)

- 此时多余出来的时间消耗就是，后缀中对于已经就位元素的反复扫描交换，需要及时分解出来



```c++
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
```



![image-20221022231235088](assets\image-20221022231235088.png)

- 算法的执行结果是梯形的时间

>  起泡排序中，元素a和元素b的相对位置发生变化只有一种可能，
>
> 分别与其它元素交换，a和b互相位置接近直至相邻；在接下来一轮的扫描交换中，二者因**逆序**而交换位置
>
> 起泡排序是稳定的，时间效率：最好O(n)，最坏O(n^2）



```c++
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
```

![image-20221103000937721](assets\image-20221103000937721.png)

```c++
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
```

![image-20221103000740292](assets\image-20221103000740292.png)

```c++
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
```

![image-20221103001005597](assets\image-20221103001005597.png)



## 归并排序

分治策略

- 序列一分为二，O(1)
- 子序列递归排序 2×T(n/2)
- 合并有序子序列 O(n)

优点

- 实现最坏情况下最优$\Omega(nlogn)$性能的第一个排序算法 
- 不需随机读写，完全顺序访问——尤其适用于列表之类的序列、磁带之类的设备
- 只要实现恰当，可保证稳定——出现雷同元素时，左侧子向量优先
- 可扩展性极佳，十分适宜于外部排序——海量网页搜索结果的归并
- 易于并行化 

缺点

- 非就地，需要对等规模的辅助空间——可否更加节省？
- 即便输入已是完全（或接近）有序，仍需$\Omega(nlogn)$时间



## Bitmap/位图

是一个向量，每一个成员都是一个bit

| 描述有限的整数集合 | $\forall 0\le k\le U: $             |                    |
| ------------------ | ----------------------------------- | ------------------ |
| k是否属于集合S     | $k\in S ?$                          | bool test(int k);  |
| k并到这个集合S     | $S \cup \left \{ k \right \} $      | void set(int k);   |
| 从集合S中减去k     | $S \setminus \left \{ k \right \} $ | void clear(int k); |

实现O(1)的复杂度







