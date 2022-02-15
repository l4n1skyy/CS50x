#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_error(int argc, string argv[]);
void caesar_cipher(string p, int k, int len);

int main(int argc, string argv[])
{
    // Check for error in command line arguments. If there is an error, return 1.
    int error = check_error(argc, argv);
    if (error != 0)
    {
        return 1;
    }

    // Convert key inputted by user into integer and store it in variable k
    int k = atoi(argv[1]);

    // Get plaintext from user and calculate length of it.
    string plaintext = get_string("Plaintext: ");
    int len = strlen(plaintext);

    // Print ciphertext: and let caesar_cipher function print the ciphertext
    printf("Ciphertext: ");
    caesar_cipher(plaintext, k, len);
}


void caesar_cipher(string p, int k, int len)
{
    char ciphertext[len];
    for (int n = 0; n < len; n++)
    {
        // Turn the char into an index in between of 0-25. Add the key to the
        // index and then modulo it by 26 to make sure it does not exceed 25.
        // Then add it by Aa so it converts back to a char.
        if (isupper(p[n]))
        {
            ciphertext[n] = (((p[n] - 65) + k) % 26) + 65;
        }
        else if (islower(p[n]))
        {
            ciphertext[n] = (((p[n] - 97) + k) % 26) + 97;
        }
        else
        {
            ciphertext[n] = p[n];
        }
        printf("%c", ciphertext[n]);
    }
    printf("\n");
}


int check_error(int argc, string argv[])
{
    // If user typed in anything other than 2 arguments in command line
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // if user typed anything other than digits
    else
    {
        for (int n = 0, len = strlen(argv[1]); n < len; n++)
        {
            if (argv[1][n] < '0' || argv[1][n] > '9')
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    // if both conditions above are false, return 0
    return 0;
}
