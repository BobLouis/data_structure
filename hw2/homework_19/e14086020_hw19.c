#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//max vertices
#define MAX_N 1000007

typedef struct Edge
{
    int next_node;
    int next_edge;
    int cost;
} Edge;

Edge edge[MAX_N << 1];
int vert, root, count = 0;
int edge_idx[MAX_N], ans[MAX_N], vis[MAX_N];

void init()
{
    count = 0;
    memset(edge_idx, -1, sizeof(edge_idx)); //to make all the edge unused
    memset(ans, 0, sizeof(ans));
    memset(vis, 0, sizeof(vis));
}

void addEdge(int from, int to, int cost)
{
    edge[count].cost = cost;
    edge[count].next_node = to;
    edge[count].next_edge = edge_idx[from]; //edge[i].next_edge = -1 => end of node
    edge_idx[from] = count++;
}

void dfs(int x)
{
    vis[x] = 1;
    for (int i = edge_idx[x]; ~i; i = edge[i].next_edge)
    {
        if (!vis[edge[i].next_node])
        {
            ans[edge[i].next_node] += (edge[i].cost + ans[x]);
            dfs(edge[i].next_node);
        }
    }
    return;
}

int main()
{
    int n;
    int start, end, cost;
    int root;
    scanf("%d", &n);
    init();
    for (int i = 0; i < n - 1; ++i)
    {
        scanf("%d%d%d", &start, &end, &cost);
        addEdge(start, end, cost);
        addEdge(end, start, cost);
    }
    scanf("%d", &root);
    dfs(root);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d %d\n", i, ans[i]);
    }
}