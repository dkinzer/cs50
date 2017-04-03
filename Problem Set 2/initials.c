/**
 * initials.c
 *
 * David Kinzer
 * dtkinzer+cs50@gmail.com
 *
 * This program prompts a user for their name and then outputs their initials in uppercase.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(void)
{
    string name = GetString();

    for (int i = 0; i < strlen(name); i++) {
        // Skip if non letter
        if (!isalpha(name[i]))
        {
            continue;
        }
        // Skip if not first letter and previous not space
        if (i != 0 && name[i - 1] != ' ')
        {
            continue;
        }
        printf("%c", toupper(name[i]));
    }

    printf("\n");
    return 0;
}
