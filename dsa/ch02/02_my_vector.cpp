# include "01_template_vector.cpp"

 //T为基本类型，或已重载赋值操作符'='
template <typename T> 
void Vector<T>::copyFrom( T const * A, Rank lo, Rank hi ) { //A中元素不致被篡改
    _elem = new T[ _capacity = max( DEFAULT_CAPACITY, 2*(hi - lo) ) ]; //分配空间
    //A[lo, hi)内的元素，逐一
    for ( _size = 0; lo < hi; _size++, lo++ ) {
        _elem[ _size ] = A[ lo ]; //复制至_elem[0, hi-lo)
    } 

    // _size = 0; // 规模清零
    // while (lo < hi) {
    //     _elem[_size++] = A[lo++]; // 复制至_elem[0, hi-lo) 
    // }
}
/**
 * 递增策略扩容： T* oldElem = _elem; _elem = new T[ _capacity += INCREMENT ]; //追加固定增量
 * 最坏情况：在初始容量0的空向量中，连续插入 n=m·I 个元素，而无删除操作
 * 即便不计申请空间操作，各次扩容过程中复制原向量的时间成本依次为
 *     0, I, 2I, 3I ... (m-1)·I                 //算术级数
 * 总体耗时 = O(n^2)，每次（insert/remove）操作的分摊成本为 O(n)
 * 
 * 加倍策略扩容： T* oldElem = _elem; _elem = new T[ _capacity <<= 1 ]; //容量加倍
 * 最坏情况：在初始容量1的满向量中，连续插入 n=2^m >> 2 个元素，而无删除操作
 * 各次扩容过程中复制原向量的时间成本依次为
 *      1, 2, 4, 8 ... 2^(m-1), 2^m = n         //几何级数
 * 总体耗时 = O(n)，每次（insert/remove）操作的分摊成本为 O(1)
 */
template <typename T> 
void  Vector<T>::expand() {  // 向量空间不足时扩容
    if( _size < _capacity) { // 尚未满，不需要扩容
        return;
    }
    _capacity = max(_capacity, DEFAULT_CAPACITY); // 不低于最小容量
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];               // 容量翻倍
    for (Rank i = 0; i < _size; i++) {            // 复制原向量内容
        _elem[i] = oldElem[i];                    // T为基本类型，或已重载赋值操作符'='                      
    } 
    delete [] oldElem;                            // 释放原空间
} // 得益于向量的封装，尽管扩容之后数据区的物理地址有所改变，却不至于出现野指针

// e作为秩为r的元素插入
template <typename T> Rank Vector<T>::insert( Rank r, T const & e ) { //0<=r<=size
    expand(); //若有必要，扩容
    //O(n-r)：自后向前 
    for ( Rank i = _size; r < i; i-- ) {
        _elem[i] = _elem[i - 1]; //后继元素顺次后移一个单元
    }
    _elem[r] = e; 
    _size++; 
    return r; //置入新元素，更新容量，返回秩
}

/**
 * @brief 区间删除，删除区间[lo, hi), 0 <= lo < hi <= _size
 * @return int  返回被删除元素的数目
 */
template <typename T> int Vector<T>::remove( Rank lo, Rank hi ) { //0<=lo<=hi<=n
    //出于效率考虑，单独处理退化情况
    if ( lo == hi ) {
        return 0; 
    }
    //O(n-hi)：[hi, _size) 自前向后 顺次前移
    while ( hi < _size ) {
        _elem[ lo ++ ] = _elem[ hi ++ ]; 
    }
    _size = lo; 
    //更新规模，若有必要则缩容
    shrink();
    return hi - lo; //返回被删除元素的数目
}

// 单元素删除，视作为区间删除的特例: [r] = [r, r+)
template <typename T> T Vector<T>::remove( Rank r ) {
    T e = _elem[r]; //备份
    remove( r, r+1 ); //“区间”删除
    return e; //返回被删除元素
} //O(n-r)

// 由区间删除实现单元素删除， 即循环调用单元素删除
// 每次循环时，正比于删除区间的后缀长度 n - hi = O(n)，而循环次数等于区间宽度 hi - lo =O(n)
// 这样将会导致 总体O(n^2)的复杂度


/**
 * @brief 查找
 * 无序向量：T为可判等的基本类型，或已重载操作符 "==" 或 "!="
 * 有序向量：T为可比较的基本类型，或已重载操作符 "<" 或 ">"
 * 词条类 Entry
 */
template <typename T> Rank Vector<T>::find(T const & e, Rank lo, Rank hi) const {
    //0 <= lo < hi <= _size 逆向查找
    while ((lo < hi--) && (e != _elem[hi])) { 
        
    }
    //返回值小于lo即意味着失败；否则即命中者的秩（有多个时，返回最大者）
    return hi;
    
}
// 输入敏感(input-sensitive)的算法: 最好O(1)，最差O(n)  特点：最好最坏情况，差异很大

/**
 * @brief 去重
 * 删除重复元素，返回被删除元素数目
 * 
 * 不变性：在当前元素V[i]的前缀V[0,i)中，各元素彼此互异
 *        初始 i=1 时，自然成立，一般情况下，数学归纳法
 * 单调性：当前元素的前缀长度单调非降，且迟早增至_size
 *        当前元素的后缀长度单调下降，且迟早减至0
 * 算法必将终止，且最多迭代O(n)轮；每轮迭代中find()和remove()累计消耗线性时间。总体是O(n^2)
 * 
 * 优化：
 * 1. 仿照uniquify()高效版的思路，元素移动的次数可降至O(n)，但比较此时依旧是O(n^2)；而且稳定性将被破坏
 * 2. 先对需要删除的重复元素做标记，之后再统一删除；稳定性保持，但因查找长度更长，从而导致更多的对比操作
 * 3. V.sort().uniquify(): 简明实现最优的O(nlogn)
 */
template <typename T> Rank Vector<T>::deduplicate() {
    Rank oldSize = _size;                       // 记录原规模
    for (Rank i = 1; i < _size;) {              // 从 _elem[1]开始，自前向后逐一考察各元素_elem[i]
        if ( find(_elem[i], 0, i) < 0 ) {       // 在前缀中寻找雷同者
            i++;                                // 若无雷同者则继续考察其后继
        } else {                                   
            remove(i);                          // 否则剔除雷同者（至多一个？！）
        }
    }
    return oldSize - _size;                     // 向量规模变化量，为删除的元素个数  
}

/**
 * @brief 遍历向量，统一对各元素分别实施visit操作，如何制定visit操作？如何将其传递到向量内部？
 * 1. 利用函数指针机制，只读或局部性修改
 * 2. 利用函数对象机制，可全局性修改  通用性更强
 */
// 函数指针  *visit
template <typename T> void Vector<T>::traverse(void (*visit)(T&)) {
    for ( Rank i = 0; i < _size; i++ ) {
        visit( _elem[i] );
    } 
}
// 函数对象  VST& visit
template <typename T> template <typename VST> void Vector<T>::traverse(VST& visit) {
    for ( Rank i = 0; i < _size; i++ ) {
        visit( _elem[i] );
    } 
}


/**
 * 统一将向量中所有元素分别加一，
 * 首先，实现一个可使单个T类型元素加一的类
 */
//假设T可直接递增或已重载操作符“++”， 函数对象：通过重载操作符“()”实现
template <typename T>  struct Increase { 
    virtual void operator()( T & e ) {
        //加一
        e++; 
    } 
}; 
 //将其Increase 作为参数传递给遍历算法，即可以之作为基本操作，遍历向量
template <typename T> void increase( Vector<T> & V ) {
    V.traverse( Increase<T>() ); 
}
// 练习，模仿此例，实现统一的减一、加倍、求和等遍历功能



