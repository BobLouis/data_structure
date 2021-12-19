#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node *root = NULL;

struct Node
{
    int val, np;
    struct Node *left, *right;
};

struct Node *newnode(int x)
{
    struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->val = x;
    tmp->np = 0;
    tmp->left = tmp->right = NULL;
    return tmp;
}

void swap(struct Node *x, struct Node *y)
{
    struct Node tmp = *x;
    *x = *y;
    *y = tmp;
}

struct Node *merge_sub(struct Node *, struct Node *);
struct Node *merge(struct Node *, struct Node *);

struct Node *merge_sub(struct Node *root, struct Node *child)
{
    if (root->left == NULL)
        root->left = child;
    else
    {
        root->right = merge(root->right, child);
        if (root->right->np > root->left->np)
            swap(root->left, root->right);
        root->np = root->right->np + 1;
    }
    return root;
}

struct Node *merge(struct Node *x, struct Node *y)
{
    if (x == NULL)
        return y;
    if (y == NULL)
        return x;
    return (x->val < y->val) ? merge_sub(x, y) : merge_sub(y, x);
}

struct Node *insert(struct Node *root, int x)
{
    struct Node *tmp = newnode(x);
    root = merge(root, tmp);
    return root;
}

struct Node *deletemin(struct Node *root)
{
    root = merge(root->right, root->left);
    return root;
}

int main()
{
    clock_t start_t, end_t;
    int n, x;
    scanf("%d", &n);
    start_t = clock();
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        if (x == 0)
            root = deletemin(root);
        else
            root = insert(root, x);
    }
    end_t = clock();
    printf("total time: %lu s", end_t - start_t);

    return 0;
}