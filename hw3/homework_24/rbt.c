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
void red_black_transplant(node *, node *);
node *tree_minimum(struct node *x);
void red_black_delete_fixup(node *x);
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

node *tree_minimum(node *x)
{
    while (x->l != NULL)
    {
        x = x->l;
    }
    return x;
}

void red_black_delete(struct node *z)
{
    struct node *y, *x;
    int yOriginalColor;

    y = z;
    yOriginalColor = y->c;

    if (z->l == NULL)
    {
        x = z->r;
        red_black_transplant(z, z->r);
    }
    else if (z->r == NULL)
    {
        x = z->l;
        red_black_transplant(z, z->l);
    }
    else
    {
        y = tree_minimum(z->r);
        yOriginalColor = y->c;
        x = y->r;

        if (y->p == z)
        {
            x->p = y;
        }
        else
        {
            red_black_transplant(y, y->r);
            y->r = z->r;
            y->r->p = y;
        }

        red_black_transplant(z, y);
        y->l = z->l;
        y->l->p = y;
        y->c = z->c;
    }

    if (yOriginalColor == 0)
    {
        red_black_delete_fixup(x);
    }
}

/*
 * As y was black and removed x gains y's extra blackness.
 * Move the extra blackness of x until
 *		1. x becomes root. In that case just remove extra blackness
 *		2. x becomes a RED and BLACK node. in that case just make x BLACK
 *
 * First check if x is x's parents left or right child. Say x is left child
 *
 * There are 4 cases.
 *
 * Case 1: x's sibling w is red. transform case 1 into case 2 by recoloring
 * w and x's parent. Then left rotate x's parent.
 *
 * Case 2: x's sibling w is black, w's both children is black. Move x and w's
 * blackness to x's parent by coloring w to RED and x's parent to BLACK.
 * Make x's parent new x.Notice if case 2 come through case 1 x's parent becomes 
 * RED and BLACK as it became RED in case 1. So loop will stop in next iteration.
 *
 * Case 3: w is black, w's left child is red and right child is black. Transform
 * case 3 into case 4 by recoloring w and w's left child, then right rotate w.
 *
 * Case 4: w is black, w's right child is red. recolor w with x's parent's color.
 * make x's parent BLACK, w's right child black. Now left rotate x's parent. Make x
 * point to root. So loop will be stopped in next iteration.
 *
 * If x is right child of it's parent do exact same thing swapping left<->right
 */

void red_black_delete_fixup(node *x)
{
    node *w;

    while (x != root && x->c == 0)
    {

        if (x == x->p->l)
        {
            w = x->p->r;

            if (w->c == 1)
            {
                w->c = 0;
                x->p->c = 0;
                leftrotate(x->p);
                w = x->p->r;
            }

            if (w->l->c == 0 && w->r->c == 0)
            {
                w->c = 0;
                x->p->c = 0;
                x = x->p;
            }
            else
            {

                if (w->r->c == 0)
                {
                    w->c = 0;
                    w->l->c = 0;
                    rightrotate(w);
                    w = x->p->r;
                }

                w->c = x->p->c;
                x->p->c = 0;
                x->r->c = 0;
                leftrotate(x->p);
                x = root;
            }
        }
        else
        {
            w = x->p->l;

            if (w->c == 0)
            {
                w->c = 0;
                x->p->c = 0;
                rightrotate(x->p);
                w = x->p->l;
            }

            if (w->l->c == 0 && w->r->c == 0)
            {
                w->c = 0;
                x->p->c = 0;
                x = x->p;
            }
            else
            {

                if (w->l->c == 0)
                {
                    w->c = 0;
                    w->r->c = 0;
                    leftrotate(w);
                    w = x->p->l;
                }

                w->c = x->p->c;
                x->p->c = 0;
                w->l->c = 0;
                rightrotate(x->p);
                x = root;
            }
        }
    }

    x->c = 0;
}

/* replace node u with node v */
void red_black_transplant(struct node *u, struct node *v)
{
    if (u == root)
    {
        root = v;
    }
    else if (u == u->p->l)
    {
        u->p->l = v;
    }
    else
    {
        u->p->r = v;
    }

    v->p = u->p;
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
            else if (*str == 'd')
            {
                scanf("%d", &x);
                tmp = find(root, x);
                if (tmp)
                    red_black_delete(tmp);
            }
        }
    }

    return 0;
}