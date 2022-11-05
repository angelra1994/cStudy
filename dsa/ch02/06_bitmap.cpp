#include "06_bitmap.h"

void Eratosthenes(int n, char *file)
{
    Bitmap B(n);
    B.set(0);
    B.set(1);                       // 0和1都不是素数
    for (int i = 2; i * i < n; i++) //逐个地
    {
        if (!B.test(i)) //确认下一个素数i
        {
            for (int j = i * i; j < n; j += i) //并将一系列能被i整除的
            {
                // j标记为合数（小于i*i的合数，必在此之前已被标记）
                B.set(j);
            }
        }
    }
    B.dump(file); //将筛选标记统一存入指定文件，以便日后直接导入
}