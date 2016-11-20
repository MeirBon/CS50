/************************************************
 * credit.c
 * P.M. Noordermeer
 * 
 * Validates credit card
 ************************************************/
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
 
// American Express numbers all start with 34 or 37             15-digit
// MasterCard numbers all start with 51, 52, 53, 54, or 55      16-digit 
// Visa numbers all start with 4                                13- and 16-digit 

int main(void)
{
    // Ask for credit card number
    long long user_ccinput = 0;
    do
    {
        printf("What is your credit card number? ");
        user_ccinput = GetLongLong();
    } while (user_ccinput < 0);
    
    int total_even = 0;
    int total_uneven = 0;
    int even_input = 0;
    
    while (user_ccinput > 0)
    {
        even_input = round(user_ccinput/10);
        total_uneven = total_uneven + (user_ccinput % 10);
        total_even = total_even + ((even_input % 10)* 2);
        user_ccinput = user_ccinput/10;
    }
    int total = total_uneven + total_even;
    printf("%i\n", total);
    printf("%i\n", total_uneven);
    printf("%i\n", total_even);
    
    // Check if credit card number is valid
    

}
/**n % 10 will get you the rightmost digit
(n / 10) % 10 will get you the next rightmost digit
(n / 100) % 10 will get you the next rightmost digit
(n / 1000) % 10 will get you the next rightmost digit
**/