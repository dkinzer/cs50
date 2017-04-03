/**
 * vigerere.c
 *
 * David Kinzer
 * dtkinzer+cs50@gmail.com
 *
 * This program encrypts user input using a vigenere cypher.
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
void caesar_encrypt(char p, int k)
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

    // Fail is non alphabetical password
    string password = argv[1];
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(password[i]))
        {
            printf("Error: expected password to be alphabetical but '%s' given.", password);
            return 1;
        }
    }

    string message = GetString();

    // Track each letter to sync password key
    int alpha_count = 0;
    int password_length = strlen(password);

    for (int i = 0; i < strlen(message); i++)
    {
        // Ignore if not alpha
        if (!isalpha(message[i]))
        {
            printf("%c", message[i]);
            continue;
        }

        // Get key and normalize it
        char key = password[alpha_count % password_length];
        int k = isupper(key) ? key - 'A': key - 'a';

        // Encrypt each alpha character
        caesar_encrypt(message[i], k);

        // Next alpha index
        alpha_count++;
    }

    printf("\n");
    return 0;
}
