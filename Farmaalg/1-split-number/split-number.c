#include <stdio.h>

int main()
{
    float input, fraction;
    int divider;

    printf("\nValue for the operation: ");
    scanf("%f", &input);

    divider = (int)input;
    fraction = input - divider;

    printf("Integer part: %d\n", divider);
    printf("Fractionary part: %f\n", fraction);
    return 0;
}