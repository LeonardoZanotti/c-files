#include <stdio.h>

int main()
{
    int bigger, input;

    printf("Inform the 1° value: ");
    scanf("%d", &bigger);

    for (int i = 2; i < 11; i++)
    {
        printf("Inform the %d° value: ", i);
        scanf("%d", &input);
        if (input > bigger)
            bigger = input;
    }

    printf("The bigger value is: %d\n", bigger);

    return 0;
}