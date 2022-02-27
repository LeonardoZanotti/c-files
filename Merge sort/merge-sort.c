#include <stdio.h>

#define LIMIT 10

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void insertionSort(int array[], int size)
{
    for (int step = 1; step < size; step++)
    {
        int key = array[step];
        int j = step - 1;

        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int h)
{
    int size = h - l + 1;
    if (size < LIMIT)
    {
        insertionSort(arr, size);
        return;
    }

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = h - m;

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

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int size)
{
    int notSorted = 1, subIsSorted = 0, l = 0, m, h, i;

    while (notSorted)
    {
        notSorted = 0;
        subIsSorted = 1;
        if (l >= size || m >= size)
            l = 0;

        m = l + 1;

        while (m < size && arr[m] <= arr[m + 1])
            m++;

        if (m < size)
        {
            h = m + 1;
            while (h < size && arr[h] <= arr[h + 1])
                h++;
        }

        for (i = l; i < h; i++)
            if (arr[i] < arr[i + 1])
                subIsSorted = 0;

        if (!subIsSorted)
            merge(arr, l, m, h);

        i = 0;
        while (arr[i] <= arr[i + 1])
            i++;

        l = h;
        notSorted = i < size;
    }
}

int main()
{
    int data[] = {9, 5, 1, 4, 3, 15, 3, 7, 2, 8, 20, 5, 12, 11, 16};
    int size = sizeof(data) / sizeof(data[0]);
    mergeSort(data, size);
    printf("Sorted array in ascending order:\n");
    printArray(data, size);
}