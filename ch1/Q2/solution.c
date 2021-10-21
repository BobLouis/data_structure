#include <stdlib.h>
#include <stdio.h>

void printFunc(int start, int end)
{
    printf("%d -> %d\n", start, end);
}

void hanoi(int n, int start, int end)
{
    //three position labeled as 1 2 3
    int temp = 6 - start - end;
    if (n == 1)
    {
        //if we only move one disk we move it directly
        printFunc(start, end);
        return;
    }
    //we move all the disks except the bottom disk to the temp position
    hanoi(n - 1, start, temp);
    //move the bottom disk to the detination
    printFunc(start, end);
    //move the rest disks to the end
    hanoi(n - 1, temp, end);
}

int main()
{
    hanoi(64, 1, 3);
    return 0;
}