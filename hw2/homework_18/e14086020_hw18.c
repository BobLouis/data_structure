#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000010

typedef long long LL;

typedef struct Edge
{
    LL start; //start vertice
    LL end;   //end vertice
    LL cost;  //cost between the node
} Edge;

Edge arr[MAX_N << 1];
LL root[MAX_N], rank[MAX_N];
LL vert, edge;

void init()
{
    for (LL i = 0; i < vert; ++i)
    {
        root[i] = i;
        rank[i] = 0;
    }
}

LL find_root(LL x)
{
    return x == root[x] ? x : (root[x] = find_root(root[x]));
}

void unite(LL x, LL y)
{
    x = find_root(x);
    y = find_root(y);
    if (y > x)
    {
        root[x] = y;
    }
    else
    {
        root[y] = x;
        rank[x] += (rank[y] == rank[x]);
    }
}

int cmp(const void *a, const void *b)
{
    return ((Edge *)a)->cost - ((Edge *)b)->cost;
}

LL kruskal()
{
    LL ans = 0;
    qsort(arr, edge, sizeof(Edge), cmp);
    for (LL i = 0; i < edge; ++i)
    {
        if (find_root(arr[i].start) != find_root(arr[i].end))
        { //check if the edge form the cycle => check if they have the same root
            unite(arr[i].start, arr[i].end);
            ans += arr[i].cost;
        }
    }
    return ans;
}

int main()
{
    scanf("%lld%lld", &vert, &edge);
    init();
    for (int i = 0; i < edge; ++i)
    {
        scanf("%lld%lld%lld", &arr[i].start, &arr[i].end, &arr[i].cost);
    }
    printf("%lld\n", kruskal());
}