#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10005

typedef struct Node
{
    int val;
    struct Node *parent;
    struct Node *child;
    int isRoot;
    int rank;
} Node;

Node *list[MAX_N];
int root[MAX_N];
int rank[MAX_N];
void init(int n)
{

    for (int i = 0; i < n; ++i)
    {
        list[i] = (Node *)malloc(sizeof(struct Node));
        list[i]->val = i;
        list[i]->parent = NULL;
        list[i]->child = NULL;
        list[i]->isRoot = 1;
        list[i]->rank = -1;
    }
}

int find(int a)
{
    Node *node = (Node *)malloc(sizeof(struct Node));
    node = list[a];
    // printf("%disRoot%d\n", a, node->isRoot);
    while (1)
    {
        if (node->isRoot)
        {
            return node->val;
        }
        else
        {
            node = node->parent;
        }
    }
    return 0;
}

int same(int a, int b)
{
    int a_root, b_root;
    a_root = find(a);
    b_root = find(b);
    return a_root == b_root ? 1 : 0;
}

int ranking(int a)
{
    Node *node = (Node *)malloc(sizeof(struct Node));
    node = list[a];
    while (1)
    {
        if (node->isRoot)
        {
            return node->rank;
        }
        else
        {
            node = node->parent;
        }
    }
    return 0;
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    int tmp = rank[a] + rank[b];
    if (ranking(a) <= ranking(b))
    {
        list[b]->parent = list[a];
        list[a]->rank = tmp;
        list[b]->isRoot = 0;
    }
    else
    {
        list[a]->parent = list[b];
        list[b]->rank = tmp;
        list[a]->isRoot = 0;
    }
}

int main()
{
    int round, ops, n;
    int a, b;
    char command[10];
    scanf("%d", &round);
    while (round--)
    {
        scanf("%d%d", &n, &ops);
        init(n);
        while (ops--)
        {
            scanf("%s", command);
            if (command[0] == 'u') //union
            {
                scanf("%d%d", &a, &b);
                unite(a, b);
            }
            else if (command[0] == 'f') //find
            {
                scanf("%d", &a);
                printf("%d\n", find(a));
            }
            else if (command[0] == 's') //same
            {
                scanf("%d%d", &a, &b);
                printf("%s\n", same(a, b) ? "true" : "false");
            }
        }
    }
    return 0;
}