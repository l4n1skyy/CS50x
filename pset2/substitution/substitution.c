#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int argc_error(int argc);
void key_upper(string argv[], char key[], int keylen);
int key_error(char key[], int keylen);
void substitution_cipher(char key[], string plaintext, int txtlen);

int main(int argc, string argv[])
{
    // Check if there is any argc error.
    int error1 = argc_error(argc);
    if (error1 != 0)
    {
        return 1;
    }

    // Change key to uppercase
    int keylen = strlen(argv[1]);
    char key[keylen];
    key_upper(argv, key, keylen);

    // Check if there is any key error.
    int error2 = key_error(key, keylen);
    if (error2 != 0)
    {
        return 1;
    }

    // Get plaintext
    string plaintext = get_string("plaintext: ");
    int txtlen = strlen(plaintext);

    // Print ciphertext
    printf("ciphertext: ");
    substitution_cipher(key, plaintext, txtlen);

    printf("\n");
}

int argc_error(int argc)
{
    // If argc is not 2
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    return 0;
}

void key_upper(string argv[], char key[], int keylen)
{
    // Change each letter to uppercase and store in in an array, key.
    for (int n = 0; n < keylen; n++)
    {
        if (isalpha(argv[1][n]))
        {
            key[n] = toupper(argv[1][n]);
        }
        else
        {
            key[n] = argv[1][n];
        }
    }
}

int key_error(char key[], int keylen)
{
    // If user typed anything other than 26 chars
    if (keylen != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // If user typed anything other than letters
    for (int n = 0; n < keylen; n++)
    {
        if (key[n] < 'A' || key[n] > 'Z')
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // If user typed duplicate characters
    for (int n2 = 0; n2 < keylen; n2++)
    {
        for (int n3 = n2 + 1; n3 < keylen; n3++)
        {
            if (key[n2] == key[n3])
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    return 0;
}

void substitution_cipher(char key[], string plaintext, int txtlen)
{
    // for each character in the text
    for (int n = 0; n < txtlen; n++)
    {
        // if the character is uppercase, print the corresponding key
        if (isupper(plaintext[n]))
        {
            int i = plaintext[n] - 'A';
            printf("%c", key[i]);
        }
        // if the character is lowercase, print the corresponding key in lowercase
        else if (islower(plaintext[n]))
        {
            int i = plaintext[n] - 'a';
            printf("%c", tolower(key[i]));
        }
        // if it's not a letter, just print if out.
        else
        {
            printf("%c", plaintext[n]);
        }
    }
}
