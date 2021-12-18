#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    for (int i = table_size - 1; i >= 0; --i)
    {
        if (table[i]->main != NULL && table[i]->excess != NULL)
        {
            tmp = merge(table[i]->main, table[i]->excess);
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
    for (int i = 0; i < table_size; ++i)
    {
        if (table[i]->main != NULL && table[i]->excess != NULL)
        {
            tmp = merge(table[i]->main, table[i]->excess);
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
    adjust();
}

void print()
{
    Node *ptr, *sib;
    printf("size %d\n", table_size);
    for (int i = 0; i < table_size; i++)
    {
        printf("%d  %p  %p \n", i, table[i]->main, table[i]->excess);
        if (table[i]->main)
        {
            for (ptr = table[i]->main; ptr != NULL; ptr = ptr->child)
            {
                for (sib = ptr; sib != NULL; sib = sib->sibling)
                    printf("deg %d data %d  ", sib->deg, sib->data);
                printf("\n");
            }
        }
        printf("\n");
    }
}

Node *get_min()
{
    Node *tmp = NULL;
    for (int i = 0; i < table_size; ++i)
    {
        if (table[i]->main)
        {
            if (!tmp)
                tmp = table[i]->main;
            else
            {
                if (table[i]->main->data < tmp->data)
                    tmp = table[i]->main;
            }
        }
    }
    return tmp;
}

int pop_min()
{
    Node *pop = get_min();
    Node *tmp;
    for (Node *ptr = pop->child; ptr != NULL; ptr = tmp)
    {
        if (!table[ptr->deg]->main)
            table[ptr->deg]->main = ptr;
        else
            table[ptr->deg]->excess = ptr;
        tmp = ptr->sibling;
        ptr->sibling = NULL;
    }
    table[pop->deg]->main = NULL;
    adjust();
    return pop->data;
}

int main()
{
    init();
    clock_t start_t, end_t;
    int n, m, val, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        insert_node(x);
    }
    start_t = clock();
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &x);
        if (x)
            insert_node(x);
        else
            pop_min();
    }
    end_t = clock();
    printf("start: %lu end: %lu\n", start_t, end_t);
    printf("duration: %lu", end_t - start_t);

    return 0;
    // for (int i = 0; i < 5000; ++i)
    // {
    //     insert_node(i);
    // }

    // print();
    // for (int i = 0; i < 4990; ++i)
    // {
    //     printf("%d\n", pop_min());
    // }
    // print();
}