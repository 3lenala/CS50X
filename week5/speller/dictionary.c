// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// N is the number of buckets in the hash table
const unsigned int N = ('z' * LENGTH * (LENGTH - 1) / 2) >> 3;
// the maximum value that the hash table can give for any alphabetical input

int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int length_word = strlen(word);
    char lower_word[length_word];
    to_lower_word(word, lower_word);
    // the hash table includes the words present in the dictionary
    // which are all lowercase
    int index = hash(lower_word);
    node *dictionary = table[index];
    while (dictionary != NULL)
    {
        // we compare the value we are pointing at with the word
        if (strcmp(dictionary->word, lower_word) == 0)
        {
            return true; // if we found the word
        }
        // go to the next value
        dictionary = dictionary->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int word_hash = 0;
    int length_word = strlen(word);
    for (int i = 0; i < length_word; i++)
    {
        // sums over each letter in the word
        word_hash += tolower((unsigned char) word[i]) * (i ^ length_word);
        word_hash ^= (word_hash >> 3);
        // shifts it three places
        // 3 was found to be the number that gives the most optimal results timewise
        // for the given texts
    }

    return (word_hash) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "Error opening the dictionary\n");
        // open error./speller texts/lalaland.txt
        return false;
    }
    char *word_in_dict = malloc(LENGTH * sizeof(char));
    while (fscanf(dict, "%45s", word_in_dict) == 1)
    {
        if (!load_word(word_in_dict)) // if the word can't be loaded
        {
            free(word_in_dict); // return error
            fclose(dict);
            return false;
        }
        word_count++;
    }
    free(word_in_dict);
    fclose(dict);
    return true; // everything went as expected
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) // for every bucket in the hash table
    {
        node *ptr = table[i];
        while (ptr != NULL) // unload its linked list
        {
            table[i] = ptr->next;
            free(ptr);
            ptr = table[i];
        }
    }
    return true;
}

bool load_word(const char *word)
{
    // load a single word into the hash table
    int index = hash(word);
    node *new_node = malloc(sizeof(node)); // where the word will be located
    if (new_node == NULL)
    {
        // there is no memory for a node
        return false;
    }
    strcpy(new_node->word, word); // copy the word
    new_node->next = table[index];
    table[index] = new_node;
    return true; // everything went as expected
}

void to_lower_word(const char *word, char *lower_word) // returns word in lowercase
{
    for (int i = 0, max_index = strlen(word) + 1; i < max_index; i++)
    {
        lower_word[i] = tolower((unsigned char) word[i]);
    }
}
