#include <stdio.h>
#include <string.h>

#define SIZE 1000

void insertionSort(int array[], int size, char text[50])
{
    int comparations = 0, swaps = 0;
    for (int step = 0; step < size; step++)
    {
        int key = array[step];
        int j = step - 1;

        comparations += 2;
        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            --j;
            comparations++;
        }

        swaps++;
        array[j + 1] = key;
    }
    printf("Insertion sort (%s)\nComparations: %d\nSwaps: %d\n\n", text, comparations, swaps);
}

void bubbleSort(int array[], int size, char text[50])
{
    int i, j, temp, comparations = 0, swaps = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swaps++;
            }
            comparations += 2;
        }
        comparations++;
    }
    printf("Bubble sort (%s)\nComparations: %d\nSwaps: %d\n\n", text, comparations, swaps);
}

void generate_data(int data[SIZE], char order[4])
{
    int i;
    if (strcmp(order, "asc") == 0)
    {
        for (i = 0; i < SIZE; i++)
            data[i] = i;
    }
    else if (strcmp(order, "desc") == 0)
    {
        for (i = 0; i < SIZE; i++)
            data[SIZE - 1 - i] = i;
    }
}

int main()
{
    int data[SIZE];

    generate_data(data, "desc");

    insertionSort(data, SIZE, "Worst case");

    generate_data(data, "desc");

    bubbleSort(data, SIZE, "Worst case");

    generate_data(data, "asc");

    insertionSort(data, SIZE, "Best case");

    generate_data(data, "asc");

    bubbleSort(data, SIZE, "Best case");
}