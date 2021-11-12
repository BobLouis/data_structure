#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10000

typedef struct Heap
{
    int *data;    // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int size;     // Current number of elements in min heap
} Heap;

int parent(int i) { return i / 2; }
int left(int i) { return i * 2; }
int right(int i) { return i * 2 + 1; }

Heap *create()
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (int *)malloc(sizeof(int) * MAX_N);
    heap->capacity = MAX_N;
    heap->size = 0;
    heap->data[0] = -1; //to know when the array used up
    return heap;
}

void insert(Heap *heap, int val)
{
    if (heap->size == heap->capacity - 1)
        return; //out of capacity

    int index = ++heap->size; //the position to be place
    while (val < heap->data[parent(index)])
    {
        heap->data[index] = heap->data[parent(index)]; //swap down the parent
        index = parent(index);                         //make the index be the parent index
    }
    heap->data[index] = val;
}

int pop_min(Heap *heap)
{
    int index = 1, child;
    int top = heap->data[1];
    int last = heap->data[heap->size--];
    while (left(index) <= heap->size)
    {
        child = left(index);
        if (child < heap->size && (heap->data[child] > heap->data[child + 1]))
            child++; //choose the smaller child to swap
        if (last <= heap->data[child])
            break;
        else
        {
            heap->data[index] = heap->data[child];
            index = child;
        }
    }
    heap->data[index] = last;
    return top;
}

int main()
{
    Heap *heap = create();
    int n = 10;
    int arr[] = {6, 2, 4, 8, 7, 9, 1, 3, 5, 10};
    for (int i = 0; i < n; ++i)
    {
        insert(heap, arr[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        printf("pop:%d \n", pop_min(heap));
    }
    return 0;
}
