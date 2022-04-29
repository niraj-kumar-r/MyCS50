#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int pyramid_height = 1;
    while (true)
    {
        pyramid_height = get_int("Height: ");

        if (pyramid_height >= 1 && pyramid_height <= 8)
        {
            break;
            // Will not break until condition met
        }
    }

    for (int i = 1; i <= pyramid_height; i++)
    {
        for (int j = 1; j <= pyramid_height - i; j++)
        {
            printf(" ");
            // initial space
        }

        for (int k = 1; k <= i; k++)
        {
            printf("#");
            // first tower
        }

        printf("  ");
        // space in between

        for (int k = 1; k <= i; k++)
        {
            printf("#");
            // second tower
        }

        printf("\n");
        // newline
    }
    // code goes brrrrr
}