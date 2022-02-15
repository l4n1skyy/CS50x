#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // ask user for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // loop for whole thing
    for (int n = 1; n <= height; n++)
    {
        // loop for spaces in each row
        for (int n2 = 1; n2 <= height - n; n2++)
        {
            printf(" ");
        }

        // loop for hashes in each row
        for (int n3 = 0; n3 < n; n3++)
        {
            printf("#");
        }
        printf("\n");
    }
}
