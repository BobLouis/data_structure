#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int n = 100000;
    int m = n * 4;
    int dice;
    srand(time(NULL));
    printf("AVL\n");
    while (n--)
    {
        dice = (rand() % 100);
        if (dice < 50)
        {
            printf("search %d\n", rand() % INT16_MAX);
        }
        else if (dice < 75)
        {
            printf("delete %d\n", rand() % INT16_MAX);
        }
        else
        {
            printf("insert %d\n", rand() % INT16_MAX);
        }
    }
    printf("m\n");
    while (m--)
    {
        dice = (rand() % 100);
        if (dice < 50)
        {
            printf("search %d\n", rand() % INT16_MAX);
        }
        else if (dice < 75)
        {
            printf("delete %d\n", rand() % INT16_MAX);
        }
        else
        {
            printf("insert %d\n", rand() % INT16_MAX);
        }
    }
    printf("quit");
    return 0;
}