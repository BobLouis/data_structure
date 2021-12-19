#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node
{
    int key, height;
    struct Node *left, *right;
};

struct Node *rootAVL = NULL;

int height(struct Node *n)
{
    if (!n)
        return 0;
    return n->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void max_height(struct Node *n)
{
    n->height = max(height(n->left), height(n->right)) + 1;
}
struct Node *new_node(int x)
{
    struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->key = x;
    tmp->height = 1;
    tmp->right = tmp->left = NULL;
    return tmp;
}

struct Node *right_R(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *t = x->right;
    x->right = y;
    y->left = t;
    max_height(y);
    max_height(x);
    return x;
}

struct Node *left_R(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *t = y->left;
    x->right = t;
    y->left = x;
    max_height(x);
    max_height(y);
    return y;
}

int get_balance(struct Node *n)
{
    if (!n)
        return 0;
    return height(n->left) - height(n->right);
}

struct Node *insert(struct Node *node, int x)
{
    if (node == NULL)
        return new_node(x);

    if (node->key > x)
        node->left = insert(node->left, x);
    else if (node->key < x)
        node->right = insert(node->right, x);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));
    int blc = get_balance(node);

    if (blc > 1 && x < node->left->key)
        return right_R(node);

    if (blc < -1 && x > node->right->key)
        return left_R(node);

    if (blc > 1 && x > node->left->key)
    {
        node->left = left_R(node->left);
        return right_R(node);
    }

    if (blc < -1 && x < node->right->key)
    {
        node->right = right_R(node->right);
        return left_R(node);
    }
    max_height(node);
    return node;
}

struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node *deleteNode(struct Node *node, int key)
{

    if (node == NULL)
        return node;

    if (key < node->key)
        node->left = deleteNode(node->left, key);

    else if (key > node->key)
        node->right = deleteNode(node->right, key);

    else
    {
        if ((node->left == NULL) || (node->right == NULL))
        {
            struct Node *temp = node->left ? node->left : node->right;

            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;

            free(temp);
        }
        else
        {

            struct Node *temp = minValueNode(node->right);

            node->key = temp->key;

            node->right = deleteNode(node->right, temp->key);
        }
    }

    if (node == NULL)
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && get_balance(node->left) >= 0)
        return right_R(node);

    if (balance > 1 && get_balance(node->left) < 0)
    {
        node->left = left_R(node->left);
        return right_R(node);
    }

    if (balance < -1 && get_balance(node->right) <= 0)
        return left_R(node);

    if (balance < -1 && get_balance(node->right) > 0)
    {
        node->right = right_R(node->right);
        return left_R(node);
    }

    return node;
}

struct Node *search(struct Node *node, int x)
{
    if (node == NULL)
        return NULL;
    if (node->key == x)
        return node;
    else if (node->key < x)
        return search(node->right, x);
    else
        return search(node->left, x);
    return NULL;
}
////////////////////////////

struct rbNode
{
    int color, key;
    struct rbNode *left, *right, *parent;
};

struct rbNode *RBroot = NULL, *neel;

struct rbNode *RBInitNode(int key)
{
    struct rbNode *node = (struct rbNode *)malloc(sizeof(struct rbNode));
    node->key = key;
    node->color = 0;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void RBInit()
{
    neel = (struct rbNode *)malloc(sizeof(struct rbNode));
    neel->color = 1;
    neel->left = neel->right = neel->parent = NULL;
    RBroot = neel, RBroot->parent = neel;
}

void RBRightRotate(struct rbNode *node)
{
    struct rbNode *left = node->left;
    node->left = left->right;
    if (left->right != neel)
        left->right->parent = node;
    left->parent = node->parent;
    if (node->parent == neel)
        RBroot = left;
    else if (node == node->parent->left)
        node->parent->left = left;
    else
        node->parent->right = left;
    left->right = node;
    node->parent = left;
}

void RBLeftRotate(struct rbNode *node)
{
    struct rbNode *right = node->right;
    node->right = right->left;
    if (right->left != neel)
        right->left->parent = node;
    right->parent = node->parent;
    if (node->parent == neel)
        RBroot = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

void RBInsertFixup(struct rbNode *currentNode)
{

    while (currentNode->parent->color == 0)
    {
        if (currentNode->parent == currentNode->parent->parent->left)
        {
            struct rbNode *uncle = currentNode->parent->parent->right;
            if (uncle->color == 0)
            {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            }
            else
            {
                if (currentNode == currentNode->parent->right)
                {
                    currentNode = currentNode->parent;
                    RBLeftRotate(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                RBRightRotate(currentNode->parent->parent);
            }
        }
        else
        {
            struct rbNode *uncle = currentNode->parent->parent->left;
            if (uncle->color == 0)
            {
                currentNode->parent->color = 1;
                uncle->color = 1;
                currentNode->parent->parent->color = 0;
                currentNode = currentNode->parent->parent;
            }
            else
            {
                if (currentNode == currentNode->parent->left)
                {
                    currentNode = currentNode->parent;
                    RBRightRotate(currentNode);
                }
                currentNode->parent->color = 1;
                currentNode->parent->parent->color = 0;
                RBLeftRotate(currentNode->parent->parent);
            }
        }
    }
    RBroot->color = 1;
}

void RBInsert(int key)
{
    struct rbNode *x = RBroot;
    struct rbNode *y = neel;
    struct rbNode *node = RBInitNode(key);
    while (x != neel)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else if (node->key > x->key)
            x = x->right;
        else
            return;
    }
    node->parent = y;
    if (y == neel)
        RBroot = node;
    else if (node->key < y->key)
        y->left = node;
    else
        y->right = node;
    node->left = neel;
    node->right = neel;
    RBInsertFixup(node);
    neel->parent = RBroot;
}

struct rbNode *RBSearch(int key)
{
    struct rbNode *current = RBroot;
    while (current != neel && current->key != key)
    {
        if (current->key > key)
            current = current->left;
        else
            current = current->right;
    }
    if (current == neel)
        return NULL;
    else
        return current;
}

struct rbNode *RBLeftmost(struct rbNode *current)
{
    while (current->left != neel)
        current = current->left;
    return current;
}

struct rbNode *RBSuccessor(struct rbNode *current)
{
    if (current->right != neel)
        return RBLeftmost(current->right);
    struct rbNode *current_pt = current->parent;
    while (current_pt != neel && current == current_pt->right)
    {
        current = current_pt;
        current_pt = current_pt->parent;
    }
    return current_pt;
}

void RBDeleteFixup(struct rbNode *current)
{
    while (current != RBroot && current->color == 1)
    {
        if (current == current->parent->left)
        {
            struct rbNode *sibling = current->parent->right;
            if (sibling->color == 0)
            {
                sibling->color = 1;
                current->parent->color = 0;
                RBLeftRotate(current->parent);
                sibling = current->parent->right;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1)
            {
                sibling->color = 0;
                current = current->parent;
            }
            else
            {
                if (sibling->right->color == 1)
                {
                    sibling->left->color = 1;
                    sibling->color = 0;
                    RBRightRotate(sibling);
                    sibling = current->parent->right;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->right->color = 1;
                RBLeftRotate(current->parent);
                current = RBroot;
            }
        }
        else
        {
            struct rbNode *sibling = current->parent->left;
            if (sibling->color == 0)
            {
                sibling->color = 1;
                current->parent->color = 0;
                RBRightRotate(current->parent);
                sibling = current->parent->left;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1)
            {
                sibling->color = 0;
                current = current->parent;
            }
            else
            {
                if (sibling->left->color == 1)
                {
                    sibling->right->color = 1;
                    sibling->color = 0;
                    RBLeftRotate(sibling);
                    sibling = current->parent->left;
                }
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->left->color = 1;
                RBRightRotate(current->parent);
                current = RBroot;
            }
        }
    }
    current->color = 1;
}

void RBDelete(int key)
{
    struct rbNode *toDelete = RBSearch(key);
    if (toDelete == NULL)
        return;
    struct rbNode *x, *y;
    if (toDelete->left == neel || toDelete->right == neel)
        y = toDelete;
    else
        y = RBSuccessor(toDelete);
    if (y->left != neel)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;

    if (y->parent == neel)
        RBroot = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != toDelete)
        toDelete->key = y->key;

    if (y->color == 1)
        RBDeleteFixup(x);
    neel->parent = RBroot;
}

int main()
{
    char op[20] = "0";
    int x;
    RBInit();
    struct Node *tmp;
    struct rbNode *tmp1;
    scanf("%s", op);
    if (!strcmp(op, "red_black"))
    {
        while (strcmp(op, "quit") != 0)
        {
            scanf("%s", op);
            if (!strcmp(op, "insert"))
            {
                scanf("%d", &x);
                RBInsert(x);
            }
            else if (!strcmp(op, "search"))
            {
                scanf("%d", &x);
                tmp1 = RBSearch(x);
                if (!tmp1)
                    printf("Not found\n");
                else
                {
                    if (tmp1->color)
                        printf("black\n");
                    else
                        printf("red\n");
                }
            }
            else if (!strcmp(op, "delete"))
            {
                scanf("%d", &x);
                RBDelete(x);
            }
            else if (!strcmp(op, "exist"))
            {
                scanf("%d", &x);
                tmp1 = RBSearch(x);
                if (!tmp1)
                    printf("Not exist\n");
                else
                    printf("exist\n");
            }
        }
    }
    else if (!strcmp(op, "AVL"))
    {
        while (strcmp(op, "quit") != 0)
        {
            scanf("%s", op);
            if (!strcmp(op, "insert"))
            {
                scanf("%d", &x);
                rootAVL = insert(rootAVL, x);
            }
            else if (!strcmp(op, "search"))
            {
                scanf("%d", &x);
                tmp = search(rootAVL, x);
                if (tmp)
                    printf("%d\n", get_balance(tmp));
                else
                    printf("Not found\n");
            }
            else if (!strcmp(op, "delete"))
            {
                scanf("%d", &x);
                deleteNode(rootAVL, x);
            }
            else if (!strcmp(op, "exist"))
            {
                scanf("%d", &x);
                tmp = search(rootAVL, x);
                if (tmp)
                    printf("exist\n");
                else
                    printf("Not exist\n");
            }
        }
    }
}