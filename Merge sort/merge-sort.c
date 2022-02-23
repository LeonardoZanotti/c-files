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

void merge(int *a, int l, int m, int r)
{
    int i, j, k;
    int *aux;

    aux = (int *)malloc(sizeof(int) * r + 1);

    for (i = m + 1; i > l; i--)
        aux[i - 1] = a[i - 1];
    for (j = m; j < r; j++)
        aux[r + m - j] = a[j + 1];

    for (k = l; k <= r; k++)
    {
        if (aux[j] < aux[i])
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

int main()
{
    int data[] = {9, 5, 1, 4, 3};
    int size = sizeof(data) / sizeof(data[0]);
    insertionSort(data, size);
    printf("Sorted array in ascending order:\n");
    printArray(data, size);
}
