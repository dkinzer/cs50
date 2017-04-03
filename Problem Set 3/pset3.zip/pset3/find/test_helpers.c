/**
 * test_helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Test the helper functions implemented in helpers.c
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"
#include "helpers.c"


void test_sort(void)
{
    int array1[] = {3, 2, 1};

    sort(array1, 3);

    int expected = 1;
    int actual = array1[0];

    if (actual != expected)
    {
        printf("Failed sort test1: expected %d, found %d", expected, actual);
    }

    expected = 3;
    actual = array1[2];

    if (actual != expected)
    {
        printf("Failed sort test2: expected %d, found %d", expected, actual);
    }

    expected = 2;
    actual = array1[1];

    if (actual != expected)
    {
        printf("Failed sort test3 last: expected %d, found %d", expected, actual);
    }


    int array2[] = {1};
    sort(array2, 1);

    expected = 1;
    actual = array2[0];

    if (actual != expected)
    {
        printf("Failed sort test4 last: expected %d, found %d", expected, actual);
    }

    printf("PASSED sort tests!\n");
}


void test_find()
{
    // Find element array of 1
    int array1[] = {1};

    sort(array1, 1);


    if (!search(1, array1, 1))
    {
        printf("Failed find tes1: expected to find 1.");
    }

    if (search(2, array1, 1))
    {
        printf("Failed find test2: expected to not find 2.");
    }

    // Find elements in array of 2
    int array2[] = {1, 2};
    if (!search(1, array2, 2))
    {
        printf("Failed find tes3: expected to find 1.");
    }

    if (!search(2, array2, 2))
    {
        printf("Failed find test4: expected to find 2.");
    }

    if (search(3, array2, 2))
    {
        printf("Failed find test5: expected to not find 3.");
    }

    // Find elements in array of 3
    int array3[] = {1, 2, 3};
    if (!search(1, array3, 3))
    {
        printf("Failed find tes6: expected to find 1.");
    }

    if (!search(2, array3, 3))
    {
        printf("Failed find test7: expected to find 2.");
    }

    if (!search(3, array3, 3))
    {
        printf("Failed find test8: expected to find 3.");
    }

    if (search(4, array3, 3))
    {
        printf("Failed find test9: expected not to find 4.");
    }

    // Find elements in array of 4
    int array4[] = {1, 2, 3, 4};
    if (!search(1, array4, 4))
    {
        printf("Failed find tes10: expected to find 1.");
    }

    if (!search(2, array4, 4))
    {
        printf("Failed find test11: expected to find 2.");
    }

    if (!search(3, array4, 4))
    {
        printf("Failed find test12: expected to find 3.");
    }

    if (!search(4, array4, 4))
    {
        printf("Failed find test13: expected to find 4.");
    }

    if (search(5, array4, 4))
    {
        printf("Failed find test13: expected not to find 5.");
    }

    printf("PASSED search tests!\n");
}


int main(void)
{
    test_sort();
    test_find();

    return 0;
}




