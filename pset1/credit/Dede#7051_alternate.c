#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdbool.h>

//prototype
long get_card_number(void);

int main(void)
{
    //this whole line is to get each number of the credit card one by one, from the end to the beginning
    long card_number = get_card_number();
    int first_number = card_number      % 10;
    int second_number = card_number     % 100 / 10;
    int third_number = card_number      % 1000 / 100;
    int fourth_number = card_number     % 10000 / 1000;
    int fifth_number = card_number      % 100000 / 10000;
    int sixth_number = card_number      % 1000000 / 100000;
    int seventh_number = card_number    % 10000000 / 1000000;
    int eighth_number = card_number     % 100000000 / 10000000;
    int nineth_number = card_number     % 1000000000 / 100000000;
    int tenth_number = card_number      % 10000000000 / 1000000000;
    int eleventh_number = card_number   % 100000000000 / 10000000000;
    int twelvth_number = card_number    % 1000000000000 / 100000000000;
    int thirteenth_number = card_number % 10000000000000 / 1000000000000 ;
    int fourteenth_number = card_number % 100000000000000 / 10000000000000 ;
    int fifteenth_number = card_number  % 1000000000000000 / 100000000000000 ;
    int sixteenth_number = card_number  % 10000000000000000 / 1000000000000000 ;

    //these lines were to multiply every second number by 2 and then add them together, the math here is the remainder from %10 and %100 , removed from each other and then add %10 again
    int multiply_1 = second_number * 2 ;
    int remainder_11 = multiply_1 % 10;
    int remainder_12 = multiply_1 % 100;
    int total_1 = (remainder_12 - remainder_11) / 10 + remainder_11;

    //do this for each and every multiplication
    int multiply_2 = fourth_number * 2 ;
    int remainder_21 = multiply_2 % 10;
    int remainder_22 = multiply_2 % 100;
    int total_2 = (remainder_22 - remainder_21) / 10 + remainder_21;

    //meaning that i'll do it a total of 8 times, if the credit card has by maximum a 16 digits
    int multiply_3 = sixth_number * 2 ;
    int remainder_31 = multiply_3 % 10;
    int remainder_32 = multiply_3 % 100;
    int total_3 = (remainder_32 - remainder_31) / 10 + remainder_31;

    int multiply_4 = eighth_number * 2 ;
    int remainder_41 = multiply_4 % 10;
    int remainder_42 = multiply_4 % 100;
    int total_4 = (remainder_42 - remainder_41) / 10 + remainder_41;


    int multiply_5 = tenth_number * 2 ;
    int remainder_51 = multiply_5 % 10;
    int remainder_52 = multiply_5 % 100;
    int total_5 = (remainder_52 - remainder_51) / 10 + remainder_51;

    int multiply_6 = twelvth_number * 2 ;
    int remainder_61 = multiply_6 % 10;
    int remainder_62 = multiply_6 % 100;
    int total_6 = (remainder_62 - remainder_61) / 10 + remainder_61;

    int multiply_7 = fourteenth_number * 2 ;
    int remainder_71 = multiply_7 % 10;
    int remainder_72 = multiply_7 % 100;
    int total_7 = (remainder_72 - remainder_71) / 10 + remainder_71;

    //ok done
    int multiply_8 = sixteenth_number * 2 ;
    int remainder_81 = multiply_8 % 10;
    int remainder_82 = multiply_8 % 100;
    int total_8 = (remainder_82 - remainder_81) / 10 + remainder_81;

    //add all the numbers that don't get multiplied
    int sum_of_singles = first_number + third_number + fifth_number + seventh_number + nineth_number + eleventh_number +
                         thirteenth_number + fifteenth_number;
    //add the numbers after multiplications
    int sum_of_multis = total_1 + total_2 + total_3 + total_4 + total_5 + total_6 + total_7 + total_8;
    int total_sum = sum_of_singles + sum_of_multis;
    //this one is to see if the credit passed the sumcheck by checking if the remainder of %10 is 0
    int zero_or_not = total_sum % 10;
    if (zero_or_not > 0)
    {
        printf("INVALID\n");
    }
    //to check if it's amex, after invalidating every card that doesn't pass the sumcheck
    else if (sixteenth_number == 0 && fifteenth_number == 3 && (fourteenth_number == 4 || fourteenth_number == 7))
    {
        printf("AMEX\n");
    }
    //to check if it's mastercard
    else if ((fifteenth_number == 1 || fifteenth_number == 2 || fifteenth_number == 3 || fifteenth_number == 4
              || fifteenth_number == 5) && sixteenth_number == 5)
    {
        printf("MASTERCARD\n");
    }
    //to check if it's visa
    else if ((sixteenth_number == 4) || (sixteenth_number == 0 && fifteenth_number == 0 && fourteenth_number == 0
                                         && thirteenth_number == 4))
    {

        printf("VISA\n");
    }
    //anything else should be considered for this problem to be invalid
    else
    {
        printf("INVALID\n");
    }
}


long get_card_number(void)
{
    long n;
    do
    {
        n = get_long("write down your credit card number : ");
    }
    while (n <= 0 || n > 9999999999999999);

    return n;
}

