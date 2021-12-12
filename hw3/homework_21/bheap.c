#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100000

typedef struct Node
{
    int data, deg;
    struct Node *parent, *child, *sibling;
} Node;

typedef struct Tree
{
    struct Node *main, *excess;
} Tree;

Tree *table[MAX_N];
int table_size = 1;

void init()
{
    Tree *tmp;

    for (int i = 0; i < MAX_N; ++i)
    {
        tmp = (Tree *)malloc(sizeof(Tree));
        tmp->main = NULL;
        tmp->excess = NULL;
        table[i] = tmp;
    }
}

Node *new_node(int x)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = x;
    tmp->deg = 0;
    tmp->child = tmp->parent = tmp->sibling = NULL;
    return tmp;
}

Node *merge(Node *b1, Node *b2)
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
        b1->child = b2, b1->deg++;
        return b1;
    }
}

void adjust()
{
    Node *tmp;
    for (int i = 0; i < table_size; ++i)
    {
        if (table[i]->main != NULL && table[i]->excess != NULL)
        {
            // printf("%d %d %d %d\n", table[i]->main->data, table[i]->main->deg, table[i]->excess->data, table[i]->excess->deg);
            tmp = merge(table[i]->main, table[i]->excess);
            // printf("%d %d %d %d", tmp->data, tmp->deg, tmp->child->data, tmp->child->deg);
            table[i]->main = table[i]->excess = NULL;
            if (!table[i + 1]->main)
            {
                table[i + 1]->main = tmp;
            }
            else
            {
                table[i + 1]->excess = tmp;
            }
            if ((i + 1) == table_size)
                ++table_size;
        }
    }
}

void insert_node(int x)
{
    Node *tmp = new_node(x);
    if (!table[0]->main)
    {
        table[0]->main = tmp;
    }
    else
    {
        table[0]->excess = tmp;
    }
}

int main()
{
    init();
    Node *ptr;
    for (int i = 0; i < 10; ++i)
    {
        insert_node(i);
        adjust();
    }
    printf("%d\n", table_size);
    for (int i = 0; i < table_size; i++)
    {
        printf("%p  %p \n", table[i]->main, table[i]->excess);
        if (table[i]->main)
        {
            for (ptr = table[i]->main; ptr != NULL; ptr = ptr->child)
                printf("deg %d data %d\n", ptr->deg, ptr->data);
        }
        printf("\n");
    }

    return 0;
}