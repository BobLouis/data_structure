#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
    int val, npl; //null path length
    struct Node *left, *right;
} Node;

Node *new_node(int x)
{
    Node *tmp = (Node *)malloc(sizeof(struct Node));
    tmp->val = x;
    tmp->npl = 0;
    tmp->left = tmp->right = NULL;
    return tmp;
}

void swap(Node *x, Node *y)
{
    Node tmp = *x; //the content of x
    *x = *y;
    *y = tmp;
}

Node *merge_sub(Node *, Node *);
Node *merge(Node *, Node *);

Node *merge_sub(Node *root, Node *child)
{
    if (root->left == NULL)
        root->left = child; //leftist first
    else
    {
        root->right = merge(root->right, child);
        if (root->right->npl > root->left->npl) //check if the npl right is larger than npl left
            swap(root->left, root->right);
        root->npl = root->right->npl + 1;
    }
    return root;
}

Node *merge(Node *x, Node *y)
{
    if (x == NULL)
        return y;
    if (y == NULL)
        return x;
    return (x->val < y->val) ? merge_sub(x, y) : merge_sub(y, x);
}

Node *insert(Node *root, int x)
{
    Node *tmp = new_node(x);
    root = merge(root, tmp);
    return root;
}

Node *pop_min(Node *root)
{
    // printf("%d ", root->val);
    root = merge(root->right, root->left);
    return root;
}

int main()
{
    clock_t start_t, end_t;
    Node *root = NULL;
    int n, m, val, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &val);
        root = insert(root, val);
    }
    start_t = clock();
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &x);
        if (x)
            root = insert(root, x);
        else
            root = pop_min(root);
    }
    end_t = clock();
    printf("start: %lu end: %lu\n", start_t, end_t);
    printf("duration: %lu", end_t - start_t);

    return 0;
}
