/**
 * mario.c
 *
 * David Kinzer
 * dtkinzer+cs50@gmail.com
 *
 * Prints an ASCII art version of a Mario Brother's game half-pyramid given som height for the pyramid. 
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
   
    do
    {
       printf("height: ");
       height = GetInt();
    }
    while(height < 0 || height > 23 );
    
    for (int row = 2; row <= height + 1; row++)
    {
        // the # and white space complant each other and vary with height
        printf("%.*s", height + 1 - row, "                         ");
        printf("%.*s\n", row, "#########################");
    }
}
