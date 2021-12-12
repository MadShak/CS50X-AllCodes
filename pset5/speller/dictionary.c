// Implements a dictionary's functionality.
#include <strings.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

#include "dictionary.h"


// Represents a node in a hash table.
typedef struct node

{
    char word[LENGTH + 1];
    struct node *next;
}

node;

// Number of buckets in hash table.
unsigned int wordCounter;
unsigned int hashValue;
const unsigned int N = 26;

// Hash table.
node *table[N];

// Loads dict into memory, returning true if successful else false.
bool load(const char *dictionary)

{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)

    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)

    {
        node *n = malloc(sizeof(node));

// NULL malloc.
        if (n == NULL)

        {
            return false;
        }

// Pointer to next node and word itself
        strcpy(n->word, word);
        hashValue = hash(word);
        n->next = table[hashValue];
        table[hashValue] = n;
        wordCounter++;
    }

    fclose(file);

    return true;
}

// Hashes word to a number.
unsigned int hash(const char *word)

{
    unsigned long hash = 5381;
    int c;

    while ((c = toupper(*word++)))

    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % N;
}

unsigned int size(void)

{

    if (wordCounter > 0)

    {
        return wordCounter;
    }

    return 0;
}

// Returns true if word is in dictionary else false.
bool check(const char *word)

{
    hashValue = hash(word);
    node *cursor = table[hashValue];

    while (cursor != NULL)

    {
        if (strcasecmp(word, cursor->word) == 0)

        {
            return true;
        }

// Cursor->next.
        cursor = cursor->next;
    }

    return false;

}

// Unloads dictionary from memory, returning true if successful else false.
bool unload(void)

{
    for (int i = 0; i < N; i++)

    {
        node *cursor = table[i];

// Not NULL.
        while (cursor)

        {
            // Create temp
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free up temp
            free(tmp);
        }

// NULL.
        if (i == N - 1 && cursor == NULL)

        {
            return true;
        }
    }

    return false;
}