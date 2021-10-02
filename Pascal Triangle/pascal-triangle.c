#include <stdio.h>

int main()
{
    int value = 1;

    printf("%d \n", value);

    for (int l = 1; l <= 5; l++)
    {
        value = 1;

        printf("%d \t", value);

        for (int c = 1; c <= l; c++)
        {
            value = (value * (l - c + 1)) / c;
            printf("%d \t", value);
        }
        printf("\n");
    }

    return 0;
}