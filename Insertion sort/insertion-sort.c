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
    // size *
    for (int step = 1; step < size; step++) // 2
    {
        int key = array[step]; // 2
        int j = step - 1;      // 2

        // size / 2
        while (key < array[j] && j >= 0) // 4
        {
            array[j + 1] = array[j]; // 3
            --j;                     // 1
        }

        array[j + 1] = key; // 2
    }
}

// 2 + size * (6 + (size/2 * 8)) = 2 + 6 * size + 4 * size² => O(N²)

int main()
{
    int data[] = {9, 5, 1, 4, 3};
    int size = sizeof(data) / sizeof(data[0]);
    insertionSort(data, size);
    printf("Sorted array in ascending order:\n");
    printArray(data, size);
}
