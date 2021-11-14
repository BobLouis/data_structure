#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    struct Node *next;
    float e, c;
} * nodes[200];

float x;
int n, t, idx;
char str1[15], str2[15], str3[15];
char in_n[50], name[10][50];
int n_cnt = 0;
struct Node *read()
{
    struct Node *head = malloc(sizeof(struct Node)), *s = head;
    head->next = NULL;
    while (t--)
    {
        scanf("%f%f", &s->c, &s->e);
        if (t)
        {
            s->next = malloc(sizeof(struct Node));
            s = s->next;
        }
        else
        {
            s->next = NULL;
        }
    }
    puts("ok");
    return head;
}

void write(struct Node *head)
{
    while (head->next)
    {
        printf("%0.fx^%0.f", head->c, head->e);
        head = head->next;
        if (head->c >= 0)
            printf("+");
    }
    printf("%0.fx^%0.f\n", head->c, head->e);
}

struct Node *add(struct Node *a, struct Node *b)
{
    struct Node *head = malloc(sizeof(struct Node));
    head->next = NULL;
    struct Node *p1 = a, *p2 = b, *tmp, *last = head;
    while (p1 && p2)
    {
        tmp = malloc(sizeof(struct Node));
        tmp->next = NULL;
        if (p1->e > p2->e)
        {
            tmp->c = p1->c;
            tmp->e = p1->e;
            p1 = p1->next;
        }
        else if (p1->e < p2->e)
        {
            tmp->c = p2->c;
            tmp->e = p2->e;
            p2 = p2->next;
        }
        else
        {
            tmp->c = p1->c + p2->c;
            tmp->e = p1->e;
            if (!tmp->c)
                tmp = NULL;
            p1 = p1->next;
            p2 = p2->next;
        }
        if (tmp)
        {
            last->next = tmp;
            last = last->next;
        }
    }
    if (p1 && p1->c)
        last->next = p1;
    if (p2 && p2->c)
        last->next = p2;

    return head->next;
}

struct Node *sub(struct Node *a, struct Node *b)
{
    struct Node *p = b, *nb = malloc(sizeof(struct Node));
    struct Node *pnb = nb;
    while (p)
    {
        pnb->c = -1 * p->c;
        pnb->e = p->e;
        p = p->next;
        if (!p)
            break;
        pnb->next = malloc(sizeof(struct Node));
        pnb = pnb->next;
    }
    pnb = NULL;
    puts("substracted");
    return add(a, nb);
}

struct Node *smul(struct Node *a, struct Node *b)
{
    struct Node *head = malloc(sizeof(struct Node));
    head->next = NULL;
    struct Node *p1 = a, *p2 = b, *tmp, *last = head;
    while (p2)
    {
        tmp = malloc(sizeof(struct Node));
        tmp->next = NULL;
        tmp->c = p1->c * p2->c;
        tmp->e = p1->e + p2->e;
        last->next = tmp;
        last = last->next;
        p2 = p2->next;
    }
    return head->next;
}

struct Node *mul(struct Node *a, struct Node *b)
{
    struct Node *head = malloc(sizeof(struct Node)), *tmp;
    head->next = NULL;

    for (struct Node *p1 = a, *p2 = b; p1; p1 = p1->next)
    {
        tmp = smul(p1, p2);
        head = add(head, tmp);
    }
    puts("multiplied");
    return head;
}

float eval(struct Node *a, float x)
{
    float sum = 0.0;
    while (a)
    {
        sum += (a->c * powf(x, a->e));
        a = a->next;
    }
    return sum;
}

int find_name(char in_name[])
{
    for (int i = 0; i < n_cnt; ++i)
    {
        if (!strcmp(name[i], in_name))
        {
            return i;
        }
    }
    return -1;
}

int insert_n(char *in_name)
{
    int res = find_name(in_name);
    if (~res)
        return res;
    else
    {
        strcpy(name[n_cnt], in_name);
        return n_cnt++;
    }
}
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", str1);
        if (!strcmp(str1, "pread"))
        {
            scanf("%s%d", in_n, &t);
            idx = insert_n(in_n);
            nodes[idx] = read();
        }
        else if (!strcmp(str1, "pwrite"))
        {
            scanf("%s", in_n);
            write(nodes[find_name(in_n)]);
        }
        else if (!strcmp(str1, "padd"))
        {
            scanf("%s%s%s", in_n, str2, str3);
            idx = insert_n(in_n);
            nodes[idx] = add(nodes[find_name(str2)], nodes[find_name(str3)]);
            puts("added");
        }
        else if (!strcmp(str1, "perase"))
        {
            scanf("%s", str1);
            idx = find_name(str1);
            nodes[idx] = malloc(sizeof(struct Node));
            nodes[idx]->next = NULL;
            puts("erased");
        }
        else if (!strcmp(str1, "psub"))
        {
            scanf("%s%s%s", in_n, str2, str3);
            idx = insert_n(in_n);
            nodes[idx] = sub(nodes[find_name(str2)], nodes[find_name(str3)]);
        }
        else if (!strcmp(str1, "pmult"))
        {
            scanf("%s%s%s", in_n, str2, str3);
            idx = insert_n(in_n);
            nodes[idx] = mul(nodes[find_name(str2)], nodes[find_name(str3)]);
        }
        else
        {
            scanf("%s%f", str1, &x);
            printf("%0.2f", eval(nodes[find_name(str1)], x));
        }
    }
}