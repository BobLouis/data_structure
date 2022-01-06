#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int n;
    scanf("%d", &n);
    printf("-1\n");
    for (int i = 1; i <= n / 2; i += 2)
    {
        printf("%d\n", (n / 2) + i);
        printf("%d\n", i);
    }
    for (int i = 1; i <= n / 2; i += 2)
    {
        printf("%d\n", (n / 2) + i + 1);
        printf("%d\n", i + 1);
    }
}