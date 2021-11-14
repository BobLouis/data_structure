#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int t, c, e, n, n_cnt = 0;
char command[7], in_n[50], name[10][50];
Node *node[10]; //node index by n_cnt
typedef struct Node
{
    int cof;
    int exp;
    struct Node *link;
} Node;

Node *new_node(int cof, int exp)
{
    Node *tmp;
    tmp = malloc(sizeof(tmp));
    tmp->cof = cof;
    tmp->exp = exp;
    return tmp;
}

Node *read()
{
    Node *head = new_node(-1, -1), *ptr = head;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &c, &e);
        ptr->link = new_node(c, e);
        ptr = ptr->link;
    }
    ptr->link = head;
    return head;
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

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%6s", command);
        if (!strcmp(command, "pread"))
        {
            scanf("%49s", name[n_cnt]);
            node[n_cnt] = read();
            ++n_cnt;
        }
        else if (!strcmp(command, "pwrite"))
        {
            scanf("%49s", in_n);
            write_node(node[find_name(in_n)]);
        }
        else if (!strcmp(command, "padd"))
        {
            scanf("%49s", name[n_cnt]);
            int opr1, opr2;
            scanf("%49s", in_n);
            opr1 = find_name(in_n);
            scanf("%49s", in_n);
            opr2 = find_name(in_n);
            node[n_cnt] = cpadd(node[opr1], node[opr2]);
            printf("added\n");
            n_cnt++;
        }
        else if (strcmp(command, "perase") == 0)
        {
            scanf("%49s", in_n);
            for (int i = 0; i < n_cnt; ++i)
            {
                if (strcmp(name[i], in_n) == 0)
                {
                    erase(node[i]);
                    n_cnt--;
                    break;
                }
            }
            printf("erased\n");
        }
        else if (strcmp(command, "psub") == 0)
        {
            scanf("%49s", name[n_cnt]);
            int opr1, opr2;
            scanf("%49s", in_n);
            for (int i = 0; i < n_cnt; ++i)
            {
                if (strcmp(name[i], in_n) == 0)
                {
                    opr1 = i;
                    break;
                }
            }
            scanf("%49s", in_n);
            for (int i = 0; i < n_cnt; ++i)
            {
                if (strcmp(name[i], in_n) == 0)
                {
                    opr2 = i;
                    break;
                }
            }

            node[n_cnt] = cpsub(node[opr1], node[opr2]);
            printf("substracted\n");
            n_cnt++;
        }
        else if (strcmp(command, "pmult") == 0)
        {
            scanf("%49s", name[n_cnt]);
            int opr1, opr2;
            scanf("%49s", in_n);
            for (int i = 0; i < n_cnt; ++i)
            {
                if (strcmp(name[i], in_n) == 0)
                {
                    opr1 = i;
                    break;
                }
            }
            scanf("%49s", in_n);
            for (int i = 0; i < n_cnt; ++i)
            {
                if (strcmp(name[i], in_n) == 0)
                {
                    opr2 = i;
                    break;
                }
            }

            node[n_cnt] = cpmult(node[opr1], node[opr2]);
            printf("multiplied\n");
            n_cnt++;
        }
        else if (strcmp(command, "eval") == 0)
        {
            float x;
            scanf("%49s", in_n);
            scanf("%f", &x);
            for (int i = 0; i < n_cnt; ++i)
            {
                if (strcmp(name[i], in_n) == 0)
                {
                    eval(node[i], 2.5);
                    break;
                }
            }
        }
    }
}