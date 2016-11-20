/************************************************
 * initials.c
 * 
 * Fulltime Programmeren 1
 * Meir Noordermeer
 * 11341335
 * 
 * Gets name from the user and prints out the initials in uppercase.
 * 
 * Demonstrates looping through an array.
 ************************************************/

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    // gets name from user
    string name = GetString();
    int charcount = 0;
    char Initial;
    
    // check if name[0] is alphabetic
    if (!isalpha(name[0]))
    {
        // loop till name[charcount] is alphabetic
        do
        {
            charcount++;
        } while (!isalpha(name[charcount]));
        
        // print initial
        Initial = toupper(name[charcount]);
        printf("%c", Initial);
        charcount++;
    }
    
    else
    {
        // print initial
        Initial = toupper(name[charcount]);
        printf("%c", Initial);
        charcount++;
    }
    
    // loop through input
    for (; charcount < strlen(name); charcount++)
    {
        // check if char is alphabetic
        if (!isalpha(name[charcount]))
        {
            // up charcount as long as there are spaces
            do
            {
                charcount++;
            } while (!isalpha(name[charcount]) && charcount < strlen(name));
            
            // make sure no spaces get printed after initials
            if (isalpha(name[charcount]))
            {
                // print initial
                Initial = toupper(name[charcount]);
                printf("%c", Initial);
            }
        }
    }
    
    // prints a new line
    printf("\n");
    
    // no errors
    return 0;
}