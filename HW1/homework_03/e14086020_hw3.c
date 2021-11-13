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

void print_data(term *a)
{
    int num = a[0].value;
    for (int i = 0; i <= num; ++i)
    {
        printf("%d %d %d \n", a[i].row, a[i].col, a[i].value);
    }
}
int main()
{
    term a[MAX_COL];
    term b[MAX_COL];
    int i = 0, x, y, z;
    while (~scanf("%d%d%d", &x, &y, &z))
    {
        a[i].row = x;
        a[i].col = y;
        a[i].value = z;
        ++i;
    }
    fast_transpose_mod(a, b);
    print_data(b);
}