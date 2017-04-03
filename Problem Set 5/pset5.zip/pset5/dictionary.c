/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"


const int ALPHABET_SIZE = 27;

// define trie node
typedef struct node
{
    bool is_word;
    struct node* children[ALPHABET_SIZE];
}
node;

// define a generic book
typedef struct book {
    node* root;

    int words;

    // for debugging
    double allocs;
    double frees;
}
book;


/**
 * Initializes the dictionary root node and returns a pointer to it.
 */
book* get_dictionary();

book* trie_dictionary = NULL; 

/**
 * Keep track of memory allocations.
 *
 * Used for debugging.
 */
void tally_allocs()
{
    book* d = get_dictionary();
    if (d == NULL)
    {
        return;
    }
    d->allocs++;
}


/**
 * Keep track of memor de-allocations.
 *
 * Used for debugging.
 */
void tally_frees()
{
    book* d = get_dictionary();
    if (d == NULL)
    {
        return;
    }
    d->frees++;
}

/**
 * Keep track of number of words in dictonary.
 */
void tally_words()
{
    book* d = get_dictionary();
    if (d == NULL)
    {
        return;
    }
    d->words++;
}


/**
 * Initializes a new trie node and returns a pointer to it.
 */
node* new_node()
{
    node* n = NULL;
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Error: failed trying to allocate new_node().");
        exit(1);
    }
    n->is_word = NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        n->children[i] = NULL;
    }

    tally_allocs();
    return n;
}

/**
 * Initializes a new book and returns a pointer to it.
 */
book* new_book()
{
    book* b = NULL;
    b = malloc(sizeof(book));
    if (b == NULL)
    {
        printf("Error: failed trying to allocate new_book().");
        exit(1);
    }
    b->words = 0;
    b->frees = 0;
    b->root = NULL;
    b->allocs = 1;

    return b;
}


/**
 * Initializes the dictionary root node and returns a pointer to it.
 */
book* get_dictionary()
{
    if (trie_dictionary == NULL)
    {
        trie_dictionary = new_book();
        trie_dictionary->root = new_node();
    }

    return trie_dictionary;
}

/**
 * Converts char to node child index.
 */
int to_position(char c)
{
    int position = 26;

    if (isalpha(c)) {
        position = tolower(c) - 97;
    }

    return position;
}

/**
 * Adds a word to a given trie_dictionary.
 */
bool add_word(book* dictionary, char* word)
{
    if (dictionary == NULL)
    {
        printf("Error: dictionary does not exist.");
        return false;
    }

    if (word == NULL || word[0] == '\0')
    {
        printf("Error: word cannot be empty.");
        return false;
    }

    node* current_node;
    current_node = dictionary->root;

    for (int i = 0; i < (LENGTH + 1); i++)
    {

        char c = word[i];

        // mark new word if char is terminator
        if (c == '\0') 
        {
            // or mark child node as new word.
            current_node->is_word = true;
            return true;
        }
        else
        {
            // create node ith child if does not exist
            int ith = to_position(word[i]);
            if (current_node->children[ith] == NULL)
            {
                current_node->children[ith] = new_node();
            }
            if (current_node->children[ith] == NULL)
            {
                printf("Error: NULL memory allocation.");
                return false;
            }
            current_node = current_node->children[ith];
        }
    }
    return true;
}

/**
 * Finds a word in the given trie_dictionary.
 */
bool find_word(book* dictionary, const char* word)
{
    node* current_node = dictionary->root;

    for (int i = 0; i < (LENGTH + 1); i++)
    {
        char c = word[i];

        // if word terminates return work check
        if (c == '\0') 
        {
            // or mark child node as new word.
            return current_node->is_word;
        }
        else
        {
            // word not possible if child is null
            int ith = to_position(word[i]);
            if (current_node->children[ith] == NULL)
            {
                return false;
            }
            current_node = current_node->children[ith];
        }
    }
    return false;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return find_word(get_dictionary(), word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    book* thisdic = get_dictionary();
    if (thisdic == NULL)
    {
        printf("Could not allocate memory for dictionary.");
        return false;
    }

    int index = 0;
    char word[LENGTH+1];

    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\''))
        {
            // append character to word
            word[index] = c;
            index++;
        }
        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';

            thisdic->words++;

            if (!add_word(thisdic, word))
            {
                return false;
            }

            // prepare for next word
            index = 0;
        }
    }

    // check whether there was an error
    if (ferror(fp))
    {
        fclose(fp);
        printf("Error reading %s.\n", dictionary);
        unload();
        return false;
    }

    // close text
    fclose(fp);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    book* b = get_dictionary();
    if (b == NULL)
    {
        return 0;
    }
    return b->words;
}

/**
 * Free up all the memory used by the children node and their progeny.
 */
node* free_progeny(node* parent)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (parent->children[i] !=  NULL) {
            free(free_progeny(parent->children[i]));
            tally_frees();
        }
        else {
           free(parent->children[i]);
           tally_frees();
        }
    }

    return parent;
}

/**
 * Free all the nodes of a dictinary.
 */
void free_dictionary(book* dictionary)
{
    if (trie_dictionary != NULL)
    {
        free(free_progeny(dictionary->root));
        tally_frees();
        free(trie_dictionary);
    }
    trie_dictionary = NULL;
}


/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    book* thisdic = get_dictionary();
    if (thisdic == NULL)
    {
        return false;
    }

    free_dictionary(thisdic);
    return true;
}

/**
 * Test transforming characters to indexes.
 */
void test_to_position(void)
{
    if (0 != to_position('a'))
    {
        printf("Error: expected to_position('a') == 0");
    }

    if (25 != to_position('z'))
    {
        printf("Error: expected to_position('z') == 25");
    }

    if (to_position('A') != to_position('a'))
    {
        printf("Error: expected to_position('A') == to_position('a')");
    }

    if (26 != to_position('\''))
    {
        printf("Error: expected to_position('\'') == 26");
    }

}

/**
 * Test adding words to a dictionary.
 */
void test_add_word(void)
{
    char test_word[6] = "hello";
    book* thisdic = get_dictionary(); 
    return;
    add_word(thisdic, test_word);

    int a = to_position('a');
    if (thisdic->root->children[a] != NULL)
    {
        printf("Error: expected node->children[a] to be null.");
    }

    int h = to_position('h');
    if (thisdic->root->children[h] == NULL)
    {
        printf("Error: expected node->children[h] not to be null.");
    }

    int e = to_position('e');
    int l = to_position('l');
    int o = to_position('o');

    if (!thisdic->root->children[h]->children[e]->children[l]->children[l]->children[o]->is_word)
    {
        printf("Error: expected 'hello' to be in the dictionary.");
    }
    free_dictionary(thisdic);
}


/**
 * Test freeing the progeny nodes of a dictionary.
 */
void test_free_progeny(void)
{
    book* thisdic = get_dictionary();

    if (thisdic == NULL)
    {
        printf("Error: thisdic should not be NULL\n");
    }

    thisdic->root->children[0] = new_node();
    thisdic->root->children[0]->children[0] = new_node();
    free_dictionary(thisdic);

    // If no segment fault, then we are good.
}

/**
 * Test freeing all the nodes of a dictionary.
 */
void test_free_dictionary(void)
{
    book* thisdic = get_dictionary();

    if (thisdic == NULL)
    {
        printf("Error: thisdic should not be NULL\n");
    }

    thisdic->root->children[0] = new_node();
    thisdic->root->children[0]->children[0] = new_node();
    free_dictionary(thisdic);
}

/**
 * Test finding a word in a dictionary.
 */
void test_find_word(void)
{
    book* thisdic = get_dictionary();

    add_word(thisdic, "a");
    add_word(thisdic, "and");
    add_word(thisdic, "house");


    if (!find_word(thisdic, "a"))
    {
        printf("Error: expect 'a' to exist.\n");
    }

    if (find_word(thisdic, "as"))
    {
        printf("Error: expect 'as' to not exist.\n");
    }

    if (!find_word(thisdic, "and"))
    {
        printf("Error: expect 'and' to exist.\n");
    }

    if (find_word(thisdic, "x"))
    {
        printf("Error: expect 'x' to not exist.\n");
    }

    free_dictionary(thisdic);
}

/**
 * Test load function.
 */
void test_load(void)
{
    load("dictionaries/small");
    //load("dictionaries/large");
    unload();
}

/**
 * Runs testing functions for dictionary implementation.
 */
void test_dictionary(void)
{
    test_to_position();
    test_add_word();
    test_find_word();
    test_free_progeny();
    test_free_dictionary();
    test_load();
}
