/**
 * memory.c
 *
 * Print memory value and skips location if not accessible.
 */

#include <stdio.h>
#include <signal.h>

int address = 1;

/**
 * Handles segmentation fault.
 */
void segv_handler(int id)
{
    address++;
}


int  main (int argc, char* argv[])
{
    signal( SIGSEGV, segv_handler);

    while(1)
    {
        printf("%d: %s\n", address, argv[address]);
        address++;
    }

    return 1;
}
