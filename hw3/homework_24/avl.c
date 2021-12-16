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

Node *minValueNode(Node *node)
{
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
Node *deleteNode(Node *root, int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (key < root->val)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if (key > root->val)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of
                               // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node *temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->val = temp->val;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->val);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = get_balance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && get_balance(root->left) >= 0)
        return right_R(root);

    // Left Right Case
    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = left_R(root->left);
        return right_R(root);
    }

    // Right Right Case
    if (balance < -1 && get_balance(root->right) <= 0)
        return left_R(root);

    // Right Left Case
    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = right_R(root->right);
        return left_R(root);
    }

    return root;
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

int main()
{
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
            else if (*str == 'd' && strlen(str) == 1)
            {
                preOrder(root);
                printf("\n");
            }
            else if (*str == 'd')
            {
                scanf("%d", &x);
                deleteNode(root, x);
            }
        }
    }

    return 0;
}
