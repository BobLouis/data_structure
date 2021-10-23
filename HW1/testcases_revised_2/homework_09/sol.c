// C program for different tree traversals
#include <stdio.h>
#include <stdlib.h>

#define NODE_MAX 100
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node;

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
node *newNode(int data)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

/* Given a binary tree, print its nodes according to the
  "bottom-up" postorder traversal. */

void nonrecur_pre(node *root)
{
    int top = 0;
    node *stack[NODE_MAX];
    node *cur = (node *)malloc(sizeof(struct node));
    stack[++top] = root;
    while (top)
    {
        cur = stack[top--];
        printf("%d ", cur->data);

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

void nonrecur_post(node *root)
{
    int top = 0;
    int index = 0, output[NODE_MAX];
    node *stack[NODE_MAX];
    node *cur = (node *)malloc(sizeof(struct node));
    stack[++top] = root;
    while (top)
    {
        cur = stack[top--];
        output[++index] = cur->data;
        if (cur->left->data != -1)
        {
            stack[++top] = cur->left;
        }
        if (cur->right->data != -1)
        {
            stack[++top] = cur->right;
        }
    }

    for (int i = index; i; --i)
    {
        printf("%d ", output[i]);
    }
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

/* Driver program to test above functions*/
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

    nonrecur_pre(root);
    printf("\n");
    nonrecur_post(root);
    getchar();
    return 0;
}