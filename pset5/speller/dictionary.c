// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1531;

// Hash table
node *table[N];

// Sum of words in dictionary
int numwords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash word to obtain hash value
    int bucket = hash(word);

    // access linked list at that index in the hash table
    node *cursor = table[bucket];

    // traverse linked list, looking for the word
    // keep moving cursor until you get to NULL, checking each node for the word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';

    int sum = 0;
    int i = 0;
    while ((int)toupper(word[i]) != 0)
    {
        sum += (int)toupper(word[i]);
        i++;
    }
    return sum % 1531; // just a random prime number I chose
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {

        // Create new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Increase number of words
        numwords++;

        // Hash word to obtain a hash value
        int bucket = hash(word);

        // Insert node into hash table at that location
        if (table[bucket] != NULL)
        {
            n->next = table[bucket];
            strcpy(n->word, word);
        }
        else
        {
            n->next = NULL;
            strcpy(n->word, word);
        }
        table[bucket] = n;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return numwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = NULL;

        while (cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }

    }

    return true;
}
