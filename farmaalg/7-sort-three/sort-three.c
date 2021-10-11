#include <stdio.h>

int main()
{
    int array[3];
    int i;

    for (i = 0; i < 3; i++)
    {
        printf("Inform the %d° value: ", i + 1);
        scanf("%d", &array[i]);
    }

    for (i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (array[i] > array[j])
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    printf("Sorted:\n");
    for (i = 0; i < 3; i++)
    {
        printf("%d\n", array[i]);
    }
    return 0;
}