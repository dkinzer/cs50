/**
 * greedy.c
 *
 * David Kinzer
 * dtkinzer+cs50@gmail.com
 *
 * Determines the amount of change given some user input.
 */
#include <stdio.h>
#include <cs50.h>

/**
 * Coverts a floating point reprentation of money into number of cents.
 */
int convertToPennies(float money)
{
    int cents = 0;
    // we need a tolarance as a placeholder for precision
    float penny_tolerance = 0.009;
    float dime_tolerance = 0.09;
    float dollar_tolerance = 0.9;
    
    float dollar = 1.0;
    float dime = 0.10;
    float penny = 0.01;
    
    int cents_dollar = 100;
    int cents_dime = 10;
    int cent = 1;
    
    while (money > penny_tolerance)
    {
        if (money > dollar_tolerance)
        {
            cents = cents + cents_dollar;
            money = money - dollar;
            continue;
        }
        if (money > dime_tolerance)
        {
            cents = cents + cents_dime;
            money = money - dime;
            continue;
        }
        cents = cents + cent;
        money = money - penny;
    }
    
    return cents;
}

/**
 * Calculate the amount of change givent an amount of pennies.
 * Uses a greedy algorithm.
 */
int getChange(int cents)
{
    int change = 0;
    int quarter = 25;
    int dime = 10;
    int nickle = 5;
    int penny = 1;
    
    while (cents > 0)
    {
        // exhausting currency form large to small makes us greedy
        if (cents >= quarter)
        {
            change++;
            cents = cents - quarter;
            continue;
        }
        if (cents >= dime)
        {
            change++;
            cents = cents - dime;
            continue;
        }
        if (cents >= nickle)
        {
            change++;
            cents = cents - nickle;
            continue;
        }
        
        change++;
        cents = cents - penny;
    }
    
    return change;
    
}

int main(void)
{
    float money;
    
    do
    {
        printf("O hai! How much change is owed?\n");
        money = GetFloat();
    }
    while (money < 0);
    
    int cents = convertToPennies(money);
    int change = getChange(cents);
  
    
    printf("%i\n", change);
}
