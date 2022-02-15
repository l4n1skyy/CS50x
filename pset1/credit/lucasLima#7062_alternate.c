#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

//function created to: reverse the string entered. It makes the operations easier to deal with
string str_reverse(string str, short number_length)
{
    for (short i = 0; i < number_length / 2; i++)
    {
        char aux = str[i];
        str[i] = str[number_length - 1 - i];
        str[number_length - 1 - i] = aux;
    }

    return str;

}

//function created to check if the credit card number is valid or not.
//It checks if the string has the minimum length and if it has only digits;
int is_creditcard_number(string number, short len)
{
    if (len < 13)
    {
        return 0;
    }

    for (short i = 0; i < len; i++)
    {
        if (!isdigit(number[i]))
        {
            return 0;
        }
    }

    return 1;

}

//function created to convert char into an integer between 0 - 9
short ctosi(char digit)
{
    return - (57 % (short) digit - 9);
}

//function created to check if the Lunh's algorithm valid the credit card
short is_valid_creditcard(string number, short number_length)
{
    //reverse the string
    number = str_reverse(number, number_length);

    short to_duplicate = 0;
    short notto_duplicate = 0;

    //check if the algarism have to be duplicated or not.
    //if yes, duplicate it, split this new number and then add its algarisms to
    //to_duplicate. If not, just add the number to notto_duplicate
    for (short i = 0; i < number_length; i++)
    {
        if (i % 2 == 1)
        {

            short digittimes2 = 2 * ctosi(number[i]);

            if (digittimes2 >= 10)
            {
                to_duplicate += digittimes2 % 10 + 1;
            }
            else
            {
                to_duplicate += digittimes2;
            }

        }
        else
        {
            notto_duplicate += ctosi(number[i]);
        }
    }

    //add the sums above and return the modulo 10 of the total value

    short checksum = notto_duplicate + to_duplicate;

    return checksum % 10;
}


//Do the magic
int main(void)
{
    string number = get_string("Number: ");
    short number_length = strlen(number);

    //store the value of the validator function and
    //luhn's algorithm validator function inside variables then apply the logic
    int is_valid = is_valid_creditcard(number, number_length);
    int is_credit = is_creditcard_number(number, number_length);

    if (!is_credit || is_valid)
    {
        printf("INVALID\n");
        return 0;
    }

    //check if the first and second digits of the credit card numbers are congruent
    //with the companies 2 firsts digits then apply the logic.
    if (is_valid == 0)
    {
        short first_digit = ctosi(number[number_length - 1]);
        short second_digit = ctosi(number[number_length - 2]);

        if (first_digit == 5 && !(second_digit < 1 || second_digit > 5))
        {

            printf("MASTERCARD\n");
        }
        else if (first_digit == 4)
        {
            printf("VISA\n");
        }
        else if (first_digit == 3 && (second_digit == 4 || second_digit == 7))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    return 0;
}
