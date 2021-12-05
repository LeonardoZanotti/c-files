#include <stdio.h>
#include <string.h>

void insertionSort(int array[], int size, char text[50])
{
    int comparations = 0, swaps = 0;
    for (int step = 1; step < size; step++)
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
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
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

void generate_data(int data[1000], char order[4])
{
    int i;
    if (strcmp(order, "asc") == 0)
    {
        for (i = 0; i < 1000; i++)
            data[i] = i;
    }
    else if (strcmp(order, "desc") == 0)
    {
        for (i = 0; i < 1000; i++)
            data[999 - i] = i;
    }
}

int main()
{
    int data[1000];
    int size = sizeof(data) / sizeof(1000);

    generate_data(data, "desc");

    insertionSort(data, size, "Worst case");

    generate_data(data, "desc");

    bubbleSort(data, size, "Worst case");

    generate_data(data, "asc");

    insertionSort(data, size, "Best case");

    generate_data(data, "asc");

    bubbleSort(data, size, "Best case");
}