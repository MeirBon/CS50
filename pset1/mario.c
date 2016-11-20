/**
* mario.c
* Petrus. M. Noordermeer
*
* Produces a half-pyramid like the ones in the ending of each level in Super Mario Brothers.
**/ 

#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int height = 0;
    // Get height from user
    do
    {
        printf("Height:");
        height = GetInt();
    } while (height < 0 || height > 23);

    // This for loop handles the count of rows to print. Both inner loops take the value of the outer loop to count correctly.
    for(int i = 0; i < height; i++) 
    {
        // This for loop prints the correct amount of spaces on each row
        for(int j=0; j < height-i-1; j++)
        {
            printf("%s", " ");
        }
        // This for loop prints the correct amount of hashes on each row, adding + 2 as we start the pyramid with 2 blocks at the top.
            for(int k=0; k < i+2; k++)
            {
                printf("#");
            }
            printf("\n");
    }
    return 0;
}
