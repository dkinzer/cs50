/**
 * caesar.c
 *
 * David Kinzer
 * dtkinzer+cs50@gmail.com
 *
 * This program encrypts user input using a caesar cypher.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


/**
 * Encrypts the supplied char using k as a key.
 * This is a Ceasar's cipher encryption.
 */
void encrypt(char p, int k)
{
    char start = isupper(p) ? 'A': 'a';

    // Use start to normalize
    char c = ((p - start + k) % 26) + start;

    printf("%c", c);
}

int main(int c, char* argv[])
{
    if (c != 2)
    {
        printf("Error: expected 1 argument, found %d. \n", c - 1);
        return 1;
    }

    // Convert input key to interger
    int k = atoi(argv[1]);

    if (k == 0 && (argv[1][0] != '0' || strlen(argv[1]) == 0))
    {
        printf("Error: expected key to be numerical, but found \"%s\".\n", argv[1]);
        return 1;
    }

    if (k < 0)
    {
        printf("Error: expected key to be greater than 0, but %d given.\n", k);
        return 1;
    }

    string message = GetString();

    for (int i = 0; i < strlen(message); i++)
    {
        // Ignore if non alpha
        if (!isalpha(message[i]))
        {
            printf("%c", message[i]);
            continue;
        }

        encrypt(message[i], k);
    }

    printf("\n");
    return 0;
}
