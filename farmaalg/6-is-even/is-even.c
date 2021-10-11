#include <stdio.h>

int main()
{
    int input;

    while (input != 0)
    {
        printf("Enter a value: ");
        scanf("%d", &input);
        if (input)
            input % 2 == 0 ? printf("even\n") : printf("odd\n");
    }

    return 0;
}