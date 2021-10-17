#include <stdio.h>
#include <stdlib.h>
typedef struct polyNode
{
    int coef;
    int expon;
    struct polyNode *link;
} polyNode;

polyNode *new_node(int coef, int expon)
{
    polyNode *temp;
    temp = malloc(sizeof(temp));
    temp->coef = coef;
    temp->expon = expon;
    return temp;
}

void read_node(polyNode *a, polyNode *b, int a_arr[], int b_arr[], int size_a, int size_b)
{

    polyNode *ptr;
    ptr = a;
    for (int i = 0; i < size_a; i += 2)
    {
        ptr->link = new_node(a_arr[i], a_arr[i + 1]);
        ptr = ptr->link;
    }
    ptr->link = a;
    ptr = b;
    for (int i = 0; i < size_b; i += 2)
    {
        ptr->link = new_node(b_arr[i], b_arr[i + 1]);
        ptr = ptr->link;
    }
    ptr->link = b;
}

void print_node(polyNode *a)
{
    polyNode *ptr;
    ptr = a->link;
    for (; ptr != a; ptr = ptr->link)
        printf("coef: %d expon: %d\n", ptr->coef, ptr->expon);
}

void attach(int coef, int expon, polyNode *ptr)
{
    polyNode *temp;
    temp = new_node(coef, expon);
    temp->link = ptr->link;
    ptr->link = temp;
    ptr = temp;
}

polyNode *cpadd(polyNode *a, polyNode *b)
{
    polyNode *ptr_a, *ptr_b, *ptr_c, *c;
    int sum;
    ptr_a = a;
    ptr_b = b;
    //skip the header of the list
    ptr_a = ptr_a->link;
    ptr_b = ptr_b->link;
    c = new_node(-1, -1);
    ptr_c = c;
    while (1)
    {
        if (ptr_a->expon > ptr_b->expon)
        {
            // printf("a coef%d expo%d\n", ptr_a->coef, ptr_a->expon);
            attach(ptr_a->coef, ptr_a->expon, ptr_c);
            ptr_c = ptr_c->link; //move the pointer to the current node
            ptr_a = ptr_a->link;
        }
        else if (ptr_a->expon == ptr_b->expon)
        {
            // printf("a=b coef%d expo%d\n", ptr_a->coef, ptr_a->expon);
            if (ptr_a == a)
                break;
            sum = ptr_a->coef + ptr_b->coef;
            if (sum)
            {
                attach(sum, ptr_a->expon, ptr_c);
                ptr_c = ptr_c->link;
                ptr_b = ptr_b->link;
                ptr_a = ptr_a->link;
            }
        }
        else
        {
            // printf("b coef%d expo%d\n", ptr_b->coef, ptr_b->expon);
            attach(ptr_b->coef, ptr_b->expon, ptr_c);
            ptr_c = ptr_c->link; //move the pointer to the current node
            ptr_b = ptr_b->link;
        }
    }
    ptr_c->link = c;
    return c;
}

polyNode *cpsub(polyNode *a, polyNode *b)
{
    polyNode *ptr_a, *ptr_b, *ptr_c, *c;
    int sum;
    ptr_a = a;
    ptr_b = b;
    //skip the header of the list
    ptr_a = ptr_a->link;
    ptr_b = ptr_b->link;
    c = new_node(-1, -1);
    ptr_c = c;
    while (1)
    {
        if (ptr_a->expon > ptr_b->expon)
        {
            // printf("a coef%d expo%d\n", ptr_a->coef, ptr_a->expon);
            attach(ptr_a->coef, ptr_a->expon, ptr_c);
            ptr_c = ptr_c->link; //move the pointer to the current node
            ptr_a = ptr_a->link;
        }
        else if (ptr_a->expon == ptr_b->expon)
        {
            // printf("a=b coef%d expo%d\n", ptr_a->coef, ptr_a->expon);
            if (ptr_a == a)
                break;
            sum = ptr_a->coef - ptr_b->coef;
            if (sum)
            {
                attach(sum, ptr_a->expon, ptr_c);
                ptr_c = ptr_c->link;
                ptr_b = ptr_b->link;
                ptr_a = ptr_a->link;
            }
        }
        else
        {
            // printf("b coef%d expo%d\n", ptr_b->coef, ptr_b->expon);
            attach(ptr_b->coef * -1, ptr_b->expon, ptr_c);
            ptr_c = ptr_c->link; //move the pointer to the current node
            ptr_b = ptr_b->link;
        }
    }
    ptr_c->link = c;
    return c;
}

polyNode *cpmult(polyNode *a, polyNode *b)
{
    polyNode *ptr_a, *ptr_b, *ptr_c, *ptr, *c;
    int expon, add = 0;
    int count = 0, i, min_expo;
    c = new_node(-1, -1);
    ptr_c = c;
    for (ptr_a = a->link; ptr_a != a; ptr_a = ptr_a->link)
    {
        for (ptr_b = b->link; ptr_b != b; ptr_b = ptr_b->link)
        {
            // printf("a coeff:%d expo: %d\n", ptr_a->coef, ptr_a->expon);
            // printf("b coeff:%d expo: %d\n", ptr_b->coef, ptr_b->expon);
            // printf("coeff:%d expo: %d\n", ptr_a->coef * ptr_b->coef, ptr_a->expon + ptr_b->expon);
            expon = ptr_a->expon + ptr_b->expon;
            if (expon >= min_expo)
            {
                for (ptr = c->link, i = 0; i < count; ptr = ptr->link, ++i)
                {
                    if (ptr->expon == expon)
                    {
                        ptr->coef += ptr_a->coef * ptr_b->coef;
                        add = 1;
                        break;
                    }
                }
            }
            if (!add)
            {
                attach(ptr_a->coef * ptr_b->coef, ptr_a->expon + ptr_b->expon, ptr_c);
                min_expo = ptr_a->expon + ptr_b->expon;
                ++count;
                ptr_c = ptr_c->link;
            }
            add = 0;
        }
    }
    ptr_c->link = c;
    return c;
}

void write_node(polyNode *a)
{
    polyNode *ptr;
    ptr = a;
    ptr = ptr->link;
    for (; ptr != a; ptr = ptr->link)
    {
        printf("%dx^%d", ptr->coef, ptr->expon);
        if (ptr->link != a && ptr->coef > 0)
            printf("+");
    }
    printf("\n");
}

int main()
{
    polyNode *a, *b, *c, *ptr;
    a = new_node(-1, -1);
    b = new_node(-1, -1);

    int a_arr[] = {2, 2, 1, 1};
    int b_arr[] = {3, 2, 2, 1};
    int size_a = sizeof(a_arr) / sizeof(a_arr[0]);
    int size_b = sizeof(b_arr) / sizeof(b_arr[0]);
    read_node(a, b, a_arr, b_arr, size_a, size_b);
    printf("node a\n");
    print_node(a);
    printf("node b\n");
    print_node(b);
    // ptr = a;
    // ptr = ptr->link->link;
    // printf("ptr_before attach %d\n", ptr->coef);
    // attach(5, 5, ptr);
    // ptr = ptr->link;
    // printf("ptr after attach %d\n", ptr->coef);
    // printf("node a after attach\n");
    // print_node(a);
    c = cpmult(a, b);
    printf("node c after mul\n");
    write_node(c);
    return 0;
}