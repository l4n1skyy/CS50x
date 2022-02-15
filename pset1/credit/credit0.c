#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool checksum(long n);
bool print_type(long n);

int main(void)
{
    long credit_no = get_long("Number: ");

    // check credit_no against Luhn's algorithm
    if (!checksum(credit_no))
    {
        printf("INVALID\n");
        return 0;
    }
    else if (!print_type(credit_no))
    {
        printf("INVALID\n");
    }
}

bool checksum(long n)
{
    int z;

    // 1. find x, digit in every other place value, i from right
    // 2. multiply x by 2 and sum digits into z
    for (int i = 1; i < 16; i = i + 2)
    {
        // 1.
        long curr_place = n % (long) pow(10, i + 1);
        long prev_place = n % (long) pow(10, i);
        long get_digit = (curr_place - prev_place) / (long) pow(10, i);

        int x = get_digit;

        // 2.
        int y = x * 2;
        int digit_tens = (y % 100 - y % 10) / 10;
        int digit_ones = y % 10;

        // sum digits with z
        z = z + digit_tens + digit_ones;
    }

    // add z with every other digit from left
    for (int i = 2; i < 15; i = i + 2)
    {
        long curr_place = n % (long) pow(10, i + 1);
        long prev_place = n % (long) pow(10, i);
        long get_digit = (curr_place - prev_place) / (long) pow(10, i);

        int x = get_digit;

        // sum digits with z
        z = z + x;
    }

    // because of the special case in second loop
    z = z + n % 10;


    // check if last digit is 0
    if (z % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool print_type(long n)
{
    int length = 1;
    double x = n;

    while (x / 10 > 1)
    {
        x = x / 10;
        length++;
    }

    int y = x * 10;

    if (length == 15 && (y == 34 || y == 37))
    {
        printf("AMEX\n");
        return true;
    }
    else if ((length == 16) && ((y == 51 || y == 52) || (y == 53 || y == 54) || (y == 55)))
    {
        printf("MASTERCARD\n");
        return true;
    }
    else if ((length == 13 || length == 16) && (y / 10 == 4))
    {
        printf("VISA\n");
        return true;
    }
    else
    {
        return false;
    }
}
