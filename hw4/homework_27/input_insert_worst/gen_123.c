#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int n;
    scanf("%d", &n);
    printf("-1\n");
    for (int i = n; i >= 1; i--)
    {
        printf("%d\n", i);
    }
}