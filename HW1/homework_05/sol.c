#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 1000

struct step
{
    int x, y;
} ans[MAX_N];

int n, m, idx = 0, map[MAX_N][MAX_N], vis[MAX_N][MAX_N];
int dir[8][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
int dfs(int x, int y)
{
    vis[x][y] = 1;
    if (x == n && y == m)
    {
        ans[++idx] = (struct step){x, y};
        return 1;
    }
    for (int i = 0, dx, dy; i < 8; ++i)
    {
        dx = x + dir[i][0], dy = y + dir[i][1];
        if (!map[dx][dy] && !vis[dx][dy] && dfs(dx, dy))
        {
            ans[++idx] = (struct step){x, y};
            return 1;
        }
    }
    return 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(map, -1, sizeof(map));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &map[i][j]); //start with map[1][1] to map[n][m] circle the map with -1
        }
    }
    dfs(1, 1);
    if (idx)
    {
        for (int i = idx; i > 0; --i)
        {
            printf("%d %d\n", ans[i].x - 1, ans[i].y - 1);
        }
    }
    else
    {
        printf("no answer");
    }
}