#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void print_map(int *map, int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            printf("%3d ", map[i * m + j]);
        }
        printf("\n");
    }
}

// void print_route(int *route, int n, int m)
// {

// }

bool visit(int *map, int n, int m, int *route, int x, int y)
{
    route[y * m + x] = 1;
    map[y * m + x] = 2; //to represent go through
    if (x == m - 1 && y == n - 1)
    {
        return 1;
    }
    // right => right down => down => down left => left => left up => up => up right
    //right x+1
    if (x + 1 < m && map[y * m + x + 1] == 0)
    {
        if (visit(map, n, m, route, x + 1, y))
            return 1;
        else
            return 0;
    }
    //down y+1
    else if (y + 1 < n && map[(y + 1) * m + x] == 0)
    {
        if (visit(map, n, m, route, x, y + 1))
            return 1;
        else
            return 0;
    }
    //left x-1
    else if (x - 1 >= 0 && map[y * m + x - 1] == 0)
    {
        if (visit(map, n, m, route, x - 1, y))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //up y-1
    else if (y - 1 >= 0 && map[(y - 1) * m + x] == 0)
    {
        if (visit(map, n, m, route, x, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //right down x+1 y+1
    else if (x + 1 < m && y + 1 < n && map[(y + 1) * m + x + 1] == 0)
    {
        if (visit(map, n, m, route, x + 1, y + 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //left down  y+1 x-1
    else if (y + 1 < n && x - 1 >= 0 && map[(y + 1) * m + x - 1] == 0)
    {
        if (visit(map, n, m, route, x - 1, y + 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //left up x-1 y-1
    else if (x - 1 >= 0 && y - 1 >= 0 && map[(y - 1) * m + x - 1] == 0)
    {
        if (visit(map, n, m, route, x - 1, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //right up  x+1 y-1
    else if (y - 1 >= 0 && x + 1 < m && map[(y - 1) * m + x + 1] == 0)
    {
        if (visit(map, n, m, route, x + 1, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    //if can't find the way out trace back and mark as -1
    route[y * m + x] = 0;
    map[y * m + x] = -1;
    //right x+1
    if (x + 1 < m && map[y * m + x + 1] == 2)
    {
        if (visit(map, n, m, route, x + 1, y))
            return 1;
        else
            return 0;
    }
    //down y+1
    else if (y + 1 < n && map[(y + 1) * m + x] == 2)
    {
        if (visit(map, n, m, route, x, y + 1))
            return 1;
        else
            return 0;
    }
    //left x-1
    else if (x - 1 >= 0 && map[y * m + x - 1] == 2)
    {
        if (visit(map, n, m, route, x - 1, y))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //up y-1
    else if (y - 1 >= 0 && map[(y - 1) * m + x] == 2)
    {
        if (visit(map, n, m, route, x, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //right down x+1 y+1
    else if (x + 1 < m && y + 1 < n && map[(y + 1) * m + x + 1] == 2)
    {
        if (visit(map, n, m, route, x + 1, y + 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //left down  y+1 x-1
    else if (y + 1 < n && x - 1 >= 0 && map[(y + 1) * m + x - 1] == 2)
    {
        if (visit(map, n, m, route, x - 1, y + 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //left up x-1 y-1
    else if (x - 1 >= 0 && y - 1 >= 0 && map[(y - 1) * m + x - 1] == 2)
    {
        if (visit(map, n, m, route, x - 1, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //right up  x+1 y-1
    else if (y - 1 >= 0 && x + 1 < m && map[(y - 1) * m + x + 1] == 2)
    {
        if (visit(map, n, m, route, x + 1, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

bool print_route(int *route, int n, int m, int x, int y)
{
    printf("%d %d \n", y, x);
    route[y * m + x] = 0;
    if (x == m - 1 && y == n - 1)
    {
        return 1;
    }
    // right => right down => down => down left => left => left up => up => up right
    //right x+1
    if (x + 1 < m && route[y * m + x + 1] == 1)
    {
        if (print_route(route, n, m, x + 1, y))
        {
            return 1;
        }

        else
            return 0;
    }
    //down y+1
    else if (y + 1 < n && route[(y + 1) * m + x] == 1)
    {
        if (print_route(route, n, m, x, y + 1))
            return 1;
        else
            return 0;
    }
    //left x-1
    else if (x - 1 >= 0 && route[y * m + x - 1] == 1)
    {
        if (print_route(route, n, m, x - 1, y))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //up y-1
    else if (y - 1 >= 0 && route[(y - 1) * m + x] == 1)
    {
        if (print_route(route, n, m, x, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //right down x+1 y+1
    else if (x + 1 < m && y + 1 < n && route[(y + 1) * m + x + 1] == 1)
    {
        if (print_route(route, n, m, x + 1, y + 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //left down  y+1 x-1
    else if (y + 1 < n && x - 1 >= 0 && route[(y + 1) * m + x - 1] == 1)
    {
        if (print_route(route, n, m, x - 1, y + 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //left up x-1 y-1
    else if (x - 1 >= 0 && y - 1 >= 0 && route[(y - 1) * m + x - 1] == 1)
    {
        if (print_route(route, n, m, x - 1, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //right up  x+1 y-1
    else if (y - 1 >= 0 && x + 1 < m && route[(y - 1) * m + x + 1] == 1)
    {
        if (print_route(route, n, m, x + 1, y - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}
int main()
{
    int n, m;
    int *map;
    int *route;
    scanf("%d %d\n", &n, &m);
    map = malloc(n * m * sizeof(int));
    route = malloc(n * m * sizeof(int));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (getchar() == '1')
                map[i * m + j] = 1;
            else
                map[i * m + j] = 0;
            getchar();
        }
    }
    if (visit(map, n, m, route, 0, 0))
    {
        print_route(route, n, m, 0, 0);
    }
    else
    {
        printf("no answer");
    }
    return 0;
}