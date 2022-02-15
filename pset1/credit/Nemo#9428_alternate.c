#include <stdio.h>
#include <cs50.h>

void dieInvalid(void);
int getLength(long cc);
int luhn(long cc);
string getCCType(long cc, int length);

int main(void)
{
    long cc;

    // Get the credit card number
    do
    {
        cc =  get_long("Number: ");
    }
    while (!cc); // keep asking on rejection

    // We got here, so there is an actual number in the var, test it now.

    int length = getLength(cc);

    if (length < 13 || length > 16 || length == 14)
    {
        dieInvalid();
    }
    else
    {
        // it's at least in the format of a real cc

        int result = luhn(cc);
        if (result % 10 == 0)
        {
            string ccType = getCCType(cc, length);
            printf("%s\n", ccType);


        }
        else
        {
            dieInvalid();
        }
    }
}

int getLength(long cc)
{
    int length = 0;
    while (cc)
    {
        cc /= 10;
        length++;
    }
    return length;
}

int luhn(long cc)
{
    bool odd = true;
    int digit;
    int nonMultiplySum = 0;
    int multiplySum = 0;
    int result;

    while (cc)
    {

        digit = cc % 10; // the remainder is our number
        cc /= 10; // strip the last digit at every loop

        if (odd)
        {
            nonMultiplySum += digit;
            odd = false; // switch between odd and even
        }
        else
        {
            int newDigit = digit * 2;
            if (newDigit / 10) // if the new number is more than 10, we must add together those 2 digits
            {
                multiplySum += newDigit % 10 + newDigit / 10;
            }
            else
            {
                multiplySum += newDigit;
            }


            odd = true;
        }

    }
    result = multiplySum + nonMultiplySum;
    return result;
}

void dieInvalid(void)
{
    printf("INVALID\n");
}

string getCCType(long cc, int length)
{

    for (int i = length - 1; i >= 2; i--)
    {
        cc /= 10; // reducing the cc nubmer to 2 digits
    }

    if (length == 15) // Amex?
    {
        if (cc == 34 || cc == 37)
        {
            return "AMEX";
        }

    }
    else if (length == 16) // visa or mastercard?
    {
        if (cc == 51 || cc == 52 || cc == 53 || cc == 54 || cc == 55)
        {
            return "MASTERCARD";
        }
        else if (cc / 10 == 4)
        {
            return "VISA";
        }

    }
    else // visa? gotta be 13 since we checked before
    {
        if (cc / 10 == 4)
        {
            return "VISA";
        }

    }
    return "INVALID";
}
