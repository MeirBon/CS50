/************************************************
 * water.c
 * Made by: P.M. Noordermeer
 * 
 * Asks user how many minutes they shower and calculates the equivalent in bottles of water.
 ************************************************/
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Defines minutes as an integer and sets value to 0
    int minutes = 0;
    
    // do, while loop to get a positive integer from the user
    do
    {
    printf("minutes: ");
    minutes = GetInt();
    } while (minutes <= 0);
    
    printf("%i\n", minutes);
    
    // Calculate and print the amount of bottles the user uses per shower
    int bottles = minutes * 12;
    printf("bottles: %i\n", bottles);
}