#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 110

int map[MAX_N][MAX_N], visit[MAX_N];
int n;

void dfs(int x)
{
    printf("%d ", x);
    visit[x] = 1;
    for (int i = 0; i < n; ++i)
    {
        if (map[x][i] && !visit[i])
            dfs(i);
    }
}

int main()
{
    int round, start;
    scanf("%d", &round);
    while (round--)
    {
        memset(visit, 0, sizeof(visit));
        scanf("%d%d", &n, &start);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &map[i][j]);
        dfs(start);
        printf("\n");
    }
}