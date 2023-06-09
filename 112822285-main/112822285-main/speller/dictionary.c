// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26; //26*26

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int n = hash(word); // to decide which order in pointer array for comparison
    node *checkptr = table[n]; // make a new pointer point to the same location as table[n]


    while (checkptr != NULL) //when the table[n] has linked list
    {
        if (strcasecmp(word, checkptr -> word) == 0) //compare two strings case insensitively, check -> word is the first node's word
        {
            return true;
        }
        checkptr = checkptr -> next; //change the pointer position to the next node
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    int i = 0;
    while (i <= N) //make all pointers in the array initialized to null
    {
        table[i] = NULL;
        i++;
    }

    FILE *dicfile = fopen(dictionary, "r"); //open the dictionary file to load in the hash table
    if (dicfile == NULL) //if it cannot open successfully
    {
        return false;
    }
    char wordstring[LENGTH + 1]; //create an char array to store file's words, the index should be the longest length a word would have
    node *n = NULL;

    while (fscanf(dicfile, "%s", wordstring) != EOF)
    {

        n = malloc(sizeof(node)); //point to dynamic created memory(before that it is a null pointer, point nothing)
        if (n == NULL) //if it is allocated memory unsuccessfully
        {
            printf("unable to open file");
            unload();
            return false;
        }
        strcpy(n -> word, wordstring); //copy strings(left from) to string right(to)
        n -> next = table[hash(n -> word)]; // make the new insert node point to the first node
        table[hash(wordstring)] = n; //make table[] pointer to new insert node


    }

    fclose(dicfile); //remember to close file
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int totalnumber = 0;
    for (int n = 0; n < N; n++)
    {
        node *checkptr = table[n];
        while (checkptr != NULL) //when node is not null
        {
            totalnumber++;
            checkptr = checkptr -> next;
        }
    }
    return totalnumber;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int n = 0; n < N; n++)
    {
        node *curser = table[n]; //create two node pointer pointed to the first node
        node *tmp = table[n];
        while (curser != NULL) //when node is not null
        {
            curser = curser -> next; //move the curser pointer to the next node
            free(tmp); //free the front node(because table[n] = malloc(...), free the memory tmp is pointing)
            tmp = curser; //make tmp point to the next node
        }
    }

    return true;
}
