/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // initiliaze starting values
    int rangeupper = n - 1;
    int rangelower = 0;
    
    /*  
    * check if value is in first place
    * do this here instead of in the loop
    * to prevent checking this every time
    */
    if (values[0] == value)
    {
        return true;
    }
    
    // loop till found
    do
    {
        int midpoint = (rangelower + rangeupper) / 2;
        // compare values
        if (values[midpoint] == value) 
        {
            // value is in list
            return true;
        }
        // search left side
        else if (values[midpoint] > value) 
        {
            // set new upper limit
            rangeupper = midpoint - 1;
        }
            
        // search right side
        else if (values[midpoint] < value) 
        {
            // set new lower limit
            rangelower = midpoint + 1;
        }
        
    // while there still is something to search
    } while (rangeupper >= rangelower);
    
    // needle not found
    return false;
}

/**
 * Sorts array of n values.
 * Using the selection sort algorithm.
 */
void sort(int values[], int n)
{
    // initiliaze all variables
    int temp;
    int minvalue;
    
    // loop through unsorted array
    for (int i = 0; i < n; i++)
    {
        // initial smallest value
        minvalue = i;
        
        // check whole array
        for (int j = i + 1; j < n; j++)
        {
            // check if new value is smaller
            if (values[minvalue] > values[j])
            {
                // set location of new smallest value
                minvalue = j;
            }
        }
        
        // swap values
        temp = values[minvalue];
        values[minvalue] = values[i];
        values[i] = temp;
    }
}