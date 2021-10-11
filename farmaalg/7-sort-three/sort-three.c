#include <stdio.h>

int main()
{
    int array[4];
    int input, k = 0;

    for (int i = 1; i < 4; i++)
    {
        printf("Inform the %d° value: ", i);
        scanf("%d", &input);

        while (input > array[k])
        {
            k++;
        }

        for (int i = 3; i >= k; i--)
        {
            array[i + 1] = array[i];
        }

        array[k] = input;
    }

    printf("Sorted:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", array[i]);
    }
    return 0;
}