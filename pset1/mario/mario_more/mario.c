#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get height from user
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // for the current row, do the following.
    // Once that is done, do the same for the next row.
    for (int n = 1; n <= height; n++)
    {
        // print the first set of spaces which sets the unique shape of the first set of hashes
        for (int z = height - n; z > 0; z--)
        {
            printf(" ");
        }
        // print the first set of hashes
        for (int H = n; H > 0; H--)
        {
            printf("#");
        }
        // print the space in between
        printf("  ");
        // print the second set of hashes
        for (int H = n; H > 0; H--)
        {
            printf("#");
        }
        // print a newline at the end of the row
        printf("\n");
    }
}
