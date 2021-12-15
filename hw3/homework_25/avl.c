#include <stdio.h>
#include <stblib.h>
#include <string.h>

typedef struct Node
{
    int val, height;
    struct Node *left, *right; //left child and right child
} Node;

Node *root = NULL;

Node *new_node(int x)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->val = x;
    tmp->height = 1;
    tmp->right = tmp->left = NULL;
    return tmp;
}

Node *insert(Node *node, int x)
{
    if (node == NULL)
    {
        return new_node(x)
    }

    if (node->val > x) //insert into left node
    {
        node->left = insert(node->left, x);
    }
    else
    {
        node->left = insert(node->left, x);
    }
    return node;
}

int main
