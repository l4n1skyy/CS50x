#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Get change owed from user in decimal format and change it to integer format
    int change_owed;
    do
    {
        change_owed = round(get_float("Change owed: ") * 100);
    }
    while (change_owed < 0);
    int coins = 0;

    // Get amount of quarters
    while (change_owed > 24)
    {
        change_owed = change_owed - 25;
        coins++;
    }
    // Get amount of dimes
    while (change_owed > 9)
    {
        change_owed = change_owed - 10;
        coins++;
    }
    // Get amount of nickels
    while (change_owed > 4)
    {
        change_owed = change_owed - 5;
        coins++;
    }
    // Get amount of pennies
    while (change_owed > 0)
    {
        change_owed = change_owed - 1;
        coins++;
    }
    // Print number of coins needed
    printf("%i\n", coins);
}
