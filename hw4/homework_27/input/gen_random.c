#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int n;
    srand(time(NULL));
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        printf("%d\n", rand() % INT32_MAX);
    }
}