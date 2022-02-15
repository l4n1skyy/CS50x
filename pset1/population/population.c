#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get starting population value
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // get ending population value
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (start_size > end_size);

    // counts and prints number of years
    int n = start_size;
    int year = 0;
    while (n < end_size)
    {
        n = n + n / 3 - n / 4;
        year++;
        //printf("n = %i\n", n); // to see how much it increases per yr
    }
    printf("Years: %i\n", year);
}
