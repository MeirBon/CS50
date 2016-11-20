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
#include <string.h>
#include <stdbool.h>

#include "dictionary.h"

// create struct node
typedef struct node
{
    struct node* next[27];
    bool isword;
} node;

// declare these variables here so they are usable in both load and size
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
    int i = 0;
    node* current_node = parent;
    
    while (word[i] != '\0')
    {
        // check for apostrophe
        if (word[i] == '\'')
        {
            // set character number
            char_num = 26;
        }
        // set to lower character and set char_num
        else
        {
            char_num = tolower(word[i]) - 'a';
        }
        
        // check if node is valid
        if (current_node->next[char_num] != NULL)
        {
            // set the next node
            current_node = current_node->next[char_num];
            // set next index
            i++;
        }
        // otherwise word is not in dictionary
        else
        {
            return false;
        }
    }
    
    // check what came out of the previous loop
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
    amount_of_words = 0;
    char current_word[LENGTH + 1];
    int length;
    int char_num;
    
    // open the given dictionary
    FILE* dict = fopen(dictionary, "r");
    // check if opened
    if (dict == NULL)
    {
        return false;
    }
    
    // create the parent trie node, use calloc to prevent isword being true
    parent = malloc(sizeof(node));
    
    node* current_node = NULL;
    
    // iterate over dictionary
    while (fscanf(dict, "%s\n", current_word) != EOF)
    {
        // (re)set node to the parent node
        current_node = parent;
        
        // save length of word
        length = strlen(current_word);
        
        // iterate over word
        for (int i = 0; i < length; i++)
        {
            // check for an apostrophe
            if (current_word[i] == '\''){
                // set char_num to last index
                char_num = 26;
            }
            
            // set correct character number
            else{
                // there are no uppercase chars in the dictionary
                char_num = (int) current_word[i] - 'a';
            }
            
            // if node is not available yet, create it
            if (current_node->next[char_num] == NULL){
                // allocate new node
                current_node->next[char_num] = malloc(sizeof(node));
                current_node = current_node->next[char_num];
            }
            
            // node must already be there
            else{
   				current_node = current_node->next[char_num];
   			}
        }
        
        // set isword boolean to true
        current_node->isword = true;
        
        // keep count of words
        amount_of_words += 1;
    }
    // close dictionary
    fclose(dict);
    
    // all went well
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // dictionary not loaded
    return amount_of_words; 
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // set the most upper node first
    node* current_node = parent;
    
    // call freetrie to free all the nodes
    freetrie(current_node);
    
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