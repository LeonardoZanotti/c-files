#include <stdio.h>

int main()
{
    for (int i = 2; i <= 100; i++)
    {
        int divisors = 0;
        for (int j = 2; j <= i; j++)
        {
            if (i % j == 0)
            {
                divisors++;
            }
        }
        if (divisors == 1)
        {
            printf("%d\n", i);
        }
    }
    return 0;
}