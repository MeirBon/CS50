/************************************************
 * crack.c
 * 
 * Fulltime Programmeren 1
 * Meir Noordermeer
 * 11341335
 * 
 * Compares the hash created by crypt until it finds the program.
 ************************************************/

#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

// set max password lenth
char PASSW_LENGTH[8];
// set starting character
char *START_KEY = " ";

void bruteforce(int index, char *used_salt, char *password);

int main(int argc, char *argv[])
{
    // create array for comparing
    char current_word[9];
    
    // check for command-line argument
    if (argc != 2) 
    {
        // warn user
        printf("You didn't give any command-line argument.\n");
        return 1;
    }
    
    // store hash that needs cracking
    char *password = argv[1]; 
    
    // set slt array
    char slt[2];
    // copy first 2 characters of password to slt
    strncpy(slt, password, 2);
    // copy these characters to the salt variable
    char *salt = (char *) slt;
    
    // open dictionary file
    FILE* dictfile = fopen("/usr/share/dict/words", "r");
    // check if file is available
    if (dictfile == NULL) 
    {
        // warn user
        printf("Unable to open dictionary.\n");
        // give error code 1
        return 1;
    }
    
    // loop through file
    while (fscanf(dictfile, "%s\n", current_word) != EOF)
    {
        // create hash
        char* attempt = crypt(current_word, salt);
        
        // compare password and hash
        if (strcmp(password, attempt) == 0)
        {
            // print password if found
            printf("Password: %s\n", current_word);
            // close dictionary
            fclose(dictfile);
            // no errors
            exit(1);
        }
    }
    
    // download online dictionary
    system("wget -t 4 --output-document=1000000.txt 'https://raw.githubusercontent.com/danielmiessler/SecLists/master/Passwords/10_million_password_list_top_1000000.txt' "); 

    // open dictionary file
    FILE* dictpass = fopen("1000000.txt", "r");
    // check if file is available
    if (dictpass == NULL)
    {
        // warn user
        printf("Unable to open dictionary.\n");
        // give error code 1
        return 1;
    }
    
    // loop through file
    while (fscanf(dictpass, "%s\n", current_word) != EOF)
    {
        // create hash
        char* attempt = crypt(current_word, salt);
        
        // compare password and hash
        if (strcmp(password, attempt) == 0)
        {
            // print password if found
            printf("Password: %s\n", current_word);
            // close dictionary
            fclose(dictpass);
            // stop program
            exit(1);
        }
    }
    
    // use bruteforce to test all possible passwords (max length 8)
    for(int i = 0; i < 8; i++)
    {
        bruteforce(i, salt, password);
    }
}

void bruteforce(int index, char *used_salt, char *password)
{
    // loop through all possible characters
    for(int j = 32; j < 127; j++)
    {
        // assign char[index] to the used character
        PASSW_LENGTH[index] = (char) j;
        // assign new character to START_KEY for use in crypt
        START_KEY = (char *) PASSW_LENGTH;
        
        // store generated crypt has in variable attempt
        string attempt = (char *) crypt(START_KEY, used_salt);
        
        // compare hashes
        if (strcmp(attempt, password) == 0)
        {
            // if true, print password
            printf("Password: %s\n", START_KEY);
            // stop program
            exit(1);
        }
        
        /* 
        * before character[index] gets changed to another
        * letter, check if it is the first character
        * if not, call the function again, decrease index by 1
        * keep calling the function until index is the first character again
        */
        
        if (index > 0)
        {
            bruteforce(index - 1, used_salt, password);
        }
    }
}

