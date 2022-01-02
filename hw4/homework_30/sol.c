#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node
{
    int bit;
    bool *data;
    int val;
    struct Node *l, *r;
} Node;

Node *root = NULL;
int Bit = 0;
Node *newNode(bool *x, int b, int value)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = (bool *)malloc(sizeof(bool) * Bit);
    for (int i = 0; i < Bit; ++i)
        tmp->data[i] = x[i];
    tmp->bit = b;
    tmp->val = value;
    return tmp;
}

bool bit(bool *x, int b)
{
    return x[b - 1];
}

Node *search(bool *k)
{
    Node *cur, *next;
    if (!root)
        return NULL; //empty
    next = root->l;
    cur = root;
    while (next->bit > cur->bit)
    {
        cur = next;
        next = (bit(k, next->bit)) ? next->r : next->l;
    }
    return next;
}

bool isEq(bool *a, bool *b)
{
    for (int i = 0; i < Bit; ++i)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

void insert(bool *x, int val)
{
    Node *cur, *par, *last, *new;
    int i;
    if (!root)
    {
        root = newNode(x, 0, val);
        root->l = root;
        printf("insert -> %d\n", val);
        return;
    }
    last = search(x);
    if (isEq(x, last->data))
    {
        printf("insert -> conflict\n");
        return;
    }

    for (i = 1; bit(x, i) == bit(last->data, i); ++i)
        ;
    cur = root->l;
    par = root;
    while (cur->bit > par->bit && cur->bit < i)
    {
        par = cur;
        cur = (bit(x, cur->bit)) ? cur->r : cur->l;
    }
    new = newNode(x, i, val);
    new->l = (bit(x, i)) ? cur : new;
    new->r = (bit(x, i)) ? new : cur;

    if (cur == par->l)
        par->l = new;
    else
        par->r = new;
    printf("insert -> %d\n", val);
}

void printData(bool *x)
{
    for (int i = 0; i < Bit; i++)
        printf("%d ", x[i]);
}

int main()
{
    // scanf("%d", &Bit);
    // Bit = 5;
    // bool d[] = {0, 1, 0, 1, 0};
    // Node *tmp = newNode(d, 5);
    // printData(tmp->data);
    scanf("%d", &Bit);
    bool *arr = (bool *)malloc(sizeof(bool) * Bit);
    char str[10] = {0};
    int val, btmp;
    Node *tmp;
    while (*str != 'q')
    {
        scanf("%s", str);
        if (*str == 'i')
        {
            for (int i = 0; i < Bit; ++i)
            {
                scanf("%1d", &btmp);
                arr[i] = btmp;
            }

            scanf("%d", &val);
            insert(arr, val);
        }
        else if (*str == 's')
        {
            for (int i = 0; i < Bit; ++i)
            {
                scanf("%1d", &btmp);
                arr[i] = btmp;
            }
            tmp = search(arr);
            if (isEq(tmp->data, arr))
                printf("search -> %d\n", tmp->val);
            else
                printf("search -> not found");
        }
    }

    return 0;
}