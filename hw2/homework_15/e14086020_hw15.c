#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1200

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node *new_node(int x)
{
    Node *tmp;
    tmp = (Node *)malloc(sizeof(struct Node));
    tmp->val = x;
    return tmp;
}

int find(int arr[], int idx, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] == idx)
            return i;
    }
    return -1;
}

Node *pre_in(int pre[], int in[], int n)
{
    if (!n)
        return NULL;
    Node *root = new_node(pre[0]);
    int mid;
    if (n == 1)
        return root;
    mid = find(in, pre[0], n);
    root->left = pre_in(pre + 1, in, mid);
    root->right = pre_in(pre + mid + 1, in + mid + 1, n - mid - 1);
    return root;
}

Node *post_in(int post[], int in[], int n)
{
    if (!n)
        return NULL;
    Node *root = new_node(post[n - 1]);
    int mid;
    if (n == 1)
        return root;
    mid = find(in, post[n - 1], n);
    root->left = post_in(post, in, mid);
    root->right = post_in(post + mid, in + mid + 1, n - mid - 1);
    return root;
}

void postorder(Node *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

void preorder(Node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

int main()
{
    int r, n;
    char str[20];
    int p[MAX_N], in[MAX_N];
    Node *root;
    scanf("%d", &r);
    while (r--)
    {
        scanf("%s", str);
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &p[i]);
        for (int i = 0; i < n; ++i)
            scanf("%d", &in[i]);
        if (str[1] == 'r')
        {
            root = pre_in(p, in, n);
            postorder(root);
            puts("");
        }
        else
        {
            root = post_in(p, in, n);
            preorder(root);
            puts("");
        }
    }
}