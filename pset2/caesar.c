/************************************************
 * caesar.c
 * 
 * Fulltime Programmeren 1
 * Meir Noordermeer
 * 11341335
 * 
 * Encrypts message with a key that the user inputs.
 * 
 * Demonstrate looping through an array and 'encrypting' the characters.
 ************************************************/
 
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
// argc contains argument count, argv contains name of program
int main(int argc, string argv[])
{
    // stores user key
    int iKeyNumber = 0;
    
    // stores the message
    string message = "";
    
    // check command-line argument
    if (argc < 2 || atoi(argv[1]) < 0)
    {
        // give warning
        printf("Try again; Give a single command line argument\n");
        
        // return error
        return 1;
    }
    
    else
    {
        // convert key to integer
        iKeyNumber = atoi(argv[1]);
        
        // get user input
        message = GetString();
    }
        
    // loop through input and convert using the given key
    for (int i = 0, j = strlen(message); i < j; i++)
    {
        // convert lowercase characters
        if (isalpha(message[i]))
        {
            if (islower(message[i]))
            {
                message[i] = (message[i] - 97 + iKeyNumber) % 26 + 97;
            }
            // convert uppercase characters
            else if (isupper(message[i]))
            {
                message[i] = (message[i] - 65 + iKeyNumber) % 26 + 65;
            }
        }
        
        // convert other signs
        else
        {
            message[i] = message[i];
        }
        // prrint encrypted message
        printf("%c", message[i]);
    }
    // prints a new line
    printf("\n");
    
    // no errors
    return 0;
}
