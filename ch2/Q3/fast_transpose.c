#include <stdio.h>
#include <stdlib.h>
#define MAX_COL 101
typedef struct
{
    int col;
    int row;
    int value;
} term;

void fast_transpose_mod(term a[], term b[])
{
    int startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value, preprev, prev;
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0)
    {
        for (i = 0; i < numCols; ++i)
            startingPos[i] = 0;

        for (i = 1; i <= numTerms; ++i)
            startingPos[a[i].col]++;
        //now startingPos represent the num of each row
        preprev = startingPos[0];
        prev = startingPos[1];
        startingPos[0] = 1;
        for (i = 1; i < numCols; ++i)
        {
            prev = startingPos[i];
            startingPos[i] = startingPos[i - 1] + preprev;
            preprev = prev;
        }

        for (i = 1; i <= numTerms; ++i)
        {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void fast_transpose(term a[], term b[])
{
    int rowTerms[MAX_COL];
    int startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0)
    {
        for (i = 0; i < numCols; ++i)
            rowTerms[i] = 0;

        for (i = 1; i <= numTerms; ++i)
            rowTerms[a[i].col]++;

        printf("rowTerms\n");
        for (i = 0; i < numCols; ++i)
        {
            printf("%3d", rowTerms[i]);
        }
        startingPos[0] = 1;
        for (i = 1; i < numCols; ++i)
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

        printf("starting pos");
        for (i = 0; i < numCols; ++i)
        {
            printf("%3d", startingPos[i]);
        }

        for (i = 1; i <= numTerms; ++i)
        {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
        printf("\nafter starting pos");
        for (i = 0; i < numCols; ++i)
        {
            printf("%3d", startingPos[i]);
        }
        printf("\n");
    }
}
void input_data(int row[], int col[], int value[], term *a)
{
    int num = value[0];
    a[0].row = row[0];
    a[0].col = col[0];
    a[0].value = num;
    for (int i = 1; i <= num; ++i)
    {
        a[i].row = row[i];
        a[i].col = col[i];
        a[i].value = value[i];
    }
}

void print_data(term *a)
{
    int num = a[0].value;
    printf("%d", num);
    printf("row   col   value\n");
    for (int i = 0; i <= num; ++i)
    {
        printf("%3d%6d%7d%3d\n", a[i].row, a[i].col, a[i].value, i);
    }
}
int main()
{
    term a[MAX_COL];
    term b[MAX_COL];
    int a_row[9] = {6, 0, 0, 0, 1, 1, 2, 4, 5};
    int a_col[9] = {6, 0, 3, 5, 1, 2, 3, 0, 2};
    int a_value[9] = {8, 15, 22, -15, 11, 3, -6, 91, 28};
    input_data(a_row, a_col, a_value, a);
    print_data(a);
    fast_transpose_mod(a, b);
    printf("\n");
    print_data(b);
}