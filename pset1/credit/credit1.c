#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool checksum(long n);
void print_type(double n);

int main(void)
{
    long credit_no = get_long("Number: ");

    // check credit_no against Luhn's algorithm
    if (!checksum(credit_no))
    {
        printf("INVALID\n");
        return 0;
    }

    // check credit_no against card specifications
    print_type(credit_no);

}

bool checksum(long n)
{
    // total sum
    int z;

    for (int i = 0; i < 16; i++)
    {
        // 1. find x, digit in every place value, i
        long foll_place = n % (long) pow(10, i + 1);
        long curr_place = n % (long) pow(10, i);
        long get_digit = (foll_place - curr_place) / (long) pow(10, i);
        int x = get_digit;

        // if i is even and less than 15 (every other place value from left)
        // i = 0 is a special case
        if ((i % 2 == 0) && (i < 15 && i != 0))
        {
            z = z + x;
        }

        // if i is odd (every other place value from right)
        else if (i % 2 != 0)
        {
            // multiply x by 2 and sum digits into z
            int y = x * 2;
            int digit_tens = (y % 100 - y % 10) / 10;
            int digit_ones = y % 10;

            // sum digits with z
            z = z + digit_tens + digit_ones;
        }
    }

    // i = 0 (the special case in even)
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

void print_type(double n)
{
    // length = first 2 digits + divided away digits
    int length = 2;

    // divide away all the digits other than first 2
    while (n / 10 > 9)
    {
        n = n / 10;
        length++;
    }

    // integer with first 2 digits of n
    int y = n;

    // check card specifications and print
    if ((length == 15) && (y == 34 || y == 37))
    {
        printf("AMEX\n");
    }
    else if ((length == 16) && ((y == 51 || y == 52) || (y == 53 || y == 54) || (y == 55)))
    {
        printf("MASTERCARD\n");
    }

    // we only want to check the first digit, not the first 2 here
    else if ((length == 13 || length == 16) && (y / 10 == 4))
    {
        printf("VISA\n");
    }

    // if it doesn't fit specifications, print invalid
    else
    {
        printf("INVALID\n");
    }
}
