#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int n = 5000;
    int m = 5000;
    srand(time(NULL));
    printf("%d\n", n);
    while (n--)
    {
        printf("%d\n", rand() % INT16_MAX);
    }
    printf("%d\n", m);
    while (m--)
    {
        printf("0\n");
        printf("%d\n", rand());
    }
    // printf("%lu", sizeof(int));
    return 0;
}