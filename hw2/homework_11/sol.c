#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_N 100

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
} Node;
Node *root;
Node *newNode(int val)
{
    Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insertLeft(Node *node, int left_val)
{
    node->left = newNode(left_val);
}

void insertRight(Node *node, int right_val)
{
    node->right = newNode(right_val);
}

void printInorder(Node *node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    printf("%d ", node->val);
    printInorder(node->right);
}

Node *find_node(int val)
{
    int top = 0;
    Node *stack[MAX_N];
    Node *cur = (Node *)malloc(sizeof(struct Node));
    stack[++top] = root;
    while (top)
    {
        cur = stack[top--];
        if (cur->val == val)
            return cur;
        if (cur->right != NULL)
            stack[++top] = cur->right;
        if (cur->left != NULL)
            stack[++top] = cur->left;
    }
    return NULL;
}

int main()
{
    int n, r, insert_node, insert_element;
    char command[6];
    Node *cur = (Node *)malloc(sizeof(struct Node));
    scanf("%d%d", &n, &r);
    root = newNode(r);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d%s%d", &insert_node, command, &insert_element);
        cur = find_node(insert_node);
        if (command[0] == 'r')
        {
            insertRight(cur, insert_element);
        }
        else
        {
            insertLeft(cur, insert_element);
        }
    }
    printInorder(root);

    return 0;
}