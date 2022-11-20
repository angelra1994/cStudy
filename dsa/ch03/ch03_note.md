# 列表 List

是否修改数据结构，操作分为

- 静态操作： 仅读取，数据结构的内容及组成一般不变：get、search 
- 动态操作： 需写入，数据结构的局部或整体将改变：put、insert、remove

数据元素的存储与组织策略也存在两种方式

- 静态存储： 数据空间整体创建或销毁，数据元素的**物理存储次序**与其**逻辑次序**严格一致；可支持高效的**静态**操作。比如向量，元素的物理地址与其逻辑次序线性对应
- 动态存储：为各数据元素动态地分配和回收的物理空间，**逻辑上相邻元素记录彼此的物理地址**，在逻辑上形成一个整体；可支持**高效**的动态操作



## 列表（list）是采用动态储存策略的典型结构

- 其中的元素称作节点（node），通过指针或引用彼此联接，在逻辑上构成一个线性序列：L = { a0, a1, ..., an-1 }
- 相邻节点彼此互称前驱（predecessor）或后继（successor），前驱或后继存在，则必然唯一。
- 没有前驱/后继的唯一节点称作首（first/front）/末（last/rear）节点
- 列表节点的秩和物理节点没有明确的对立关系

![image-20221106232050049](assets\image-20221106232050049.png)



**ListNode ADT接口**

作为列表的基本元素 列表节点首先需要 独立地“封装”实现

列车 ~ 车厢 ~ 货物 list ~ node ~ data

|            操作 | 功能                                          |
| --------------: | --------------------------------------------- |
|          pred() | 当前节点前驱节点的位置                        |
|          succ() | 当前节点后继节点的位置                        |
|          data() | 当前节点所存数据对象                          |
| insertAsPred(e) | 插入前驱节点，存入被引用对象e，返回新节点位置 |
| insertAsSucc(e) | 插入后继节点，存入被引用对象e，返回新节点位置 |



**List ADT接口**

|                          操作接口 | 功能                                 | 适用对象      |
| --------------------------------: | ------------------------------------ | ------------- |
|                            size() | 报告列表当前的规模（节点总数）       | 列表          |
|                   first(), last() | 返回首、末节点的位置                 | 列表          |
| insertAsFirst(e), insertAsLast(e) | 将e当作首、末节点插入                | 列表          |
|        insert(p, e), insert(e, p) | 将e当作节点p的直接**后继、前驱**插入 | 列表          |
|                         remove(p) | 删除位置p处的节点，返回其中数据项    | 列表          |
|                      disordered() | 判断所有节点是否已按非降序排列       | 列表          |
|                            sort() | 调整各节点的位置，使之按非降序排列   | 列表          |
|                           find(e) | 查找目标元素e，失败时返回NULL        | 列表          |
|                         search(e) | 查找e，返回不大于e且秩最大的节点     | 有序列表      |
|         deduplicate(), uniquify() | 剔除重复节点                         | 列表/有序列表 |
|                        traverse() | 遍历列表                             | 列表、        |

```c++
#include "listNode.h" //引入列表节点类
template <typename T> class List { //列表模板类
	private: int _size; ListNodePosi<T> header, trailer; //哨兵
	//头、首、末、尾节点的秩，可分别理解为-1、0、n-1、n
	protected: /* ... 内部函数 */
	public: /* ... 构造函数、析构函数、只读接口、可写接口、遍历接口 */
};
```

头尾哨兵是不可见的

首末是对外可见的

![image-20221106234810285](assets\image-20221106234810285.png)



- 按照循位置访问的方式，物理存储地址与其逻辑次序无关 
- 依据秩的随机访问无法高效实现，而只能依据元素间的引用顺序访问

![image-20221119190848499](assets\image-20221119190848499.png)



## 选择排序

有序的部分是后缀，在序的前缀中找到最大值的最后者放到有序后缀的首位中。**U**+**S**
且无序前缀都比有序的后缀最小值小
选择排序没有最好最坏情况，都是$\Theta(n^2)$的复杂度

```c++
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
```



![image-20221120110601569](assets\image-20221120110601569.png)



分析：

- 利用remove接口返回需要被删除的元素，在insert到有序部分的最前端。
- remove(delete)和insert(insert)都涉及动态空间分配

```c++
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
```

共迭代n次，在第k次迭代中

- selectMax() 为 $\Theta(n-k)$ //算术级数 
- swap() 为 O(1) //或 remove() + insert() 

花费于每次挑选最大元的工作量体现为算数级数的形式，故总体复杂度应为 $\Theta(n^2)$

尽管如此，元素的**移动**操作远远少于起泡排序              //实际更为费时 
也就是说， $\Theta(n^2)$主要来自于元素的比较操作             //成本相对更低
可否...每轮只做o(n)次比较，即找出当前的最大元素？
可以！...利用高级数据结构，selectMax()可改进至O(logn)            //稍后分解 
当然，如此立即可以得到O(nlogn)的排序算法                                 //保持兴趣



## 插入排序

有序部分是前缀，将无序后缀的第一个元素插入到有序部分中。**S**+**U**
无序后缀的大小和有序前缀无关

![image-20221120120912415](assets\image-20221120120912415.png)

```c++
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
```

- 最好的场景：完全（或几乎）有序  ， 每次迭代，只需**1**次比较，**0**次交换，累计**O(n)**时间
- 最好的场景：完全（或几乎）逆序   ， 第**k**次迭代，需要O(k)次比较，1次交换，累计**$O(n^2)$**时间 （List）
   第**k**次迭代，需要O(logn)次比较，n次交换，累计$O(n^2)$时间 （Vector）

![image-20221120125528056](assets\image-20221120125528056.png)

- 平均情况（后向分析 backward Analysis） 若各元素的取值系独立均匀分布，平均要做多少次元素比较？
  考查e=[r]刚插入完成的那一时刻...此时的有序前缀[0,r]中，其中的r+1个元素均有可能是e，概率均为1/(r+1)
  刚完成的这次迭代中，引入S[r]所花费时间的数学期望为 $1 + \sum_{k=0}^{r} \cfrac{k}{r+1}=1 +\cfrac{r}{2}$ 
  总体时间的数学期望位为$\sum_{k=0}^{n-1}(1+\cfrac{r}{2})=\O(n^2)$ 

## 逆序对

inversion

插入排序是输入敏感的，数据的逆序对的程度，影响排序的耗时

![image-20221120131613403](assets\image-20221120131613403.png)
