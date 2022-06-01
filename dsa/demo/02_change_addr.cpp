#include <iostream>
using namespace std;

int main()
{
    int a1 = 3, a2 = 5;
    int *p1 = &a1, *p2 = &a2;

    cout << "a1 " << a1 << " " << &a1 << endl;
    cout << "a2 " << a2 << " " << &a2 << endl;
    cout << "*p1 " << *p1 << " " << p1 << endl;
    cout << "*p2 " << *p2 << " " << p2 << endl;
    cout << endl;

    int *p = p1;
    p1 = p2;
    p2 = p;

    cout << "a1 " << a1 << " " << &a1 << endl;
    cout << "a2 " << a2 << " " << &a2 << endl;
    cout << "*p1 " << *p1 << " " << p1 << endl;
    cout << "*p2 " << *p2 << " " << p2 << endl;
    cout << endl;

    /* 輸出如下
    a1 3 0x61fe04
    a2 5 0x61fe00
    *p1 3 0x61fe04
    *p2 5 0x61fe00

    a1 3 0x61fe04
    a2 5 0x61fe00
    *p1 5 0x61fe00
    *p2 3 0x61fe04
    */

    return 0;
}
