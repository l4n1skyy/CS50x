// make credit using only / and % 
// this only calculates checksum
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long cc = get_long("Number: ");

    // get length
    long x = cc;
    int len = 0;
    do
    {
        x = x / 10;
        len++;
    } 
    while (x > 0);
    
    // calculate checksum
    int sum = cc % 10;
    int place_value = 0;
    long y = cc;
    long digit;

    do
    {
        // get digit and place value
        y = y / 10;
        digit = y % 10;
        place_value++;

        // if place value is even
        if (place_value % 2 == 0)
        {
            sum = sum + digit;
        }

        // if place value is odd
        else
        {
            sum = sum + (digit * 2 / 10 % 10) + (digit * 2 % 10);
        }
    } 
    while (place_value < len);
    
    printf("sum: %i\n", sum);
}
