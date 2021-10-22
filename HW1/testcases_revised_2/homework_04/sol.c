#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_complete(int n, int m, int *map);
int visit(int *map, int n, int m, int *step, int *x, int *y);
int move(int *map, int n, int m, int *x, int *y, int direction);
void print_map(int *map, int n, int m);

int check_complete(int n, int m, int *map)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int index = i * m + j;
            if (map[index] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}
int visit(int *map, int n, int m, int *step, int *x, int *y)
{
    if (check_complete(n, m, map))
        return 1;

    while (!move(map, n, m, x, y, (rand() % 8)))
        ;
    *step += 1;
    if (visit(map, n, m, step, x, y))
        return 1;
    else
        return 0;
}
int move(int *map, int n, int m, int *x, int *y, int direction)
{

    switch (direction)
    {
    case 0:
        if (*x - 1 >= 0 && *y + 1 < n)
        {
            *x -= 1;
            *y += 1;
            map[*y * m + *x]++;
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 1:
        if (*y + 1 < n)
        {
            *y += 1;
            map[*y * m + *x]++;
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 2:
        if (*x + 1 < m && *y + 1 < n)
        {
            *y += 1;
            *x += 1;
            map[*y * m + *x]++;
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 3:
        if (*x + 1 < m)
        {
            *x += 1;
            map[*y * m + *x]++;
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 4:
        if (*x + 1 < m && *y - 1 >= 0)
        {
            *x += 1;
            *y -= 1;
            map[*y * m + *x]++;
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 5:
        if (*y - 1 >= 0)
        {
            *y -= 1;
            map[*y * m + *x]++;
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 6:
        if (*x - 1 >= 0 && *y - 1 >= 0)
        {
            *x -= 1;
            *y -= 1;
            map[*y * m + *x]++;
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 7:
        if (*x - 1 >= 0)
        {
            *x -= 1;
            map[*y * m + *x]++;
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    }
    printf("undefined direction");
    return -1;
}
void print_map(int *map, int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            printf("%4d ", map[i * m + j]);
        }
        printf("\n");
    }
}
int main()
{
    srand(time(0));
    int *map;
    char ch;
    int step = 0;
    int x = 1;
    int y = 1;
    int n;
    int m;
    int id;
    //make the map start from (0,0)
    x -= 1;
    y -= 1;
    // malloc the array

    while (scanf("%c", &ch) && ch != 'q')
    {
        if (ch == 'a')
        {
            scanf("%d%d", &n, &m);
            map = malloc(n * m * sizeof(int));
            //reset the array to zero
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    map[i * m + j] = 0;
                }
            }
            x = y = 1;
            visit(map, n, m, &step, &x, &y);
            printf("%d\n", step);
            print_map(map, n, m);
            free(map);
        }
        else
        {
            scanf("%d", &id);
            if (id == 1)
            {
                n = m = 15;
                map = malloc(n * m * sizeof(int));
                //reset the array to zero
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < m; ++j)
                    {
                        map[i * m + j] = 0;
                    }
                }
                x = y = 10;
                visit(map, n, m, &step, &x, &y);
                printf("%d\n", step);
                print_map(map, n, m);
                free(map);
            }
            else
            {
                n = 39;
                m = 19;
                map = malloc(n * m * sizeof(int));
                //reset the array to zero
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < m; ++j)
                    {
                        map[i * m + j] = 0;
                    }
                }
                x = y = 1;
                visit(map, n, m, &step, &x, &y);
                printf("%d\n", step);
                print_map(map, n, m);
                free(map);
            }
        }
        getchar();
    }
    return 0;
}