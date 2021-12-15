#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int val, height;
    struct Node *left, *right; //left child and right child
} Node;

Node *root = NULL;

int height(Node *n)
{
    if (!n)
        return 0;
    return n->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void max_height(Node *n)
{
    n->height = max(height(n->left), height(n->right)) + 1;
}
Node *new_node(int x)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->val = x;
    tmp->height = 1;
    tmp->right = tmp->left = NULL;
    return tmp;
}

Node *right_R(Node *y)
{
    Node *x = y->left;
    Node *t = x->right;
    x->right = y;
    y->left = t;
    // y->height = max(height(y->left), height(y->right)) + 1;
    max_height(y);
    max_height(x);
    return x;
}

Node *left_R(Node *x)
{
    Node *y = x->right;
    Node *t = y->left;
    x->right = t;
    y->left = x;
    max_height(x);
    max_height(y);
    return y;
}

int get_balance(Node *n)
{
    if (!n)
        return 0;
    return height(n->left) - height(n->right);
}

Node *insert(Node *node, int x)
{
    if (node == NULL)
        return new_node(x);

    if (node->val > x) //insert into left node
        node->left = insert(node->left, x);
    else if (node->val < x)
        node->right = insert(node->right, x);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));
    int blc = get_balance(node);

    //left left case
    if (blc > 1 && x < node->left->val)
        return right_R(node);
    //right right
    if (blc < -1 && x > node->right->val)
        return left_R(node);
    //left right
    if (blc > 1 && x > node->left->val)
    {
        node->left = left_R(node->left);
        return right_R(node);
    }
    //right left
    if (blc < -1 && x < node->right->val)
    {
        node->right = right_R(node->right);
        return left_R(node);
    }
    max_height(node);
    return node;
}

void preOrder(Node *root)
{
    if (root != NULL)
    {
        printf("%d %d ", root->val, root->height);
        preOrder(root->left);
        preOrder(root->right);
    }
}

Node *find(Node *node, int x)
{
    if (node == NULL)
        return NULL;
    if (node->val == x)
        return node;
    else if (node->val < x)
        return find(node->right, x);
    else
        return find(node->left, x);
    return NULL;
}

/* Driver program to test above function*/
int main()
{

    /* Constructing tree given in the above figure */
    //     root = insert(root, 10);
    //     root = insert(root, 20);
    //     root = insert(root, 30);
    //     root = insert(root, 40);
    //     root = insert(root, 50);
    //     root = insert(root, 25);

    //     /* The constructed AVL Tree would be
    //             30
    //            /  \
//          20   40
    //         /  \     \
//        10  25    50
    //   */

    //     printf("Preorder traversal of the constructed AVL"
    //            " tree is \n");
    //     preOrder(root);

    char str[15] = {'\0'};
    int x;
    Node *node;
    scanf("%s", str);
    if (*str == 'A')
    {
        while (*str != 'q')
        {
            scanf("%s", str);
            if (*str == 'i')
            {
                scanf("%d", &x);
                root = insert(root, x);
            }
            else if (*str == 's')
            {
                scanf("%d", &x);
                node = find(root, x);
                if (node)
                {
                    printf("%d\n", get_balance(node));
                }
                else
                {
                    printf("Not found\n");
                }
            }
            else if (*str == 'e')
            {
                scanf("%d", &x);
                node = find(root, x);
                if (node)
                {
                    printf("exist\n");
                }
                else
                {
                    printf("Not exist\n");
                }
            }
            else if (*str == 'd')
            {
                preOrder(root);
                printf("\n");
            }
        }
    }

    return 0;
}
