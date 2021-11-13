#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_N 100
//n represent the height and m represent the width of the array
int m, n, sum, map[MAX_N][MAX_N], vis[MAX_N][MAX_N];
int dir[8][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
void dfs(int x, int y)
{
    int cnt = 0, dx, dy, idx;
    while (cnt < n * m && sum < 50000)
    {
        if (!vis[x][y])
        {
            cnt++;
            vis[x][y] = 1;
        }
        sum++;
        map[x][y]++;
        idx = rand() % 8, dx = x + dir[idx][0], dy = y + dir[idx][1];
        while (dx < 0 || dy < 0 || dx >= n || dy >= m)
        {
            idx = rand() % 8, dx = x + dir[idx][0], dy = y + dir[idx][1];
        }
        x = dx, y = dy;
    }
}

void print_map()
{
    printf("%d\n", sum);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            printf("%4d", map[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    char ch;
    int tmp;
    while (scanf("%c", &ch) && ch != 'q')
    {
        sum = 0;
        memset(map, 0, sizeof(map));
        memset(vis, 0, sizeof(vis));
        if (ch == 'a')
        {
            scanf("%d%d", &n, &m);
            dfs(0, 0);
            print_map();
        }
        else if (ch == 'b')
        {
            scanf("%d", &tmp);
            if (tmp == 1)
            {
                n = m = 15;
                dfs(9, 9);
                print_map();
            }
            else
            {
                n = 39;
                n = 19;
                dfs(0, 0);
                print_map();
            }
        }
    }
}
