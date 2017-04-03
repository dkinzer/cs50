/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// board positions
int positions[DIM_MAX * DIM_MAX][2];

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // Tally numbers in opposite order
    int next_number = (d * d) - 1;

    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            board[row][col] = next_number;
            positions[next_number][0] = row;
            positions[next_number][1] = col;
            next_number--;
        }
    }

    // Swap possition 1 & 2 for even d
    if (d % 2 == 0)
    {
        int one_row = positions[1][0];
        int one_col = positions[1][1];
        int two_row = positions[2][0];
        int two_col = positions[2][1];

        board[one_row][one_col] = 2;
        board[two_row][two_col] = 1;
        positions[1][1] = two_col;
        positions[2][1] = one_col;
    }

}

/**
 * Prints the board in its current state.
 */
void draw(void)
{

    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            
            // Draw special case
            if (board[row][col] == 0)
            {
                if (d == 3)
                {
                    printf("%2s", "_");
                }
                else
                {
                    printf("%3s", "_");
                }
                continue;
            }

            if (d == 3)
            {
                printf("%2d", board[row][col]);
            }
            else
            {
                printf("%3d", board[row][col]);
            }
        }
            if (d == 3)
            {
                printf("\n");
            }
            else
            {
                printf("\n\n");
            }
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // Check tile broundries
    if (tile < 1 && tile > (d * d) - 1)
    {
        return false;
    }

    int tile_row = positions[tile][0];
    int tile_col = positions[tile][1];
    int zero_row = positions[0][0];
    int zero_col = positions[0][1];

    // Check if tile is next to zero
    bool above = tile_row ==  zero_row - 1 && tile_col == zero_col;
    bool below = tile_row ==  zero_row + 1 && tile_col == zero_col;
    bool left = tile_row ==  zero_row && tile_col == zero_col - 1;
    bool right = tile_row ==  zero_row && tile_col == zero_col + 1;
    
    if (above || below || left || right)
    {
        // Switch tile positions
        positions[0][0] = tile_row;
        positions[0][1] = tile_col;
        positions[tile][0] = zero_row;
        positions[tile][1] = zero_col;

        // Switch board numbers
        board[tile_row][tile_col] = 0;
        board[zero_row][zero_col] = tile;

        return true;
    }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int previous = board[0][0];

    // Check that board position numbers are in order
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            // Skip first check
            if (row == 0 &&  col == 0)
            {
                continue;
            }
            // Skip the last check
            if (row == d - 1 && col == d - 1)
            {
                continue;
            }
            if (board[row][col] != previous + 1)
            {
                return false;
            }
            // Update previous
            previous = board[row][col];
        }
    }
    return true;
}
