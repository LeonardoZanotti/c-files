#include <stdio.h>

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

void merge(int array[], int a1[], int a2[], int start)
{
    int size = (sizeof(a1) + sizeof(a2)) / sizeof(a1[0]);

    int i, k = 0, j = 0;
    for (i = start; i < size; i++)
    {
        if (j > size / 2 || (k <= size / 2 && a1[k] < a2[j]))
        {
            array[i] = a1[k];
            k++;
        }
        else
        {
            array[i] = a2[j];
            j++;
        }
    }
}

void mergeSort(int arr[], int size)
{
    int isSorted = 1, i;
    int arr1[size], arr2[size];

    while (isSorted)
    {
        isSorted = 0;
        i = 0;

        while (arr[i] <= arr[i + 1])
        {
            arr1[i] = arr[i];
            i++;
        }

        i++;

        while (arr[i] <= arr[i + 1])
        {
            arr2[i] = arr[i];
            i++;
        }
    }
}

int main()
{
    int data[] = {9, 5, 1, 4, 3};
    int size = sizeof(data) / sizeof(data[0]);
    mergeSort(data, size);
    // insertionSort(data, size);
    printf("Sorted array in ascending order:\n");
    printArray(data, size);
}
