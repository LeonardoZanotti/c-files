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

void mergeSort(int arr[], int l, int h)
{
    int notSorted = 0, i;

    if (l < h)
    {
        int m = (l + h) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, h);

        for (i = 0; i < h; i++)
            if (arr[i] > arr[i + 1])
                notSorted = 1;

        if (notSorted)
            merge(arr, l, m, h);
    }
}

int main()
{
    int data[] = {9, 5, 1, 4, 3};
    int size = sizeof(data) / sizeof(data[0]);
    mergeSort(data, 0, size - 1);
    // insertionSort(data, size);
    printf("Sorted array in ascending order:\n");
    printArray(data, size);
}
