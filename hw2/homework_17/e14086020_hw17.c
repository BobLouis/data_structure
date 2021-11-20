#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 110

typedef struct Node
{
    int val;
    struct Node *front;
    struct Node *back;
} Node;

Node *new_node(int x)
{
    Node *tmp = (Node *)malloc(sizeof(struct Node));
    tmp->val = x;
    tmp->front = NULL;
    tmp->back = NULL;
    return tmp;
}

int map[MAX_N][MAX_N], visit[MAX_N];
int n;
Node *q_front = NULL;

void in_q(int x)
{

    if (q_front == NULL)
    {
        q_front = new_node(x);
        return;
    }
    else
    {
        Node *tmp = new_node(x);
        Node *cur;
        for (cur = q_front; cur->back != NULL; cur = cur->back)
            ;
        cur->back = tmp;
        tmp->front = cur;
    }
}

int out_q()
{
    int val = q_front->val;
    if (q_front->back)
    {
        q_front = q_front->back;
        q_front->front = NULL;
    }
    else
    {
        q_front = NULL;
    }
    return val;
}

void bfs(int x)
{
    in_q(x);
    visit[x] = 1;
    while (q_front)
    {
        printf("%d ", (x = out_q()));
        for (int i = 0; i < n; ++i)
        {
            if (map[x][i] && !visit[i])
            {
                in_q(i);
                visit[i] = 1;
            }
        }
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
        bfs(start);
        printf("\n");
    }
}