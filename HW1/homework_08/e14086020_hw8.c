#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 100

typedef struct node
{
    char val;
    struct node *left;
    struct node *right;
} Node;

int n, x, y;
char *str;
Node *list[maxN];

Node *init(char ch)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->val = ch;
    tmp->left = tmp->right = NULL;
    return tmp;
}

Node *build(Node *root)
{
    int top = 0;
    Node *cur = root, *tmp;
    Node **stk = (Node **)malloc(sizeof(Node) * maxN);

    cur->val = *(++str);
    cur->left = NULL, cur->right = NULL;
    str++;

    while (*str)
    {
        if (*str == '(')
            tmp = init(*(++str)), cur->left = tmp, stk[++top] = tmp;
        else if (*str == ',')
            tmp = init(*(++str)), cur->right = tmp, stk[top] = tmp;
        else if (*str == ')')
            top--;
        cur = stk[top], str++;
    }
    return root;
}

void write(Node *root, int flag)
{
    printf("%c%c", flag ? '(' : ',', root->val);
    if (root->left)
        write(root->left, 1);
    if (root->right)
        write(root->right, 0);
    if (flag)
        printf("%c", ')');
}

void sort(Node *root)
{
    char ch = root->val;
    if (root->right && root->right->val < root->val)
        root->val = root->right->val, root->right->val = ch;
    if (root->left)
        sort(root->left);
    if (root->right)
        sort(root->right);
}

void getstr(Node *root, char *ch)
{
    strcat(ch, &root->val);
    if (root->left)
        getstr(root->left, ch);
    if (root->right)
        getstr(root->right, ch);
}

int isequal(Node *a, Node *b)
{
    char *as, *bs;
    as = (char *)malloc(sizeof(char) * maxN), bs = (char *)malloc(sizeof(char) * maxN);
    getstr(a, as), getstr(b, bs);
    return !strcmp(as, bs);
}

int main()
{
    str = (char *)malloc(sizeof(char) * maxN);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", str);
        if (*str == 'r')
        {
            scanf("%d%s", &x, str);
            list[x] = (Node *)malloc(sizeof(Node));
            build(list[x]), sort(list[x]);
            printf("readed\n");
        }
        else if (*str == 'i')
        {
            scanf("%d%d", &x, &y);
            printf(isequal(list[x], list[y]) ? "true\n" : "false\n");
        }
        else if (*str == 'w')
        {
            scanf("%d", &x);
            write(list[x], 1);
            printf("\n");
        }
        else if (*(str + 1) == 'o')
        {
            scanf("%d%d", &x, &y);
            list[y] = list[x];
            printf("copied\n");
        }
        else if (*(str + 1) == 'l')
        {
            scanf("%d", &x);
            printf("cleared\n");
        }
    }
}
