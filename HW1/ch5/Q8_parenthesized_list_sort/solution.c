#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

void read_node(polyNode *a, int a_arr[], int size_a)
{
    polyNode *ptr;
    ptr = a;
    for (int i = 0; i < size_a; i += 2)
    {
        ptr->link = new_node(a_arr[i], a_arr[i + 1]);
        ptr = ptr->link;
    }
    ptr->link = a;
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

int main()
{
    int n, id[50], count = 0;
    char command[7], input[50][100];

    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%7s", command);
        if (strcmp(command, "read") == 0)
        { // push command, call push()
            scanf("%d", id[count]);
            scanf("%100s", input[count]);
            ++count;
        }
        else if (strcmp(command, "pwrite") == 0)
        {
                }
    }

    // print_node(node[2]);
    // printf("name %s", name[0]);
    // for (int i = 0; i < 4; ++i)
    // {
    //     printf("%d ", name_arr[0][i]);
    // }
    // printf("\nname %s", name[1]);
    // for (int i = 0; i < 4; ++i)
    // {
    //     printf("%d ", name_arr[1][i]);
    // }
}