#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxN 1000000
// #define swap(x, y) ((x) ^= (y) ^= (x) ^= (y))
//insertion
void InsertSort(int *arr, int len)
{
    int tmp;
    for (int i = 2; i <= len; i++)
    {
        tmp = arr[i];
        for (int j = i - 1; j >= 0; j--)
            if (tmp < arr[j])
                arr[j + 1] = arr[j];
            else
            {
                arr[j + 1] = tmp;
                break;
            }
    }
}
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
//quicksort
void median(int *a, int *b, int *c)
{
    if ((*a <= *b) && (*b <= *c) || (*c <= *b) && (*b <= *a)) //a b c  c b a
        swap(b, c);
    else if ((*b <= *a) && (*a <= *c) || (*c <= *a) && (*a <= *b)) //b a c  c a b
        swap(a, c);
}

int part_med(int arr[], int L, int R)
{
    median(&arr[L], &arr[(R + L) >> 1], &arr[R]);
    int pivot = arr[R];
    int i = (L - 1);
    for (int j = L; j <= R - 1; j++)
        if (arr[j] < pivot)
            i++, swap(&arr[i], &arr[j]);
    swap(&arr[i + 1], &arr[R]);
    return (i + 1);
}

void quickSort_med(int arr[], int L, int R)
{
    if (L < R)
    {
        int pi = part_med(arr, L, R);
        quickSort_med(arr, L, pi - 1);
        quickSort_med(arr, pi + 1, R);
    }
}

int part(int arr[], int L, int R)
{
    // median(&arr[L], &arr[(R + L) >> 1], &arr[R]);
    int pivot = arr[R];
    int i = (L - 1);
    for (int j = L; j <= R - 1; j++)
        if (arr[j] < pivot)
            i++, swap(&arr[i], &arr[j]);
    swap(&arr[i + 1], &arr[R]);
    return (i + 1);
}

void quickSort(int arr[], int L, int R)
{
    if (L < R)
    {
        int pi = part(arr, L, R);
        quickSort(arr, L, pi - 1);
        quickSort(arr, pi + 1, R);
    }
}

//iterative merge
int min(int x, int y) { return (x < y) ? x : y; }
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort_iter(int arr[], int n)
{
    int curr_size;
    int left_start;
    for (curr_size = 1; curr_size <= n; curr_size = 2 * curr_size)
    {
        for (left_start = 0; left_start < n; left_start += 2 * curr_size)
        {
            int mid = min(left_start + curr_size - 1, n);
            int right_end = min(left_start + 2 * curr_size - 1, n);
            merge(arr, left_start, mid, right_end);
        }
    }
}

void MergeSort(int *arr, int L, int R)
{
    int mid, *tmp = (int *)malloc(sizeof(int) * (R - L + 1));
    if (L < R)
    {
        mid = (L + R) >> 1;
        MergeSort(arr, L, mid);
        MergeSort(arr, mid + 1, R);

        int idx = 0, p1 = L, p2 = mid + 1;
        while (p1 <= mid && p2 <= R)
            tmp[idx++] = (arr[p1] < arr[p2] ? arr[p1++] : arr[p2++]);
        while (p1 <= mid)
            tmp[idx++] = arr[p1++];
        while (p2 <= R)
            tmp[idx++] = arr[p2++];
        for (int i = 0; i < idx; i++)
            arr[L + i] = tmp[i];
    }
}

void Heapfy(int *arr, int idx, int len)
{
    if (idx << 1 <= len)
    {
        while ((idx <<= 1) <= len)
        {
            if (idx + 1 <= len && arr[idx + 1] > arr[idx])
                idx += 1;
            if (arr[idx >> 1] < arr[idx])
                swap(&arr[idx], &arr[idx >> 1]);
            else
                break;
        }
    }
}

void HeapSort(int *arr, int len)
{
    for (int i = len >> 1; i >= 1; i--)
        Heapfy(arr, i, len);
    for (int i = len; i > 1; i--)
        swap(&arr[1], &arr[i]), Heapfy(arr, 1, i - 1);
}

int t, idx = 1, arr[maxN];
void print(int *arr, int x)
{
    for (int i = 0; i < x + 1; ++i)
        printf("%d\n", arr[i]);
    printf("\n");
}
int main()
{
    // scanf("%d", &t);
    // while (~scanf("%d", arr + idx))
    //     idx++;
    // idx -= 1;
    // if (t == 0)
    //     InsertSort(arr, idx);
    // if (t == 1)
    //     QuickSort(arr, 1, idx);
    // if (t == 2)
    //     MergeSort(arr, 1, idx);
    // if (t == 3)
    //     HeapSort(arr, idx);
    // for (int i = 1; i <= idx; i++)
    //     printf("%d ", arr[i]);
    // puts("");

    int arr[maxN], ori[maxN];
    int idx = 0;
    clock_t start_t, end_t;
    while (~scanf("%d", arr + idx))
        idx++;
    idx--;

    for (int i = 0; i <= idx; ++i)
        ori[i] = arr[i];
    printf("\n%d\n", idx + 1);
    for (int t = 0; t < 6; ++t)
    {
        start_t = clock();
        switch (t)
        {
        case 0:
            InsertSort(arr, idx);
            // print(arr, idx);
            printf("\ninsertion sort\n");
            break;
        case 1:
            quickSort(arr, 1, idx);
            // print(arr, idx);
            printf("\nquicksort\n");
            break;
        case 2:
            quickSort_med(arr, 1, idx);
            // print(arr, idx);
            printf("\nquickSort three med\n");
            break;
        case 3:
            MergeSort(arr, 1, idx);
            // print(arr, idx);
            printf("\nmerge sort recursive\n");
            break;
        case 4:
            mergeSort_iter(arr, idx);
            // print(arr, idx);
            printf("\nmerge sort iterative\n");
            break;
        case 5:
            HeapSort(arr, idx);
            // print(arr, idx);
            printf("\nHeap sort\n");
            break;
        }

        end_t = clock();
        printf("duration: %lu\n", end_t - start_t);
        for (int i = 0; i <= idx; ++i)
            arr[i] = ori[i];
    }

    // InsertSort(arr, 9);
    // print(arr, 10);
    // quickSort(arr, 1, 9);
    // print(arr, 10);
    // quickSort_med(arr, 1, 9);
    // print(arr, 10);
    // MergeSort(arr, 1, 9);
    // print(arr, 10);
    // HeapSort(arr, 9);
    // print(arr, 10);
    // mergeSort_iter(arr, 9);
    // print(arr, 10);
    return 0;
}