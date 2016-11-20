/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // checks if usage is correct
    if (argc != 2 && argc != 3)
    {
        // if not, inform user of usage
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // store and convert first argument of user as an integer
    int n = atoi(argv[1]);

    // if there are 3 command-line arguments, use third as seed to create a specific set of numbers
    if (argc == 3)
    {
        // generate numbers
        srand48((long int) atoi(argv[2]));
    }
    
    // else create a random set of numbers
    else
    {
        // generate random set of numbers (using current time as seed)
        srand48((long int) time(NULL));
    }

    // loop through numbers
    for (int i = 0; i < n; i++)
    {
        // print numbers
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}