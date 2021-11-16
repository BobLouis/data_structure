#include <stdio.h>
#include <stdlib.h>

#define NODE_MAX 100

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node;

node *newNode(int data)
{
    node *node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void printInorder(node *node)
{
    if (node->data == -1)
        return;

    printInorder(node->left);
    printf("%d ", node->data);
    printInorder(node->right);
}

void printPreorder(node *node)
{
    if (node->data == -1)
        return;
    printf("%d ", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

int insert_node(node *ptr, int num)
{
    if (ptr->data == -1)
        return 0;

    if (ptr->left == NULL)
    {
        ptr->left = newNode(num);
        return 1;
    }
    else
    {
        if (insert_node(ptr->left, num))
            return 1;
    }

    if (ptr->right == NULL)
    {
        ptr->right = newNode(num);
        return 1;
    }
    else
    {
        if (insert_node(ptr->right, num))
            return 1;
    }
    return 0;
}

void swap_tree(node *root)
{
    node *cur = (node *)malloc(sizeof(struct node));
    node *temp = (node *)malloc(sizeof(struct node));
    node *stack[NODE_MAX];
    int top = 0;
    stack[++top] = root;
    while (top)
    {
        cur = stack[top--]; //pop
        temp = cur->left;
        cur->left = cur->right;
        cur->right = temp;
        if (cur->right->data != -1)
        {
            stack[++top] = cur->right;
        }
        if (cur->left->data != -1)
        {
            stack[++top] = cur->left;
        }
    }
}
int main()
{
    int n, input;
    scanf("%d", &n);
    scanf("%d", &input);
    node *root = newNode(input);
    node *curr;
    curr = root;
    for (int i = 0; i < n - 1; ++i)
    {
        scanf("%d", &input);
        insert_node(root, input);
    }
    swap_tree(root);
    printPreorder(root);
    printf("\n");
    printInorder(root);
    getchar();
    return 0;
}