#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

char ALPHABET[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};

int POINTS[] =
{
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3,
    10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};

int compute_score(string word);

int main(void)
{
    // get words from user
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // calculate score using custom function
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // print result
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

}

// custom function for calculating score of word
int compute_score(string word)
{
    int len = strlen(word);
    char characters[len];
    int score = 0;

    // Change each letter to uppercase and store in in an array, characters.
    for (int n = 0; n < len; n++)
    {
        characters[n] = toupper(word[n]);
    }

    // for each character, do the following
    for (int n2 = 0; n2 < len; n2++)
    {
        // for each alphabet,
        for (int n3 = 0; n3 < 26;)
        {
            // if the alphabet is not the same as the character,
            if (characters[n2] != ALPHABET[n3])
            {
                n3++;
            }
            // if the alphabet is the same as the character,
            else if (characters[n2] == ALPHABET[n3])
            {
                score += POINTS[n3];
                break;
            }
        }
    }
    return score;
}
