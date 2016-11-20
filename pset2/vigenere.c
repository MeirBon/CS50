/************************************************
 * vigenere.c
 *
 * Fulltime Programmeren 1
 * Meir Noordermeer
 * 11341335
 *
 * Encrypts a given string using a given keyword (using vigenere).
 * 
 * Demonstrates use of looping through arrays/strings.
 ************************************************/
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// argc contains argument count, argv contains name of program
int main(int argc, string argv[])
{
    // stores message
    string message = NULL;
    // stores the keyword
    string keyword = argv[1];
    // counter for the keyword
    int counter = 0;
    // track count in keyword
    int charcount = 0;
    
    // check for 2 command-line arguments
    if (argc < 2 || argc > 2)
    {
        // inform user
        printf("Please enter a single alphabetical command-line argument\n");
        // return error code 1
        return 1;
    }
    
    
    
    // check if keyword is alpha
    for (int i = 0; i < strlen(keyword); i++)
    {
        if (!isalpha(keyword[i]))
        {
            // inform user
            printf("You did not enter an alphabetical command-line argument\n");
            
            // return error code 1
            return 1;
        }
    }
    
    do 
    {
        // get user message
        message = GetString(); 
    } while (message == '\0'); 

     // loop through the given input and convert
    for (int j = 0; (j < strlen(message)); j++)
    {
        // check if char is alphabetic
        if (isalpha(message[j]))
        {
            // set counter to modulo keylength (to reset counter if needed)
            counter = charcount % strlen(keyword);
            
            // preserve lowercase characters
            if (islower(message[j]))
            {
                // lowercase char keyword
                if (islower(keyword[counter]))
                {
                    message[j] = ((message[j] - 'a' + keyword[counter] - 97) % 26) + 97;
                }
                
                // uppercase char keyword
                else
                {
                    message[j] = ((message[j] - 'a' + keyword[counter] - 65) % 26) + 97;
                }
            }
            
            // preserve uppercase chararacters
            if (isupper(message[j]))
            {
                if (islower(keyword[counter]))
                {
                    message[j] = ((message[j] - 'A' + keyword[counter] - 97) % 26) + 65;
                }
                else
                {
                    message[j] = ((message[j] - 'A' + keyword[counter] - 65) % 26) + 65;
                }
            }
            
            // print encrypted message
            printf("%c", message[j]);
            
            // track count of keyword
            charcount++;
        }
        else
        {   
            // print encrypted message
            printf("%c", message[j]);
        }
    }
    // print a new line
    printf("\n");
    
    // no errors
    return 0;
}
