#include <stdlib.h>
#include <stdio.h>
int main()
{
    long num = 0;
    int tmp;
    for (int i = 0; i < 741; ++i)
    {
        scanf("%d", &tmp);

        num += tmp;
        printf("total:%lu tmp:%d\n", num, tmp);
    }
    printf("total num %lu", num);
}