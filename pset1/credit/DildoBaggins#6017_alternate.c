//AMEX - 15 digits - 34,37
//MasterCard - 16 digits - 51,52,53,54,55
//VISA - 13 or 16 digits - 4

#include <stdio.h>
#include <math.h>
#include <cs50.h>

int get_digits(long n);
int luhn(long n);

int main(void)
{
    long cc;

    cc = get_long("Enter Credit Card Number: ");

    int digits = get_digits(cc);

    if (cc < 0)
    {
        printf("INVALID\n");
    }
    else if (digits != 13 && digits != 15 && digits != 16)
    {
        printf("INVALID\n");
    }
    else if (digits == 15)
    {
        int initial = cc / (pow(10, 13));

        if (initial == 34 || initial == 37)
        {
            int check = luhn(cc);

            if (check == 1)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (digits == 16)
    {
        int initial = cc / (pow(10, 14));

        if (initial == 51 || initial == 52 || initial == 53 || initial == 54 || initial == 55)
        {
            int check = luhn(cc);

            if (check == 1)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (initial / 10 == 4)
        {
            int check = luhn(cc);

            if (check == 1)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (digits == 13)
    {
        int initial = cc / (pow(10, 12));

        if (initial == 4)
        {
            int check = luhn(cc);

            if (check == 1)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

int get_digits(long n)
{
    int count = 0;

    if (n == 0)
    {
        count = 1;
    }

    while (n != 0)
    {
        n /= 10;
        count++;
    }

    return count;
}

int luhn(long n)
{
    int rem;
    int sum = 0;
    long temp = n;
    do
    {
        temp /= 10;
        rem = temp % 10;
        rem *= 2;
        temp /= 10;

        if (rem > 9)
        {
            sum += (rem % 10) + (rem / 10);
        }
        else
        {
            sum += rem;
        }
    }
    while (temp > 0);

    int rem_2;
    int sum_2 = 0;

    do
    {
        rem_2 = n % 10;
        n /= 100;
        sum_2 += rem_2;
    }
    while (n > 0);

    int check;

    if ((sum + sum_2) % 10 == 0)
    {
        check = 1;
    }
    else
    {
        check = 0;
    }

    return check;
}
