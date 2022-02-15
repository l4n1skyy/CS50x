#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int letter_counter(string text, int len);
int word_counter(string text, int len);
int sentence_counter(string text, int len);
float compute_grade(int letters, int words, int sentences, int len);


int main(void)
{
    // get text from user
    string text = get_string("Text: ");
    int len = strlen(text);

    // get num of letters, words and sentences
    int letters = letter_counter(text, len);
    int words = word_counter(text, len);
    int sentences = sentence_counter(text, len);

    // grade is received in float form and rounded up to int
    int grade = round(compute_grade(letters, words, sentences, len));

    // print out grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);

    }

}


int letter_counter(string text, int len)
{
    int letters = 0;
    // for each character in text, check if its a letter, and if it's a letter,
    // +1 to the letter counter.
    for (int n = 0; n < len; n++)
    {
        if
        // to check if it's a letter
        (('a' <= text[n] && text[n] <= 'z') ||
            ('A' <= text[n] && text[n] <= 'Z'))
        {
            letters++;
        }
    }
    return letters;
}

int word_counter(string text, int len)
{
    // word counter starts at 1 because, spaces + 1 = num of words.
    int words = 1;
    // for each character in text, if it is a space, +1 to word counter.
    for (int n = 0; n < len; n++)
    {
        if (text[n] == ' ')
        {
            words++;
        }
    }
    return words;
}

int sentence_counter(string text, int len)
{
    int sentences = 0;
    // for each character in text, if it is !, ?, or ., +1 to sentence counter.
    for (int n = 0; n < len; n++)
    {
        if (text[n] == '!' || text[n] == '?' || text[n] == '.')
        {
            sentences++;
        }
    }
    return sentences;
}

float compute_grade(int letters, int words, int sentences, int len)
{
    // Coleman-Liau index
    float L = letters * 100.0 / words;
    float S = sentences * 100.0 / words ;
    float grade = 0.0588 * L - 0.296 * S - 15.8;
    return grade;
}
