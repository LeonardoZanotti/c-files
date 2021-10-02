#include <stdio.h>

int main()
{
    int index = 0, tabIndex = 0;
    for (int i = 1; i < 16; i++)
    {
        if (index == tabIndex)
        {
            printf("%d \n", i);
            index++;
            tabIndex = 0;
        }
        else
        {
            printf("%d \t", i);
            tabIndex++;
        }
    }
    return 0;
}