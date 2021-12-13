#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100000

typedef struct Node
{
    int val, deg, key;
    struct Node *parent, *child, *right, *left;
} Node;

Node *mini = NULL;

Node *new_node(int val, int key)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->val = val;
    tmp->key = key;
    tmp->deg = 0;
    tmp->parent = tmp->child = tmp->left = tmp->right = NULL;
    return tmp;
}

void insert(int val, int key)
{
    Node *new = new_node(val, key);
    if (!mini)
    {
        (mini->left)->right = new;
        new->right = mini;
        new->left = mini->left;
        mini->left = new;
        if (new->key < mini->key)
            mini = new;
    }
    else
    {
        new->right = new->left = new;
    }
}