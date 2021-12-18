#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int arr[10000000];
int top = 1;

typedef struct BTreeNode
{
    int *keys; // An array of keys
    // int t;                // Minimum degree (defines the range for number of keys)
    struct BTreeNode **C; // An array of child pointers
    int n;                // Current number of keys
    int leaf;             // Is true when node is leaf. Otherwise false
} BTreeNode;

// A function to traverse all nodes in a subtree rooted with this node
void traverse();

void traverse_a();
// A function to search a key in subtree rooted with this node.
BTreeNode *search(BTreeNode *node, int k); // returns NULL if k is not present.

// A function that returns the index of the first key that is greater
// or equal to k
int findKey(BTreeNode *node, int k);

// A utility function to insert a new key in the subtree rooted with
// this node. The assumption is, the node must be non-full when this
// function is called
void insertNonFull(BTreeNode *node, int k);

// A utility function to split the child y of this node. i is index
// of y in child array C[].  The Child y must be full when this
// function is called
void splitChild(BTreeNode *node, int i, BTreeNode *y);

// A wrapper function to del_node the key k in subtree rooted with
// this node.
void del_node(BTreeNode *node, int k);

// A function to remove the key present in idx-th position in
// this node which is a leaf
void del_nodeFromLeaf(BTreeNode *node, int idx);

// A function to remove the key present in idx-th position in
// this node which is a non-leaf node
void del_nodeFromNonLeaf(BTreeNode *node, int idx);

// A function to get the predecessor of the key- where the key
// is present in the idx-th position in the node
int getPred(BTreeNode *node, int idx);

// A function to get the successor of the key- where the key
// is present in the idx-th position in the node
int getSucc(BTreeNode *node, int idx);

// A function to fill up the child node present in the idx-th
// position in the C[] array if that child has less than t-1 keys
void fill(BTreeNode *node, int idx);

// A function to borrow a key from the C[idx-1]-th node and place
// it in C[idx]th node
void borrowFromPrev(BTreeNode *node, int idx);

// A function to borrow a key from the C[idx+1]-th node and place it
// in C[idx]th node
void borrowFromNext(BTreeNode *node, int idx);

// A function to merge idx-th child of the node with (idx+1)th child of
// the node
void merge(BTreeNode *node, int idx);

BTreeNode *root = NULL; // Pointer to root node
int t = 3;              // Minimum degree

BTreeNode *new_node(int t1, int leaf1)
{
    BTreeNode *tmp = (BTreeNode *)malloc(sizeof(BTreeNode));
    tmp->keys = (int *)malloc(sizeof(int) * (2 * t - 1));
    // tmp->t = t1;
    tmp->leaf = leaf1;
    tmp->C = (BTreeNode **)malloc(sizeof(BTreeNode) * 2); //not sure
    // tmp->C = (BTreeNode **)malloc(sizeof(BTreeNode *) * 2);
    tmp->n = 0;
    return tmp;
}

int findKey(BTreeNode *node, int k)
{
    int idx = 0;
    while (idx < node->n && node->keys[idx] < k)
        ++idx;
    return idx;
}

void del_node(BTreeNode *node, int k)
{
    int idx = findKey(node, k);
    // The key to be removed is present in this node
    if (idx < node->n && node->keys[idx] == k)
    {
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (node->leaf)
            del_nodeFromLeaf(node, idx);
        else
            del_nodeFromNonLeaf(node, idx);
    }
    else
    {

        // If this node is a leaf node, then the key is not present in tree
        if (node->leaf)
        {
            printf("The key %d is does not exist in the tree\n", k);
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        int flag = ((idx == node->n) ? 1 : 0);

        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (node->C[idx]->n < t)
            fill(node, idx);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > node->n)
            del_node(node->C[idx - 1], k);
        else
            del_node(node->C[idx], k);
    }
    return;
}

void del_nodeFromLeaf(BTreeNode *node, int idx)
{

    // Move all the keys after the idx-th pos one place backward
    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    // Reduce the count of keys
    node->n--;

    return;
}

void del_nodeFromNonLeaf(BTreeNode *node, int idx)
{

    int k = node->keys[idx];

    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (node->C[idx]->n >= t)
    {
        int pred = getPred(node, idx);
        node->keys[idx] = pred;
        del_node(node->C[idx], pred);
    }

    // If the child C[idx] has less that t keys, examine C[idx+1].
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if (node->C[idx + 1]->n >= t)
    {
        int succ = getSucc(node, idx);
        node->keys[idx] = succ;
        del_node(node->C[idx + 1], succ);
    }

    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(node, idx);
        del_node(node->C[idx], k);
    }
    return;
}

int getPred(BTreeNode *node, int idx)
{
    // Keep moving to the right most node until we reach a leaf
    BTreeNode *cur = node->C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    // Return the last key of the leaf
    return cur->keys[cur->n - 1];
}

int getSucc(BTreeNode *node, int idx)
{

    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    BTreeNode *cur = node->C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    // Return the first key of the leaf
    return cur->keys[0];
}

// A function to fill child C[idx] which has less than t-1 keys
void fill(BTreeNode *node, int idx)
{

    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx != 0 && node->C[idx - 1]->n >= t)
        borrowFromPrev(node, idx);

    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (idx != node->n && node->C[idx + 1]->n >= t)
        borrowFromNext(node, idx);

    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (idx != node->n)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
    return;
}

// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void borrowFromPrev(BTreeNode *node, int idx)
{

    BTreeNode *child = node->C[idx];
    BTreeNode *sibling = node->C[idx - 1];

    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key

    // Moving all key in C[idx] one step ahead
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = node->keys[idx - 1];

    // Moving sibling's last child as C[idx]'s first child
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    node->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void borrowFromNext(BTreeNode *node, int idx)
{

    BTreeNode *child = node->C[idx];
    BTreeNode *sibling = node->C[idx + 1];

    // keys[idx] is inserted as the last key in C[idx]
    child->keys[(child->n)] = node->keys[idx];

    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->leaf))
        child->C[(child->n) + 1] = sibling->C[0];

    //The first key from sibling is inserted into keys[idx]
    node->keys[idx] = sibling->keys[0];

    // Moving all keys in sibling one step behind
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void merge(BTreeNode *node, int idx)
{
    BTreeNode *child = node->C[idx];
    BTreeNode *sibling = node->C[idx + 1];

    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[t - 1] = node->keys[idx];

    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i = idx + 2; i <= node->n; ++i)
        node->C[i - 1] = node->C[i];

    // Updating the key count of child and the current node
    child->n += sibling->n + 1;
    node->n--;

    // Freeing the memory occupied by sibling
    free(sibling);
    return;
}

void insert(int k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new_node(t, 1);
        root->keys[0] = k; // Insert key
        root->n = 1;       // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1)
        {
            // Allocate memory for new root
            BTreeNode *s = new_node(t, 0);
            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            splitChild(s, 0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            insertNonFull(s->C[i], k);

            // Change root
            root = s;
        }
        else // If root is not full, call insertNonFull for root
            insertNonFull(root, k);
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void insertNonFull(BTreeNode *node, int k)
{
    // Initialize index as index of rightmost element
    int i = node->n - 1;

    // If this is a leaf node
    if (node->leaf == 1)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && node->keys[i] > k)
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        // Insert the new key at found location
        node->keys[i + 1] = k;
        node->n = node->n + 1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && node->keys[i] > k)
            i--;

        // See if the found child is full
        if (node->C[i + 1]->n == 2 * t - 1)
        {
            // If the child is full, then split it
            splitChild(node, i + 1, node->C[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (node->keys[i + 1] < k)
                i++;
        }
        insertNonFull(node->C[i + 1], k);
    }
}

void splitChild(BTreeNode *node, int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new_node(t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children of y to z
    if (y->leaf == 0)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = node->n; j >= i + 1; j--)
        node->C[j + 1] = node->C[j];

    // Link the new child to this node
    node->C[i + 1] = z;

    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = node->n - 1; j >= i; j--)
        node->keys[j + 1] = node->keys[j];

    // Copy the middle key of y to this node
    node->keys[i] = y->keys[t - 1];

    // Increment count of keys in this node
    node->n = node->n + 1;
}

void traverse(BTreeNode *node)
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < node->n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (node->leaf == 0)
            traverse(node->C[i]);
        printf(" %d", node->keys[i]);
    }

    // Print the subtree rooted with last child
    if (node->leaf == 0)
        traverse(node->C[i]);
}

void traverse_a(BTreeNode *node)
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < node->n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (node->leaf == 0)
            traverse_a(node->C[i]);
        // cout << " " << keys[i];
        arr[top++] = node->keys[i];
    }

    // Print the subtree rooted with last child
    if (node->leaf == 0)
        traverse_a(node->C[i]);
}

// Function to search key k in subtree rooted with this node
BTreeNode *search(BTreeNode *node, int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < node->n && k > node->keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (node->keys[i] == k)
        return node;

    // If key is not found here and this is a leaf node
    if (node->leaf == 1)
        return NULL;

    // Go to the appropriate child
    return search(node->C[i], k);
}

void del_node_b(int k)
{
    if (!root)
    {
        printf("The tree is empty\n");
        return;
    }

    // Call the remove function for root
    del_node(root, k);

    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->n == 0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        // Free the old root
        free(tmp);
    }
    return;
}

int main()
{
    int n, x, r;
    char str[15];
    BTreeNode *tmp;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", str);
        if (*str == 'a')
        {
            scanf("%d", &x);
            insert(x);
            printf("add(%d) = ok\n", x);
        }
        else if (*str == 'g')
        {
            scanf("%d", &x);
            if (*(str + 3) == 'k')
            {
                if (!x)
                {
                    printf("getk(0) = not found\n");
                    continue;
                }
                top = 1;
                if (root != NULL)
                    traverse_a(root);
                if (x >= top)
                {
                    printf("getk(%d) = not found\n", x);
                }
                else
                {
                    r = arr[x];
                    printf("getk(%d) = %d\n", x, r);
                }
            }
            else
            {
                tmp = (root == NULL) ? NULL : search(root, x);
                if (tmp)
                    printf("get(%d) = %d\n", x, x);
                else
                    printf("get(%d) = not found\n", x);
            }
        }
        else if (*str == 'r')
        {
            scanf("%d", &x);
            if (*(str + 6) == 'k')
            {
                if (!x)
                {
                    printf("removek(0) = not found\n");
                    continue;
                }
                top = 1;
                if (root != NULL)
                    traverse_a(root);
                if (x >= top)
                {
                    printf("removek(%d) = not found\n", x);
                }
                else
                {
                    r = arr[x];
                    del_node_b(r);
                    printf("removek(%d) = %d\n", x, r);
                }
            }
            else
            {
                tmp = (root == NULL) ? NULL : search(root, x);
                if (tmp)
                {
                    del_node_b(x);
                    printf("remove(%d) = %d\n", x, x);
                }
                else
                    printf("remove(%d) = not found\n", x);
            }
        }
        // t.traverse();
        // printf("\n");
    }
    return 0;
}