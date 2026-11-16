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
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void greet(void);
void init(void);
void draw(void);
short move(int tile);
short won(void);
void findempty(int *row, int *col);
void findtile(int value, int *row, int *col);
int get_int();

int main(int argc, char* argv[])
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
    while (1)
    {
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
        fflush(stdout);
        int tile = get_int();
        
        printf("\n");

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
 * Get an non-negative integer from user input
 * If the input is not non-negative integer, return INT_MAX
 */
 int get_int(void)
 {
    char line[64];
    int input;

    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        return 0;         
    }
    
    if(sscanf(line,"%d", &input) !=1)
    {
        return INT_MAX;
    }
    return input;
}


    



    
 

/**
 * Greets player.
 */
void greet(void)
{    
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO

    int count = d*d- 1;
    for(int i = 0; i< d ;i++)
    {
        for(int j =0;j<d ;j++)
        {
            board[i][j] = count;
            count--;
        }
    }
    board[d-1][d-1]=0;
//check this part of the code
     if ((d * d - 1) % 2 == 1)
   {
       int r1, c1, r2, c2;
       findtile(1, &r1, &c1);
       findtile(2, &r2, &c2);
       board[r1][c1] = 2;
       board[r2][c2] = 1;
   }


}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO

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

    return;
}


void findempty(int *row, int *col)
{
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            if (board[i][j] == 0)
            {
                *row = i;
                *col = j;
                return;
            }
}

void findtile(int value, int *row, int *col)
{
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            if (board[i][j] == value)
            {
                *row = i;
                *col = j;
                return;
            }
}

/**
 * If tile borders empty space, moves tile and returns 1, else
 * returns 0.
 */
short move(int tile)
{
    // TOD
    int emptycol;
    int emptyrow;
    int tilerow = -1;
    int tilecol = -1;findempty(&emptyrow, &emptycol); 
  if (tilerow == -1|| emptyrow>= d*d)
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
short won(void)
{
    // TODO
    int expected =1;
    for(int i =0; i<d; i++)
    {

        for(int j = 0;j <d;j++)
        {
            
            if(i == d-1&& j==d-1)
            {
                return board[i][j] == 0;
            }
            if(board[i][j] != expected)
            {
                return 0;
            }
            expected++;
        }
    }



    return false;

}
