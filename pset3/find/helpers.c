/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1)
    {
        return false;
    }
    
    int first = values[0];
    int last = values[n - 1];
    int middle = (first + last) / 2;
    
    while (first <= last)
    {
        printf("%d, %d, %d\n", first, middle, last);
        if (middle == value)
        {
            return true;
        }
        else if (middle < value)
        {
            first = middle + 1;
        }
        else
        {
            last = middle - 1;
        }
 
        middle = (first + last) / 2;
    }
    return false;
}

/**
 * Sorts array of n values using bubble sort.
 */
void sort(int values[], int n)
{

    for(int i = 0; i < n - 1; i++)
    {
        bool noswap = true;
        for (int j = 0; j < n - 1; j++)
        {
            if (values[j] > values[j + 1])
            {
                int temp = values[j + 1];
                values[j + 1] = values[j];
                values[j] = temp;
                noswap = false;
            }
            
        }
        if (noswap == true)
        {
            break;
        }
    }
    return;
}
