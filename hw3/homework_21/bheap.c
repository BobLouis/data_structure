#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100000

typedef struct Node
{
    int data, deg;
    struct Node *parent, *child, *sibling;
} Node;

Node *heap[MAX_N];
int heap_size = 0;

Node *new_node(int x)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = x;
    tmp->deg = 0;
    tmp->child = tmp->parent = tmp->sibling = NULL;
    return tmp;
}

Node *merge_tree(Node *b1, Node *b2)
{
    //make the parent smaller
    if (b1->data > b2->data)
    {
        b1->parent = b2, b1->sibling = b2->child;
        b2->child = b1, b2->deg++;
        return b2;
    }
    else
    {
        b2->parent = b1, b2->sibling = b1->child;
        b1->child = b1, b2->deg++;
        return b1;
    }
}

void adjust()
{
    if (heap_size <= 1)
        return;
    int i1 = 0, i2 = 1;
    while (i2 < heap_size)
    {
        if (heap[i1]->deg == heap[i2]->deg)
        {
            heap[i1] = merge_tree(heap[i1], heap[i2]);
            for (int i = i2 + 1; i < heap_size; i++)
                heap[i - 1] = heap[i];
            heap_size--;
            i1++;
            i2 = i1 + 1;
        }
        else
        {
            i1++;
            i2++;
        }
    }
}

void insert_node(int x)
{
}

int main()
{
    Node *b1 = new_node(1);
    Node *b2 = new_node(2);
    printf("%d", b1->data);
    return 0;
}