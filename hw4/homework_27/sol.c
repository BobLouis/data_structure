#include <stdio.h>
#include <stdlib.h>
#define maxN 1000000
#define swap(x, y) ((x) ^= (y) ^= (x) ^= (y))
//insertion
void InsertSort(int *arr, int len)
{
    int tmp, j, flag;
    for (int i = 1; i < len; i++)
    {
        tmp = arr[i];
        for (j = i - 1; j >= 0; j--)
            if (tmp < arr[j])
                arr[j + 1] = arr[j], flag = 1;
            else
                break;
        if (flag)
            arr[j + 1] = tmp, flag = 0;
    }
}
//quicksort
int median(int a, int b, int c)
{
    if ((a <= b) && (b <= c))
        return b; // a b c
    if ((a <= c) && (c <= b))
        return c; // a c b
    if ((b <= a) && (a <= c))
        return a; // b a c
    if ((b <= c) && (c <= a))
        return c; // b c a
    if ((c <= a) && (a <= b))
        return a; // c a b
    return b;     // c b a
}

int split(int a[], int low, int high)
{
    int mid = (low + high) >> 1;
    int pivot = a[median(low, mid, high)];
    while (1)
    {
        while (low < high && pivot <= a[high])
            high--;
        if (low >= high)
            break;
        a[low++] = a[high];
        while (low < high && a[low] <= pivot)
            low++;
        if (low >= high)
            break;
        a[high--] = a[low];
    }
    a[high] = pivot;
    return high;
}
void QuickSort(int a[], int low, int high)
{
    int index;
    if (low < high)
    {
        index = split(a, low, high);
        QuickSort(a, low, index - 1);
        QuickSort(a, index + 1, high);
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
                swap(arr[idx], arr[idx >> 1]);
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
        swap(arr[1], arr[i]), Heapfy(arr, 1, i - 1);
}

int t, idx = 1, arr[maxN];

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

    int arr[] = {2, 1, 0, 5, 7, 2, 9, 3};
    // InsertSort(arr, 3);
    QuickSort(arr, 0, 7);
    for (int i = 0; i < 8; ++i)
        printf("%d ", arr[i]);
    return 0;
}