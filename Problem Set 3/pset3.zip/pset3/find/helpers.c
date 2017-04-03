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
 *
 * Implements the search function using a binary search algorithm.
 */
bool search(int value, int values[], int n)
{
    if (value < 0)
    {
        return false;
    }

    // Binary search needs a sorted list 
    sort(values, n);

    // Track middle and boundries
    int size = n;
    int start = 0;
    int end  = n - 1;
    int middle = end/2;


    while (start <= end)
    {
        // Deal with edge case
        if (size == 2)
        {
            return values[start] == value || values[end] == value;
        }

        if (values[middle] == value)
        {
            return true;
        }

        // Prepare search left side
        if (values[middle] > value)
        {
            end = middle - 1;
        }
        // Prepare search right side
        else
        {
            start = middle + 1;
        }

        // Determine new array middle and size
        middle = (end - start)/2;
        size = end - start + 1;

    }

    return false;
}

/**
 * Sorts array of n values using the insertion algorithm.
 */
void sort(int values[], int n)
{
    // Iterate over each element starting at second position
    for (int i = 1; i < n; i ++)
    {
        // Track element to sort and open position
        int element = values[i];
        int j = i;

        // If value element is less than value left
        while (j > 0 && element < values[j - 1])
        {
            // Shift value left  to right
            values[j] = values[j - 1];

            // Update open position
            j = j - 1;
        }
    
        // Place element in open position
        values[j] = element;
    }
    return;
}

