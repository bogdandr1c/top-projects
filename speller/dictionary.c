// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int counter = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to obtain its hash value
    int hash_v = hash(word);

    // Search the hash table at the location specified by the word's hash value
    node *ptr = table[hash_v];

    while (ptr != NULL)
    {
        // Return true if the word is found
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        else
        {
            // increment ptr
            ptr = ptr->next;
        }
    }

    // Return false otherwise
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // No need to improve since it will always return a value for 0 to 25;
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // remove garbage values from table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dict_f = fopen(dictionary, "r");
    if (dict_f == NULL)
    {
        printf("Error!\n");
        return 1;
    }
    // Read each word in the file
    // I need a buffer to store words
    // While loop!
    char word_buffer[LENGTH];

    while (fscanf(dict_f, "%s", word_buffer) != EOF)
    {
        // First create a new node (word)
        node *new_w = malloc(sizeof(node));
        if (new_w == NULL)
        {
            printf("Error!\n");
            return false;
        }

        int hash_w = hash(word_buffer);

        // Add each word to the hash table (i can use strcpy)
        strcpy(new_w->word, word_buffer);
        new_w->next = table[hash_w];
        table[hash_w] = new_w;
        counter++;
    }

    // Close the dictionary file
    fclose(dict_f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO (i can do it in previous function since it already goes through every word)
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr1 = table[i];
        node *ptr2 = table[i];

        while (ptr2 != NULL)
        {
            ptr2 = ptr2->next;
            free(ptr1);
            ptr1 = ptr2;
        }
    }
    return true;
}
