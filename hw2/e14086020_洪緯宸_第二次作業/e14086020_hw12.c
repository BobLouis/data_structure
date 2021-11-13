#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000

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

void change(Heap *heap, int origin, int modified)
{
    //change the data in the array
    int index = 0;

    for (int i = 1; i <= heap->size; ++i)
    {
        if (heap->data[i] == origin)
        {
            index = i;
            break;
        }
    }
    if (!index)
        return; //can't find the element

    //change the modified position
    if (modified < origin) //change the index up
    {
        while (modified < heap->data[parent(index)])
        {
            heap->data[index] = heap->data[parent(index)];
            index = parent(index);
        }
    }
    else //change the index down
    {
        while (left(index) <= heap->size)
        {
            if (right(index <= heap->size) && (modified > heap->data[right(index)] || modified > heap->data[left(index)]))
            {
                if (heap->data[right(index)] < heap->data[left(index)]) //deter which child to change
                {
                    heap->data[index] = heap->data[right(index)];
                    index = right(index);
                }
                else
                {
                    heap->data[index] = heap->data[left(index)];
                    index = left(index);
                }
            }
            else if (modified > heap->data[left(index)])
            {
                heap->data[index] = heap->data[left(index)];
                index = left(index);
            }
            else
                break;
        }
    }

    heap->data[index] = modified;
}

int pop_min(Heap *heap)
{
    int index = 1;
    int top = heap->data[1];
    int last = heap->data[heap->size--];
    while (left(index) <= heap->size)
    {
        if (right(index <= heap->size) && (last > heap->data[right(index)] || last > heap->data[left(index)]))
        {
            if (heap->data[right(index)] < heap->data[left(index)]) //deter which child to change
            {
                heap->data[index] = heap->data[right(index)];
                index = right(index);
            }
            else
            {
                heap->data[index] = heap->data[left(index)];
                index = left(index);
            }
        }
        else if (last > heap->data[left(index)])
        {
            heap->data[index] = heap->data[left(index)];
            index = left(index);
        }
        else
            break;
    }
    heap->data[index] = last;
    return top;
}
// int verify(Heap *heap)
// {
//     for (int i = 1; i << 1 < heap->size; i++)
//     {
//         if (heap->data[i << 1] < heap->data[i] || heap->data[i << 1 | 1] < heap->data[i])
//             return 0;
//     }
//     return 1;
// }

int main()
{
    Heap *heap = create();
    int n = 10;
    int arr[] = {6, 2, 4, 8, 7, 9, 1, 3, 5, 10};
    for (int i = 0; i < n; ++i)
    {
        insert(heap, arr[i]);
    }
    change(heap, 1, 50);
    for (int i = 0; i < n; ++i)
    {
        printf("pop:%d \n", pop_min(heap));
    }
    return 0;
}
