#include <stdio.h>
#include <string.h>

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

void generate_data(int data[1000], char order[4])
{
    int i;
    if (strcmp(order, 'asc') == 0)
    {
        for (i = 0; i < 1000; i++)
            data[i] = i;
    }
    else if (strcmp(order, 'desc') == 0)
    {
        for (i = 0; i < 1000; i++)
            data[999 - i] = i;
    }
}

int main()
{
    int data[1000];

    generate_data(data, 'asc');
    // generate_data(data, 'desc');

    int size = sizeof(data) / sizeof(data[0]);

    insertionSort(data, size);

    printf("Sorted array in ascending order:\n");
}
