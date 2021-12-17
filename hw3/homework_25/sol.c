#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct BTreeNode
{
    int *keys;            // An array of keys
    int t;                // Minimum degree (defines the range for number of keys)
    struct BTreeNode **C; // An array of child pointers
    int n;                // Current number of keys
    int leaf;             // Is true when node is leaf. Otherwise false
} BTreeNode;

void traverse();

// A function to search a key in subtree rooted with this node.
// BTreeNode *search(int k); // returns NULL if k is not present.

// A function that returns the index of the first key that is greater
// or equal to k
int findKey(BTreeNode *node, int k);

// A utility function to insert a new key in the subtree rooted with
// this node. The assumption is, the node must be non-full when this
// function is called
void insertNonFull(int k);

// A utility function to split the child y of this node. i is index
// of y in child array C[].  The Child y must be full when this
// function is called
void splitChild(int i, BTreeNode *y);

// A wrapper function to remove the key k in subtree rooted with
// this node.
void del_node(BTreeNode *node, int k);

// A function to remove the key present in idx-th position in
// this node which is a leaf
void removeFromLeaf(int idx);

// A function to remove the key present in idx-th position in
// this node which is a non-leaf node
void removeFromNonLeaf(int idx);

// A function to get the predecessor of the key- where the key
// is present in the idx-th position in the node
int getPred(int idx);

// A function to get the successor of the key- where the key
// is present in the idx-th position in the node
int getSucc(int idx);

// A function to fill up the child node present in the idx-th
// position in the C[] array if that child has less than t-1 keys
void fill(int idx);

// A function to borrow a key from the C[idx-1]-th node and place
// it in C[idx]th node
void borrowFromPrev(int idx);

// A function to borrow a key from the C[idx+1]-th node and place it
// in C[idx]th node
void borrowFromNext(int idx);

// A function to merge idx-th child of the node with (idx+1)th child of
// the node
void merge(int idx);

BTreeNode *root = NULL; // Pointer to root node
int t = 3;              // Minimum degree

BTreeNode *new_node(int t1, int leaf1)
{
    BTreeNode *tmp = (BTreeNode *)malloc(sizeof(BTreeNode));
    tmp->keys = (int *)malloc(sizeof(int) * (2 * t - 1));
    tmp->t = t1;
    tmp->leaf = leaf1;
    tmp->C = (BTreeNode **)malloc(sizeof(BTreeNode) * 2); //not sure
    // tmp->C = (BTreeNode **)malloc(sizeof(BTreeNode *) * 2);
    tmp->n = 0;
    return tmp;
}

int findKey(BTreeNode *node, int k)
{
    int idx = 0;
    int n = node->n;
    int *keys = node->keys;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

void del_node(BTreeNode *node, int k)
{
    int idx = findKey(node, k);
    int *keys = node->keys;
    int n = node->n;
    int leaf = node->leaf;
    BTreeNode **C = node->C;
    // The key to be removed is present in this node
    if (idx < n && keys[idx] == k)
    {
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf)
            del_nodeFromLeaf(idx);
        else
            del_nodeFromNonLeaf(idx);
    }
    else
    {

        // If this node is a leaf node, then the key is not present in tree
        if (leaf)
        {
            printf("The key %d is does not exist in the tree\n", k);
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        int flag = ((idx == n) ? 1 : 0);

        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (C[idx]->n < t)
            fill(idx);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > n)
            del_node(C[idx - 1], k);
        else
            del_node(C[idx], k);
    }
    return;
}

int main()
{
    return 0;
}