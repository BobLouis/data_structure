#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LENGTH 100

void push(char element[], char stack[], int *top, int stackSize)
{
    if (*top == -1)
    {
        int i;
        for (i = 0; element[i] != '\0'; ++i)
        {
            stack[(stackSize - 1) * stackSize + i] = element[i];
        }
        stack[(stackSize - 1) * stackSize + i] = '\0';
        *top = stackSize - 1;
    }
    else if (*top == 0)
    {
        printf("the stack is full\n");
    }
    else
    {
        int i;
        for (i = 0; element[i] != '\0'; ++i)
        {
            stack[(*top - 1) * stackSize + i] = element[i];
        }
        stack[(*top - 1) * stackSize + i] = '\0';
        (*top)--;
    }
}

void pop(char stack[], int *top, int stackSize)
{
    if (*top == -1)
    {
        printf("the stack is empty\n");
    }
    else
    {
        // printf("element popped: ");
        // for (int i = 0; stack[(*top) * stackSize + i] != '\0'; ++i)
        // {
        //     printf("%c", stack[(*top) * stackSize + i]);
        // }
        // printf("\n");
        if ((*top) == stackSize - 1)
            (*top) = -1;
        else
            (*top)++;
    }
}

char *top_ele(char stack[], int top, int stackSize)
{
    if (top == -1)
    {
        printf("stack empty\n");
        return 0;
    }
    else
    {
        // printf("the top elemet is : ");
        // for (int i = 0; stack[(top)*stackSize + i] != '\0'; ++i)
        // {
        //     printf("%c", stack[(top)*stackSize + i]);
        // }
        // printf("\n");
        return &(stack[(top)*stackSize]);
    }
}

bool isOperator(char x)
{
    switch (x)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '%':
        return true;
    default:
        return false;
    }
}

int main()
{
    char expression[LENGTH];
    char ch;
    int count = 0;
    //inout the first expression
    while ((ch = getchar()) != '\n')
    {
        expression[count] = ch;
        ++count;
    }

    int i, j, index;
    int stackSize = count + 2;
    char *temp = malloc((count + 1) * sizeof(char));
    char *operand1 = malloc((count + 1) * sizeof(char));
    char *operand2 = malloc((count + 1) * sizeof(char));
    char *stack = malloc(stackSize * stackSize * sizeof(char));
    int top = -1;
    printf("expression :");
    for (i = 0; i < count; ++i)
    {
        printf("%c", expression[i]);
    }
    printf("\n");
    //prefix to postfix
    for (i = count - 1; i >= 0; --i)
    {
        if (isOperator(expression[i]))
        {
            operand1 = top_ele(stack, top, stackSize);
            pop(stack, &top, stackSize);
            operand2 = top_ele(stack, top, stackSize);
            pop(stack, &top, stackSize);

            printf("operand 1 %s\n", operand1);
            printf("operand 2:%s\n", operand2);

            for (j = 0; operand1[j] != '\0'; ++j)
                ;
            index = j;
            for (j = 0; operand2[j] != '\0'; ++j)
            {
                operand1[index + j] = operand2[j];
            }
            operand1[index + j] = expression[i];
            printf("combined string push: %s\n", operand1);
            push(operand1, stack, &top, stackSize);
        }
        else
        {
            printf("stack push %c\n", expression[i]);
            temp[0] = expression[i];
            temp[1] = '\0';
            push(temp, stack, &top, stackSize);
        }
    }
    printf("result %s\n", top_ele(stack, top, stackSize));
    pop(stack, &top, stackSize);

    //read the second expression
    count = 0;
    //inout the first expression
    while ((ch = getchar()) != EOF)
    {
        expression[count] = ch;
        ++count;
    }
    printf("expression :");
    for (i = 0; i < count; ++i)
    {
        printf("%c", expression[i]);
    }
    printf("\n");

    //postfix to prefix
    for (i = 0; i < count; ++i)
    {
        if (isOperator(expression[i]))
        {
            operand1 = top_ele(stack, top, stackSize);
            pop(stack, &top, stackSize);
            operand2 = top_ele(stack, top, stackSize);
            pop(stack, &top, stackSize);

            printf("operand 1 %s\n", operand1);
            printf("operand 2:%s\n", operand2);

            temp[0] = expression[i];
            for (j = 0; operand2[j] != '\0'; ++j)
                temp[j + 1] = operand2[j];
            index = j + 2;
            for (j = 0; operand1[j] != '\0'; ++j)
            {
                temp[index + j] = operand1[j];
            }
            printf("combined string push: %s\n", temp);
            push(temp, stack, &top, stackSize);
        }
        else
        {
            printf("stack push %c\n", expression[i]);
            temp[0] = expression[i];
            temp[1] = '\0';
            push(temp, stack, &top, stackSize);
        }
    }
    printf("result %s\n", top_ele(stack, top, stackSize));
    pop(stack, &top, stackSize);
    return 0;
}