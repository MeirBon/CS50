/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 * Mèir Noordermeer
 *
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

// set hashtable size (2^17)
#define HASHTABLE_SIZE 131072

// define struct node
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
} node;

// create hash table
node* hash_table[HASHTABLE_SIZE];

// declare amount_of_words here so it is usable in both load and size
unsigned int amount_of_words;

// prototype hash function
int hash_it(char* needs_hashing);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // store length of word
    int length_word = strlen(word);
    
    // create check char array
    char check_word[length_word];
    
    // need to make sure everything is lowercase
    for (int i = 0; i < length_word; i++)
    {
        // convert to lowercase
        check_word[i] = tolower(word[i]);
    }
    check_word[length_word] = '\0';
    
    // create hash value
    int bucket = hash_it(check_word);
    
    // set current_bucket to the first node of the bucket
    node* current_bucket = hash_table[bucket];
    
    // check until the end of the linked list
    while (current_bucket != NULL)
    {
        // compare words
        if (!strcmp(current_bucket->word, check_word))
        {
            // word is in dictionary
            return true;
        }
        
        // set next checkable word
        current_bucket = current_bucket->next;
    }
    
    // word was not in dictionary
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 * Using a hash function to create buckets in which we store the words.
 */
bool load(const char* dictionary)
{
    // reset amount of words
    amount_of_words = 0;
    
    // create variable for word
    char insert_word[LENGTH + 1];
    
    // open dictionary
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }
    
    // keep reading till EOF
    while (fscanf(dict, "%s", insert_word) != EOF)
    {
        // calloc a node for each new word, use calloc to prevent garbage values
        node* new_node = calloc(1, sizeof(node));
        
        // check if calloc was succesful
        if (new_node == NULL)
        {
            printf("Could not calloc new_node.\n");
            return false;
        }
        
        // copy word to node
        strcpy(new_node->word, insert_word);
        
        // generate bucket to point to
        int bucket = hash_it(new_node->word);
        
        // if bucket is empty, insert allocated node
        if (hash_table[bucket] == NULL)
        {
            hash_table[bucket] = new_node;
        }
        
        // if bucket is not empty, add word to linked list
        else
        {
            new_node->next = hash_table[bucket];
            hash_table[bucket] = new_node;
        }
        
        // keep count of amount of words in dictionary
        amount_of_words++;
    }
    
    // close dictionary
    fclose(dict);
    
    // load succesful
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 * Amount of words is caluclated in load, size just returns the value.
 */
unsigned int size(void)
{
    // returns amount_of_words which was calculated in load
    return amount_of_words;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // loop through all buckets
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // asign current_bucket to current position in hash_table
        node* current_bucket = hash_table[i];
        
        // while bucket is not empty, go in the bucket
        while (current_bucket != NULL)
        {
            // preserve linked list
            node* temp = current_bucket;
            // set next node to be checked
            current_bucket = current_bucket->next;
            // free node
            free(temp);
        }
    }
    
    // set amount_of_words to 0 again
    amount_of_words = 0;
    
    // unload succesfull
    return true;
}

/**
 * Hash function by the husband of reddit user delipity:
 * https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
 * 
 * This function loops through every char of the word. It shifts the bits to left by 2.
 * This is the same as multiplying by 4, but shifting is more efficient.
 * Then this value get multiplied by the power of the ascii value of the char.
 */
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(needs_hashing); i < n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}