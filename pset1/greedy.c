/**
 * greedy.c
 * Petrus M. Noordermeer
 *
 * Calculates the minimum amount of coins to give back as change.
 **/
 
#include <cs50.h>
#include <math.h>
#include <stdio.h>

int GetCoins(int typecoin, int money);

int main(void)
{
    // Get the amount of change from the user, make sure the amount of change is positive
    float c = 0;
    
    do
    {
    printf("How much change is owed: ");
    c = GetFloat();
    } while (c < 0);
    
    // Rounding the float value and converting it to an integer
    c = c * 100;
    int change = 0;
    change = round(c);
    
    // Calculate amount of quarters
    int aquarter = GetCoins(25, change);
    change -= (aquarter * 25);
    
    // Calculate amount of dimes
    int adime = GetCoins(10, change);
    change -= (adime * 10);
    
    // Calculate amount of nickels
    int anickel = GetCoins(5, change);
    change -= (anickel * 5);
    
    // Calculate amount of pennies
    int apenny = GetCoins(1, change);
    change -= (apenny * 1);
    
    // Adds up amount of each coin and prints total
    int total = aquarter + adime + anickel + apenny;
    printf("%d\n", total);
}

// Repeating function for finding the amount of coins in change.
int GetCoins(int typecoin, int money)
{
    int amountofcoin = 0;
    if (typecoin == 1)
    {
       while (money > (typecoin - 1))
        {
            money = money - typecoin;
            amountofcoin = amountofcoin + 1;
        }
    }
    else
    {
        while (money > (typecoin - 1))
        {
            money = money - typecoin;
            amountofcoin = amountofcoin + 1;
        }
    }
    return amountofcoin;
}