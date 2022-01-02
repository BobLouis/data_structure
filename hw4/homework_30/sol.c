#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node
{
    int bit;
    bool *data;
    struct Node *l, *r;
} Node;

Node root;
int Bit = 0;
Node *newNode(bool *x, int b)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = (bool *)malloc(sizeof(bool) * Bit);
    for (int i = 0; i < Bit; ++i)
        tmp->data[i] = x[i];
    tmp->bit = b;
    return tmp;
}

Node search(Node t, bool *k)
{
    Node cur, next;
}

void printData(bool *x)
{
    for (int i = 0; i < Bit; i++)
        printf("%d ", x[i]);
}

int main()
{
    // scanf("%d", &Bit);
    Bit = 5;
    bool d[] = {0, 1, 0, 1, 0};
    Node *tmp = newNode(d, 5);
    printData(tmp->data);
    return 0;
}