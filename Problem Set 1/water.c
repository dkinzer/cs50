/**
 * water.c
 *
 * David Kinzer
 * dtkinzer+cs50@gmail.com
 *
 * Determines and prints the number of water bottles per shower given a span of time in minutes. 
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("minutes: ");
    int minutes = GetInt();
    
    int bottles = (192 * minutes) / 16;
    printf("bottles: %i \n", bottles);
}
