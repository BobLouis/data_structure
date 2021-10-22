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

void erase(polyNode *a)
{
    polyNode *ptr = a->link;
    polyNode *prev;
    while (ptr != a)
    {
        prev = ptr;
        ptr = ptr->link;
        // printf("deleting %d %d\n", prev->coef, prev->expon);
        free(prev);
    }
    // printf("deleting %d %d\n", a->coef, a->expon);
    free(a);
}

float eval(polyNode *a, float x)
{
    float answer = 0;
    polyNode *ptr;
    ptr = a;
    ptr = ptr->link;
    for (; ptr != a; ptr = ptr->link)
    {
        answer += pow(x, ptr->expon) * ptr->coef;
    }
    answer = (int)floor(answer * 100);
    answer = (float)answer / 100;
    printf("%.2f", answer);
    return answer;
}

int main()
{
    int num, data, num_data, name_count = 0;
    char command[7];
    char input_name[50];
    char name[10][50];
    int *name_arr[10];
    polyNode *node[10];
    int node_size[10];
    scanf("%d", &num);
    for (int i = 0; i < num; ++i)
    {
        scanf("%6s", command);
        if (strcmp(command, "pread") == 0)
        { // push command, call push()
            scanf("%49s", name[name_count]);
            scanf("%d", &num_data);
            node_size[name_count] = num_data * 2;
            name_arr[name_count] = malloc(num_data * 2 * sizeof(int));
            for (int i = 0; i < num_data * 2; i += 2)
            {
                scanf("%d", &name_arr[name_count][i]);
                scanf("%d", &name_arr[name_count][i + 1]);
            }
            node[name_count] = new_node(-1, -1);
            read_node(node[name_count], name_arr[name_count], node_size[name_count]);
            printf("ok\n");
            ++name_count;
        }
        else if (strcmp(command, "pwrite") == 0)
        {
            scanf("%49s", input_name);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    write_node(node[i]);
                    break;
                }
            }
        }
        else if (strcmp(command, "padd") == 0)
        {
            scanf("%49s", name[name_count]);
            int operand1, operand2;
            scanf("%49s", input_name);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    operand1 = i;
                    break;
                }
            }
            scanf("%49s", input_name);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    operand2 = i;
                    break;
                }
            }

            node[name_count] = cpadd(node[operand1], node[operand2]);
            printf("added\n");
            name_count++;
        }
        else if (strcmp(command, "perase") == 0)
        {
            scanf("%49s", input_name);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    erase(node[i]);
                    name_count--;
                    break;
                }
            }
            printf("erased\n");
        }
        else if (strcmp(command, "psub") == 0)
        {
            scanf("%49s", name[name_count]);
            int operand1, operand2;
            scanf("%49s", input_name);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    operand1 = i;
                    break;
                }
            }
            scanf("%49s", input_name);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    operand2 = i;
                    break;
                }
            }

            node[name_count] = cpsub(node[operand1], node[operand2]);
            printf("substracted\n");
            name_count++;
        }
        else if (strcmp(command, "pmult") == 0)
        {
            scanf("%49s", name[name_count]);
            int operand1, operand2;
            scanf("%49s", input_name);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    operand1 = i;
                    break;
                }
            }
            scanf("%49s", input_name);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    operand2 = i;
                    break;
                }
            }

            node[name_count] = cpmult(node[operand1], node[operand2]);
            printf("multiplied\n");
            name_count++;
        }
        else if (strcmp(command, "eval") == 0)
        {
            float x;
            scanf("%49s", input_name);
            scanf("%f", &x);
            for (int i = 0; i < name_count; ++i)
            {
                if (strcmp(name[i], input_name) == 0)
                {
                    eval(node[i], 2.5);
                    break;
                }
            }
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