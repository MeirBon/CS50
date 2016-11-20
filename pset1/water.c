/**
 * water.c
 *
 * Computer Science 50
 * Petrus. M. Noordermeer
 *
 * Calculates the amount of bottles of water used depending on the amount of minutes the user showers.
 **/
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks user for input value
    printf("How many minutes do you shower: ");
    int m = GetInt();
    
    // Calculate amount of bottles and prints them on the screen
    int b = m * 12;
    printf("You use %d bottles per shower", b);
}