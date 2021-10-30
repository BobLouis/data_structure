#include <stdio.h>
#include <string.h>
#define MAX_N 100

Node *root;
typedef struct Node
{
    int val;
    struct node *left;
    struct node *right;
} Node;

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
    node->left = newNode(right_val);
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
    Node *stack[100];
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
            cur = find_node(insert_node);
            insertRight(cur, insert_element);
        }
        else
        {
            cur = find_node(insert_node);
            insertLeft(cur, insert_element);
        }
    }
    printInorder(root);
    return 0;
}