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
#include <ctype.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int* x, int* y);

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
    // all values - 1
    int val_tile = d * d - 1;
    
    // loop through columns
    for (int col = 0; col < d; col++)
    {
        // loop through rows
        for (int row = 0; row < d && val_tile >= 0; row++)
        {
            // assign value
            board[col][row] = val_tile;
            // set next value
            val_tile--;
        }
    }
    
    // swap 1 and 2 if d is even
    if ((d % 2) == 0)
    {
        swap(&board[d - 1][d - 3], &board[d - 1][d - 2]);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // loop through rows
    for (int row = 0; row < d; row++)
    {
        // loop through columns
        for (int col = 0; col < d; col++)
        {
            // check for empty tile
            if (board[row][col] == 0)
            {
                // prints ' ' instead of 0
                printf("  ");
            }
            
            // print value
            else
            {
                // prints value and space
                printf("%2d ", board[row][col]);
            }
        }
        
        // print next line
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int rowloc;
    int colloc;
    // check if user gives valid input
    if (tile == 0 || tile > (d * d))
    {
        // wrong move
        return false;
    }
    
    // loops through rows
    for (int row = 0; row < d; row++)
    {
        // loops through columns
        for (int col = 0; col < d; col++)
        {
            // check for tile
            if (board[row][col] == tile)
            {
                // save row and column of tile
                rowloc = row;
                colloc = col;
            }
        }
    }
    
    // check all posible locations
    // make sure we don't go out of bounds
    
    // check if empty tile is below
    if (rowloc > 0)
    {
        if (board[rowloc - 1][colloc] == 0)
        {
            swap(&board[rowloc][colloc], &board[rowloc - 1][colloc]);
            return true;
        }
    }
    
    // check if empty tile is above 
    if (rowloc < (d - 1))
    {
        if (board[rowloc + 1][colloc] == 0)
        {
            swap(&board[rowloc][colloc], &board[rowloc + 1][colloc]);
            return true;
        }
    }
    
    // check if empty tile is on left side
    if (colloc > 0)
    {
        if (board[rowloc][colloc - 1] == 0)
        {
            swap(&board[rowloc][colloc], &board[rowloc][colloc - 1]);
            return true;
        }
    }
    
    // check if empty tile is on right side
    if (colloc < (d - 1))
    {
        if (board[rowloc][colloc + 1] == 0)
        {
            swap(&board[rowloc][colloc], &board[rowloc][colloc + 1]);
            return true;
        }
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // set first value to be checked
    int check_val = 1;
    
    // loop through columns
    for (int i = 0; i < d; i++)
    {
       // loop through rows
        for (int j = 0; j < d; j++)
        {
            // check for value
            if (board[i][j] == check_val)
            {
                // set next check value
                check_val++;
                
                // once last tile is reached
                if (check_val == (d * d))
                {
                    // check if last tile is 0
                    if (board[(d - 1)][(d - 1)] == 0)
                    {
                        // user won
                        return true;
                    }
                }
            }
            
            // if values don't match, game is not won (yet)
            else
                return false;
        }
    }
    
    // if anything goes wrong, stop function
    return false;
}

/**
 * Swaps 2 integer values
 **/
void swap(int* x, int* y)
{
    int swp = *x;
    *x = *y;
    *y = swp;
}