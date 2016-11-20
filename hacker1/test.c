#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
        long long user_ccinput = 0;
    do
    {
        printf("What is your credit card number? ");
        user_ccinput = GetLongLong();
    } while (user_ccinput < 0);
    
    int total_uneven = 0;
    int total_even = 0;
    string cc = user_ccinput
    
    for (i = 0; i <= strlen(cc); i++)
    {
        //Count other digits
        int addother[i] = (user_ccinput % 10);
        user_ccinput = round(user_ccinput / 10);
        
        //Count every other digit
        intaddevother = (user_ccinput % 10) *2);
        user_ccinput = round(user_ccinput / 10);
    }
    
    int total = total_uneven + total_even;
    printf("%d\n", total);
}