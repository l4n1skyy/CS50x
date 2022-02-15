#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Number: ");
    long long number = GetLongLong();
    // credit card numbers should have a few digits
    bool valid = number > 100000;
    char *type = "INVALID";
    int checksum = 0;
    int digits = 0;
    int firstTwo = 0;
    long long num2 = number;
    // compute checksum
    while (valid && num2)
    {
        if (100 > num2 && num2 >= 10)
        {
            firstTwo = num2;
        }
        digits++;
        if (digits % 2)
        {
            checksum += num2 % 10;
        }
        else
        {
            checksum += 2 * (num2 % 5) + (num2 % 10) / 5;
        }
        num2 /= 10;
    }
    if (checksum % 10)
    {
        valid = false;
    }
    if (valid && digits == 15 && (firstTwo == 34 || firstTwo == 37))
    {
        type = "AMEX";
    }
    if (valid && digits == 16 && firstTwo >= 51 && firstTwo <= 55)
    {
        type = "MASTERCARD";
    }
    if (valid && (digits == 13 || digits == 16) && firstTwo / 10 == 4)
    {
        type = "VISA";
    }
    printf("%s\n", type);
    return 0;
}
