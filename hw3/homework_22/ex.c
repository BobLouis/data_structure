#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Creating a structure to represent a node in the heap
typedef struct Node
{
    struct Node *parent; // Parent pointer
    struct Node *child;  // Child pointer
    struct Node *left;   // Pointer to the node on the left
    struct Node *right;  // Pointer to the node on the right
    int key;             // Value of the node
    int val;
    int degree; // Degree of the node
    char mark;  // Black or white mark of the node
    char c;     // Flag for assisting in the Find node function
} Node;

// Creating min pointer as "mini"
Node *mini = NULL;

// Declare an integer for number of nodes in the heap
int no_of_nodes = 0;

// Function to insert a node in heap
void insertion(int val)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->key = val;
    new->degree = 0;
    new->mark = 'W';
    new->c = 'N';
    new->parent = NULL;
    new->child = NULL;
    new->left = new;
    new->right = new;
    if (mini != NULL)
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
        mini = new;
    }
    no_of_nodes++;
}
// Linking the heap nodes in parent child relationship
void Fibonnaci_link(Node *ptr2, Node *ptr1)
{
    (ptr2->left)->right = ptr2->right;
    (ptr2->right)->left = ptr2->left;
    if (ptr1->right == ptr1)
        mini = ptr1;
    ptr2->left = ptr2;
    ptr2->right = ptr2;
    ptr2->parent = ptr1;
    if (ptr1->child == NULL)
        ptr1->child = ptr2;
    ptr2->right = ptr1->child;
    ptr2->left = (ptr1->child)->left;
    ((ptr1->child)->left)->right = ptr2;
    (ptr1->child)->left = ptr2;
    if (ptr2->key < (ptr1->child)->key)
        ptr1->child = ptr2;
    ptr1->degree++;
}
// Consolidating the heap
void Consolidate()
{
    int temp1;
    float temp2 = (log(no_of_nodes)) / (log(2));
    int temp3 = temp2;
    Node *arr[temp3 + 1];
    for (int i = 0; i <= temp3; i++)
        arr[i] = NULL;
    Node *ptr1 = mini;
    Node *ptr2;
    Node *ptr3;
    Node *ptr4 = ptr1;
    //do circular
    do
    {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;
        while (arr[temp1] != NULL)
        {
            ptr2 = arr[temp1];
            //make ptr1 smaller than ptr2
            if (ptr1->key > ptr2->key)
            {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == mini)
                mini = ptr1;
            Fibonnaci_link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                mini = ptr1;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != mini);
    mini = NULL;
    for (int j = 0; j <= temp3; j++)
    {
        if (arr[j] != NULL)
        {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (mini != NULL)
            {
                (mini->left)->right = arr[j];
                arr[j]->right = mini;
                arr[j]->left = mini->left;
                mini->left = arr[j];
                if (arr[j]->key < mini->key)
                    mini = arr[j];
            }
            else
            {
                mini = arr[j];
            }
            if (mini == NULL)
                mini = arr[j];
            else if (arr[j]->key < mini->key)
                mini = arr[j];
        }
    }
}

// Function to extract minimum node in the heap
void Extract_min()
{
    if (mini == NULL)
        printf("The heap is empty");
    else
    {
        Node *temp = mini;
        Node *pntr;
        pntr = temp;
        Node *x = NULL;
        if (temp->child != NULL)
        {

            x = temp->child;
            do
            {
                pntr = x->right;
                (mini->left)->right = x;
                x->right = mini;
                x->left = mini->left;
                mini->left = x;
                if (x->key < mini->key)
                    mini = x;
                x->parent = NULL;
                x = pntr;
            } while (pntr != temp->child);
        }
        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        mini = temp->right;
        if (temp == temp->right && temp->child == NULL)
            mini = NULL;
        else
        {
            mini = temp->right;
            Consolidate();
        }
        no_of_nodes--;
    }
}

// Cutting a node in the heap to be placed in the root list
void Cut(Node *found, Node *temp)
{
    if (found == found->right)
        temp->child = NULL;

    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == temp->child)
        temp->child = found->right;

    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (mini->left)->right = found;
    found->right = mini;
    found->left = mini->left;
    mini->left = found;
    found->parent = NULL;
    found->mark = 'B';
}

// Recursive cascade cutting function
void Cascase_cut(Node *temp)
{
    Node *ptr5 = temp->parent;
    if (ptr5 != NULL)
    {
        if (temp->mark == 'W')
        {
            temp->mark = 'B';
        }
        else
        {
            Cut(temp, ptr5);
            Cascase_cut(ptr5);
        }
    }
}

// Function to decrease the value of a node in the heap
void Decrease_key(Node *found, int val)
{
    if (mini == NULL)
        printf("The Heap is Empty");

    if (found == NULL)
        printf("Node not found in the Heap");

    found->key = val;

    Node *temp = found->parent;
    if (temp != NULL && found->key < temp->key)
    {
        Cut(found, temp);
        Cascase_cut(temp);
    }
    if (found->key < mini->key)
        mini = found;
}

// Function to find the given node
void Find(Node *mini, int old_val, int val)
{
    Node *found = NULL;
    Node *temp5 = mini;
    temp5->c = 'Y';
    Node *found_ptr = NULL;
    if (temp5->key == old_val)
    {
        found_ptr = temp5;
        temp5->c = 'N';
        found = found_ptr;
        Decrease_key(found, val);
    }
    if (found_ptr == NULL)
    {
        if (temp5->child != NULL)
            Find(temp5->child, old_val, val);
        if ((temp5->right)->c != 'Y')
            Find(temp5->right, old_val, val);
    }
    temp5->c = 'N';
    found = found_ptr;
}

// Deleting a node from the heap
void Deletion(int val)
{
    if (mini == NULL)
        printf("The heap is empty");
    else
    {

        // Decreasing the value of the node to 0
        Find(mini, val, 0);

        // Calling Extract_min function to
        // delete minimum value node, which is 0
        Extract_min();
        printf("Key Deleted");
    }
}

// Function to display the heap
void display()
{
    Node *ptr = mini;
    if (ptr == NULL)
        printf("The Heap is Empty");

    else
    {
        printf("The root nodes of Heap are: ");
        do
        {
            printf("%d", ptr->key);
            ptr = ptr->right;
            if (ptr != mini)
            {
                printf("-->");
            }
        } while (ptr != mini && ptr->right != NULL);
        printf("The heap has %d nodes", no_of_nodes);
    }
}

// Driver code
int main()
{
    // We will create a heap and insert 3 nodes into it
    printf("Creating an initial heap\n");
    for (int i = 0; i < 30; ++i)
    {
        insertion(1);
    }
    // insertion(5);
    // insertion(2);
    // insertion(8);

    // Now we will display the root list of the heap
    display();

    // Now we will extract the minimum value node from the heap
    printf("Extracting min\n");
    Extract_min();
    display();

    // Now we will decrease the value of node '8' to '7'
    printf("Decrease value of 8 to 7\n");
    Find(mini, 29, 7);
    display();

    // Now we will delete the node '7'
    printf("Delete the node 7\n");
    Deletion(7);
    display();

    return 0;
}