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

#include "dictionary.h"

// create struct node
typedef struct node
{
    struct node* next[27];
    bool isword;
} node;

// declare amount_of_words here so it is usable in both load and size
unsigned int amount_of_words = 0;

// declare parent node (most upper node)
node* parent;

// prototype
void freetrie(node* parent);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int char_num;
    int index = 0;
    node* current_node = parent;
    
    while (word[index])
    {
        // check for apostrophe
        if (word[index] == '\'')
        {
            // set character number
            char_num = 26;
        }
        // set to lower character and set char_num
        else
        {
            char_num = tolower(word[index]) - 'a';
        }
        
        // check if node is available
        if (current_node->next[char_num] != NULL)
        {
            // set the next node
            current_node = current_node->next[char_num];
            
            // set next word index
            index++;
        }
        // otherwise word is not in dictionary
        else
        {
            return false;
        }
    }
    
    // check if word is in dictionary
    if (current_node->isword == true)
    {
        return true;
    }
    
    // word wasn't in dictionary
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 * Dictionary is loaded into memory using a trie structure.
 */
bool load(const char* dictionary)
{
    // keep count of words
    amount_of_words = 0;
    // variable to save the trie node to go to
    int char_num;
    // save character from dictionary
    char character;
    
    // open the given dictionary
    FILE* dict = fopen(dictionary, "r");
    // check if opened
    if (dict == NULL)
    {
        // file could not be opened
        printf("Could not open dictionary.\n");
        return false;
    }
    
    // create the parent trie node, use calloc to prevent isword being true
    parent = calloc(1, sizeof(node));
    
    // set start node
    node* current_node = parent;
    
    // iterate over dictionary
    while ((character = fgetc(dict)) != EOF)
    {
        // check for end of line
        if (character == '\n')
        {
            // set isword boolean to true
            current_node->isword = true;
            
            // keep count of words
            amount_of_words++;
            
            // reset current_node to the parent node
            current_node = parent;
        }
        else
        {
            // check for an apostrophe
            if (character == '\'')
            {
                // set char_num to last index
                char_num = 26;
            }
            // set correct character number
            else
            {
                // there are no uppercase chars in the dictionary
                char_num = character - 'a';
            }
        
            // if node is not available yet, create it
            if (current_node->next[char_num] == NULL)
            {
                // allocate new node
                current_node->next[char_num] = calloc(1, sizeof(node));
                current_node = current_node->next[char_num];
            }
            
            // node must already be there
            else
            {
                current_node = current_node->next[char_num];
   	    	}
        }
    }
    
    // close dictionary
    fclose(dict);
    
    // no errors
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 * amount_of_words is calculated in load, this function just returns the value
 */
unsigned int size(void)
{
    // returns 0 if dictionary is not loaded, else returns amount of words
    return amount_of_words; 
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // call freetrie to free all the nodes
    freetrie(parent);
    
    // unload succesful
    return true;
}

/** 
 * function to free the trie
 * this function keeps calling itself when a node is not empty
 * to make sure that every subsequent node gets freed before it is lost
 **/
void freetrie(node* input_node)
{
    // free all 27 nodes
    for(int i = 0; i < 27; i++)
    {
        // check if node is not empty
        if (input_node->next[i] != NULL)
        {
            // free every node in this unempty node
            freetrie(input_node->next[i]);
        }
    }
    // free original node
    free(input_node);
    
    // exit the function
    return;
}