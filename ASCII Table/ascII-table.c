#include <stdio.h>

int main()
{
    // First row -> hex label
    printf("\t");
    for (int j = 0; j <= 15; j++)
    {
        if (j == 15)
        {
            printf("%x \n", j);
            continue;
        }
        printf("%x \t", j);
    }

    // ASCII values
    for (int i = 0; i < 256; i++)
    {
        int integer = (i < 32) ? 32 : i;
        char breakLine = ' ';

        if (i % 16 == 15)
        {
            breakLine = '\n';
        }

        if (i % 16 == 0)
        {
            printf("%x \t %c", (i / 16), (char)integer);
            continue;
        }

        printf("\t %c %c", (char)integer, breakLine);
    }
    return 0;
}