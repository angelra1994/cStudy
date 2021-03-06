#include <iostream>
#include <stdio.h>
void swap(int &x, int &y);
void swap1(int *x, int *y);
using namespace std;
int main(int argc, char const *argv[])
{
    /* 不要c和c++杂糅起来编程，可读性差 */
    /* iostream是c++的, stdio.h是c的 */
    /* 包含iostream就不包含stdio.h了, 使用cout输出 */
    /* c++写.h，不过.h的目的，一般是声明类 */
    cout << "before reverse" << endl;
    int a[5] = {0,1,2,3,4};
    int len = sizeof(a)/sizeof(a[0]);
    for (size_t i = 0; i < len; i++) {
        printf("a[%d] is %d \n", i,  a[i]);
        printf("&a[%d] is %d \n", i,  &a[i]);
    }
    swap(a[1], a[2]);
    cout << "after reverse" << endl;
    for (size_t i = 0; i < len; i++) {
        printf("a[%d] is %d \n", i,  a[i]);
        printf("&a[%d] is %d \n", i,  &a[i]);
    }

    int a1 = 1;
    int a2 = 2;
    printf("a1 is %d, &a1 is %d \n", a1, &a1);
    printf("a2 is %d, &a2 is %d \n", a2, &a2);
    swap(a1, a2);
    printf("a1 is %d, &a1 is %d \n", a1, &a1);
    printf("a2 is %d, &a2 is %d \n", a2, &a2);

    cout << "use *x" << endl;
    swap1(&a[1], &a[2]);
    cout << "after reverse" << endl;
    for (size_t i = 0; i < len; i++) {
        printf("a[%d] is %d \n", i,  a[i]);
        printf("&a[%d] is %d \n", i,  &a[i]);
    }
    
    swap1(&a1, &a2);
    printf("a1 is %d, &a1 is %d \n", a1, &a1);
    printf("a2 is %d, &a2 is %d \n", a2, &a2);

    return 0;
}

void swap(int &x, int &y) {
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}

/**
 * 如果传入&[1]，那形参必须是指针类型
 */
void swap1(int *x, int *y) {
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}
