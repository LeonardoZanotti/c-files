#include <stdio.h>

int main()
{
    for (int i = 1; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d \n", i);
        }
        else
        {
            printf("\t %d \n", i);
        }
    }
    return 0;
}