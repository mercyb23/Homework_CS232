/**
 * fifteen.c
 *
 * Refer to Computer Science 50
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

#ifndef INT_MAX
    #define INT_MAX 12345678
#endif // INT_MAX

// board


int d;

// prototypes
void greet(void);
void free_board(int **board, int d);
void init(int **board, int d);
void draw(int **board, int d);
void findempty(int **board, int d, int *row, int *col);
void findtile(int **board, int d, int value, int *row, int *col);
short move(int **board, int d, int tile);
short won(int **board, int d);
int get_int(void);
int **allocate_board(int d);


int main(int argc, char* argv[])
{
 
    if (argc != 2)
    {
        printf("Usage: fifteen %s d\n",argv[0]);
        return 1;
    }

   
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

    // allocate the board on the heap
    int **board = allocate_board(d);
    if (board == NULL)
    {
        fclose(file);
        printf("Error: out of memory.\n");
        return 4;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init(board, d);

    // accept moves until game is won
    while (1)
    {
        // draw the current state of the board
        draw(board, d);

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
        if (won(board, d))
        {
            printf("ftw!\n");
            break;
        }

       
        printf("Tile to move: ");
        fflush(stdout);
        int tile = get_int();

        printf("\n");

        
        if (tile == 0)
        {
            break;
        }

        
        fprintf(file, "%i\n", tile);
        fflush(file);

      
        if (!move(board, d, tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        
        usleep(500000);
    }

   
    fclose(file);

   
    free_board(board, d);

   
    return 0;
}

/**
 * Gets an integer from user input.
 * Returns INT_MAX if the input is not an integer, 0 on end of input.
 */
int get_int(void)
{
    char line[64];
    int input;

    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        return 0;
    }

    if (sscanf(line, "%d", &input) != 1)
    {
        return INT_MAX;
    }
    return input;
}


void greet(void)
{
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}


int **allocate_board(int d)
{
    int **board = malloc(d * sizeof(int *));
    if (board == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < d; i++)
    {
        board[i] = malloc(d * sizeof(int));
        if (board[i] == NULL)
        {
            for (int k = 0; k < i; k++)
            {
                free(board[k]);
            }
            free(board);
            return NULL;
        }
    }

    return board;
}

/**
 * Frees a board allocated by allocate_board.
 */
void free_board(int **board, int d)
{
    for (int i = 0; i < d; i++)
    {
        free(board[i]);
    }
    free(board);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(int **board, int d)
{
    int count = d * d - 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = count;
            count--;
        }
    }
    board[d - 1][d - 1] = 0;

    // if the number of tiles is odd (d is even), swap 1 and 2
    if ((d * d - 1) % 2 == 1)
    {
        int r1, c1, r2, c2;
        findtile(board, d, 1, &r1, &c1);
        findtile(board, d, 2, &r2, &c2);
        board[r1][c1] = 2;
        board[r2][c2] = 1;
    }
}

/**
 *//Prints the board in its current state.
void draw(int **board, int d)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                printf("  ");
            }
            else
            {
                printf("%2d", board[i][j]);
            }
            printf(" ");
        }
        printf("\n");
    }
}

void findempty(int **board, int d, int *row, int *col)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void findtile(int **board, int d, int value, int *row, int *col)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == value)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

/**
 * If tile borders empty space, moves tile and returns 1, else
 * returns 0.
 */
short move(int **board, int d, int tile)
{
    int emptyrow = -1;
    int emptycol = -1;
    int tilerow = -1;
    int tilecol = -1;

    findempty(board, d, &emptyrow, &emptycol);

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                tilerow = i;
                tilecol = j;
            }
        }
    }

    if (tilerow == -1)
    {
        return 0;
    }

    int distance = abs(tilerow - emptyrow) + abs(tilecol - emptycol);
    if (distance == 1)
    {
        board[emptyrow][emptycol] = tile;
        board[tilerow][tilecol] = 0;
        return 1;
    }

    return 0;
}

/**
 * Returns 1 if game is won (i.e., board is in winning configuration),
 * else 0.
 */
short won(int **board, int d)
{
    int expected = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (i == d - 1 && j == d - 1)
            {
                return board[i][j] == 0;
            }
            if (board[i][j] != expected)
            {
                return 0;
            }
            expected++;
        }
    }

    return 0;
}
