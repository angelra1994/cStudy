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

| 操作                                           | 功能                               | 使用对象      |
| ---------------------------------------------- | ---------------------------------- | ------------- |
| size()                                         | 报告向量当前的规模（元素总数）     | 向量          |
| get(r)                                         | 获取秩为r的元素                    | 向量          |
| put(r, e)                                      | 用e替换秩为r元素的数值             | 向量          |
| insert(r, e)                                   | e作为秩为r元素插入，原后继依次后移 | 向量          |
| remove(r)                                      | 删除秩为r的元素，返回该元素原值    | 向量          |
| disordered()    返回相邻逆序对的个数           | 判断所有元素是否已按非降序排列     | 向量          |
| sort()                                         | 调整各元素的位置，使之按非降序排列 | 向量          |
| find(e)         返回 -1 非法rank，表示查找失败 | 查找目标元素e                      | 向量          |
| search(e)                                      | 查找e，返回不大于e且秩最大的元素   | 有序向量      |
| deduplicate(), uniquify()                      | 剔除重复元素                       | 向量/有序向量 |
| traverse()                                     | 遍历向量并统一处理所有元素         | 向量          |



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
- 递推式：$\frac{}{} ·log_2n = \lambda·[1+\alpha(\lambda)·log_2(\lambda n)]+(1-\lambda )·[2+\alpha(\lambda)·log_2((1-\lambda )n)]$
- 整理得：$\cfrac{-ln2}{\alpha(\lambda)} = \cfrac{\lambda · ln\lambda + (1-\lambda )·ln(1-\lambda )}{2-\lambda }$
- 当 $\lambda = \phi = (\sqrt5 - 1)/2时，\alpha(\lambda)=1.440420...$达到最小
