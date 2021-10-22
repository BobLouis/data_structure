#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int recursive(int i)
{
    if (!i)
        return 0;
    if (i == 1)
        return 1;

    return (recursive(i - 1) + recursive(i - 2));
}

int iterative(int i)
{
    int current = 1;
    int prev = 1;
    int preprev = 0;
    if (i > 1)
    {
        for (int j = 1; j < i; ++j)
        {
            current = prev + preprev;
            preprev = prev;
            prev = current;
        }
        return current;
    }
    else if (i == 0)
    {
        return 0;
    }
    else if (i == 1)
    {
        return 1;
    }
    return 0;
}

int main()
{
    char command[10];
    int n, num;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%10s", command);
        if (strcmp(command, "recursive") == 0)
        {
            scanf("%d", &num);
            printf("%d\n", recursive(num));
        }
        else if (strcmp(command, "iterative") == 0)
        {
            scanf("%d", &num);
            printf("%d\n", iterative(num));
        }
    }
}