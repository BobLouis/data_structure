#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

char prefix[MAX], postfix[MAX], stack[MAX][MAX];

bool is_oper(char ch)
{
    return ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^'));
}

void prefix_to_postfix()
{
    char operand1[MAX], operand2[MAX];
    int len = (int)strlen(prefix);
    int top = 0, i;
    //top point to the space next to the latest data and is raedy to be stored
    for (i = len - 1; i >= 0; --i)
    {
        if (is_oper(prefix[i]))
        {
            strcpy(operand1, stack[--top]);
            strcpy(operand2, stack[--top]);
            sprintf(stack[top++], "%s%s%c", operand1, operand2, prefix[i]);
        }
        else
        {
            stack[top][0] = prefix[i];
            stack[top][1] = '\0';
            ++top;
        }
    }
    printf("%s", stack[--top]);
}

void postfix_to_prefix()
{
    char operand1[MAX], operand2[MAX];
    int len = (int)strlen(postfix);
    int top = 0, i;
    for (i = 0; i < len; ++i)
    {
        if (is_oper(postfix[i]))
        {
            strcpy(operand1, stack[--top]);
            strcpy(operand2, stack[--top]);
            sprintf(stack[top++], "%c%s%s", postfix[i], operand2, operand1);
        }
        else
        {
            stack[top][0] = postfix[i];
            stack[top][1] = '\0';
            ++top;
        }
    }
    printf("%s", stack[--top]);
}

int main()
{
    scanf("%s", prefix);
    scanf("%s", postfix);
    prefix_to_postfix();
    printf("\n");
    postfix_to_prefix();
    return 0;
}