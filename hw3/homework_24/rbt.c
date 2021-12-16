#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    int d;          // data
    int c;          // 1-red, 0-black
    struct node *p; // parent
    struct node *r; // right-child
    struct node *l; // left child
} node;

node *root = NULL;
int dup = 0;
void inorder(node *);

node *new_node(int x)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->r = NULL;
    temp->l = NULL;
    temp->p = NULL;
    temp->d = x;
    temp->c = 1;
    return temp;
}

node *bst(node *trav,
          node *temp)
{
    if (trav == NULL)
        return temp;

    if (temp->d < trav->d)
    {
        trav->l = bst(trav->l, temp);
        trav->l->p = trav;
    }
    else if (temp->d > trav->d)
    {
        trav->r = bst(trav->r, temp);
        trav->r->p = trav;
    }
    else
    {
        dup = 1;
        return trav;
    }
    dup = 0;
    return trav;
}

void rightrotate(node *temp)
{
    node *left = temp->l;
    temp->l = left->r;
    if (temp->l)
        temp->l->p = temp;
    left->p = temp->p;
    if (!temp->p)
        root = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;
    left->r = temp;
    temp->p = left;
}

void leftrotate(node *temp)
{
    node *right = temp->r;
    temp->r = right->l;
    if (temp->r)
        temp->r->p = temp;
    right->p = temp->p;
    if (!temp->p)
        root = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;
    right->l = temp;
    temp->p = right;
}

void fixup(node *root, node *pt)
{
    node *parent_pt = NULL;
    node *grand_parent_pt = NULL;

    while ((pt != root) && (pt->c != 0) && (pt->p->c == 1))
    {
        parent_pt = pt->p;
        grand_parent_pt = pt->p->p;

        /*  Case : A
             Parent of pt is left child
             of Grand-parent of
           pt */
        if (parent_pt == grand_parent_pt->l)
        {

            struct node *uncle_pt = grand_parent_pt->r;

            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->c == 1)
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }

            else
            {

                /* Case : 2
                     pt is right child of its parent
                     Left-rotation required */
                if (pt == parent_pt->r)
                {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /* Case : 3
                     pt is left child of its parent
                     Right-rotation required */
                rightrotate(grand_parent_pt);
                if (grand_parent_pt == root)
                    root = grand_parent_pt->p;
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }

        /* Case : B
             Parent of pt is right
             child of Grand-parent of
           pt */
        else
        {
            struct node *uncle_pt = grand_parent_pt->l;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->c == 1))
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->l)
                {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /* Case : 3
                     pt is right child of its parent
                     Left-rotation required */
                leftrotate(grand_parent_pt);
                if (grand_parent_pt == root)
                    root = grand_parent_pt->p;
                // printf("pt %d", pt->d);
                // inorder(root);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
    }

    root->c = 0;
}

node *find(node *ptr, int x)
{
    if (ptr == NULL)
        return NULL;
    if (ptr->d == x)
        return ptr;
    else if (ptr->d < x)
        return find(ptr->r, x);
    else
        return find(ptr->l, x);
    return NULL;
}

void inorder(node *trav)
{
    if (trav == NULL)
        return;
    inorder(trav->l);
    printf("%d %s", trav->d, trav->c ? "red\n" : "black\n");
    inorder(trav->r);
}

int main()
{
    char str[15];
    scanf("%s", str);
    node *tmp;
    int x;
    if (*str == 'r')
    {
        while (*str != 'q')
        {
            scanf("%s", str);
            if (*str == 'i')
            {
                scanf("%d", &x);
                tmp = new_node(x);
                root = bst(root, tmp);
                if (!dup)
                    fixup(root, tmp);
            }
            else if (*str == 's')
            {
                scanf("%d", &x);
                tmp = find(root, x);
                if (tmp)
                    printf("%s", tmp->c ? "red\n" : "black\n");
                else
                    printf("Not found\n");
            }
            else if (*str == 'e')
            {
                scanf("%d", &x);
                tmp = find(root, x);
                if (tmp)
                    printf("exist\n");
                else
                    printf("Not exist\n");
            }
        }
    }

    return 0;
}