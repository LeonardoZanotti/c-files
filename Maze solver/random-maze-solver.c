#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define WALL "\u2589"
#define VISITED "\u2591"
#define FREE " "
#define PLAYER "\u263A"
#define EXIT "\u2573"
#define MAZE_SIZE 31

typedef struct StackBase StackNode;
typedef StackNode *Stack;
struct StackBase
{
    int data;
    StackNode *next;
};

// Auxiliar method
// Verify if stack is empty
int empty_stack(Stack *v)
{
    return (v == NULL || (*v) == NULL) ? 1 : 0;
}

// Auxiliar method
// Check stack length
int stack_length(Stack *v)
{
    if (empty_stack(v))
        return 0;
    int count = 0;
    StackNode *N = (*v);
    while (N != NULL)
    {
        count++;
        N = (*N).next;
    }
    return count;
}

// Create stack
Stack *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    if (stack != NULL)
    {
        *stack = NULL;
    }

    return stack;
}

// Free the memory allocated to the stack
void free_stack(Stack *v)
{
    if (v != NULL)
    {
        StackNode *N;
        while ((*v) != NULL)
        {
            N = (*v);
            *v = (*N).next;
            free(N);
        }
        free(v);
    }
}

// Insert in the start of the stack
int insert_start(Stack *v, int data)
{
    if (v == NULL)
        return 0;
    StackNode *N = (StackNode *)malloc(sizeof(StackNode));
    if (N == NULL)
        return 0;
    (*N).data = data;
    (*N).next = (*v);
    (*v) = N;
    return 1;
}

// Remove element from the start of the stack
int remove_start(Stack *v)
{
    if (empty_stack(v))
        return 0;
    StackNode *N = (*v);
    (*v) = (*N).next;
    free(N);
    return 1;
}

// Print all the stack data
int print_stack(Stack *v)
{
    if (!empty_stack(v))
    {
        printf("\nStack:");

        StackNode *N = (*v);
        while (N != NULL)
        {
            printf("\n%d", (*N).data);
            N = (*N).next;
        }

        printf("\n");

        return 1;
    }

    return 0;
}

// turn matrix item into a value that can be stored in the stack
int stackable_item(int row, int col)
{
    return row * MAZE_SIZE + col;
}

// get the row from a stack item
int get_item_row(StackNode *item)
{
    return (*item).data / MAZE_SIZE;
}

// get the col from a stack item
int get_item_col(StackNode *item)
{
    return (*item).data % MAZE_SIZE;
}

int main(int argc, char **argv)
{
    char ch;
    int found = 0, end;

    Stack *stack = create_stack();

    // fill the matrix with file data
    char maze[MAZE_SIZE][MAZE_SIZE];
    int row = 0, col = 0, playerRow = 0, playerCol = 0, exitRow = 0, exitCol = 0;

    srand(time(0));

    // random exit and player start cell
    while (playerRow == exitRow && playerCol == exitCol)
    {
        playerRow = rand() % (MAZE_SIZE - 2) + 1;
        playerCol = rand() % (MAZE_SIZE - 2) + 1;
        exitRow = rand() % (MAZE_SIZE - 2) + 1;
        exitCol = rand() % (MAZE_SIZE - 2) + 1;
    }

    // start the maze with all cells as walls
    for (row = 0; row < MAZE_SIZE; row++)
    {
        for (col = 0; col < MAZE_SIZE; col++)
        {
            maze[row][col] = '0';
        }
    }

    // create the ways
    for (row = 1; row < MAZE_SIZE - 1; row += 2)
    {
        for (col = 1; col < MAZE_SIZE - 1; col += 2)
        {
            int x1, y1;
            int x2, y2;
            int dx, dy;
            int dir = rand() % 4, count = 0;

            while (count < 4)
            {
                dx = 0;
                dy = 0;
                switch (dir)
                {
                case 0:
                    dx = 1;
                    break;
                case 1:
                    dy = 1;
                    break;
                case 2:
                    dx = -1;
                    break;
                default:
                    dy = -1;
                    break;
                }
                x1 = row + dx;
                y1 = col + dy;
                x2 = x1 + dx;
                y2 = y1 + dy;
                if (x2 > 0 && x2 < MAZE_SIZE - 1 && y2 > 0 && y2 < MAZE_SIZE - 1 && maze[x1][y1] == '0' && maze[x2][y2] == '0')
                {
                    maze[x1][y1] = '1';
                    maze[x2][y2] = '1';
                    row = x2;
                    col = y2;
                    dir = rand() % 4;
                    count = 0;
                }
                else
                {
                    dir = (dir + 1) % 4;
                    count += 1;
                }
            }
        }
    }

    // set player and exit, also, stack the player cell
    maze[playerRow][playerCol] = '3';
    maze[exitRow][exitCol] = '2';
    insert_start(stack, stackable_item(playerRow, playerCol));

    // solve the maze
    do
    {
        printf("\e[1;1H\e[2J");

        // usleep(50000);
        row = get_item_row(*stack);
        col = get_item_col(*stack);
        end = 1;

        maze[row][col] = '4';

        // check left
        if (col > 0 && (maze[row][col - 1] == '1' || maze[row][col - 1] == '2'))
            insert_start(stack, stackable_item(row, col - 1));

        // check right
        else if (col < MAZE_SIZE - 1 && (maze[row][col + 1] == '1' || maze[row][col + 1] == '2'))
            insert_start(stack, stackable_item(row, col + 1));

        // check up
        else if (row > 0 && (maze[row - 1][col] == '1' || maze[row - 1][col] == '2'))
            insert_start(stack, stackable_item(row - 1, col));

        // check down
        else if (row < MAZE_SIZE - 1 && (maze[row + 1][col] == '1' || maze[row + 1][col] == '2'))
            insert_start(stack, stackable_item(row + 1, col));

        // return because path is blocked
        else
            remove_start(stack);

        if (empty_stack(stack))
            break;

        row = get_item_row(*stack);
        col = get_item_col(*stack);
        found = maze[row][col] == '2';
        maze[row][col] = '3';

        if ((col > 0 && maze[row][col - 1] == '2') ||
            (col < MAZE_SIZE - 1 && maze[row][col + 1] == '2') ||
            (row > 0 && maze[row - 1][col] == '2') ||
            (row < MAZE_SIZE - 1 && maze[row + 1][col] == '2'))
            end = 0;

        for (row = 0; row < MAZE_SIZE; row++)
        {
            for (col = 0; col < MAZE_SIZE; col++)
            {
                switch (maze[row][col])
                {
                case '0':
                    printf("%s", WALL);
                    break;
                case '1':
                    printf("%s", FREE);
                    end = 0;
                    break;
                case '2':
                    printf("%s", EXIT);
                    break;
                case '3':
                    printf("%s", PLAYER);
                    break;
                case '4':
                    printf("%s", VISITED);
                    break;
                default:
                    break;
                }
            }
            printf("\n");
        }
    } while (!end && !found);

    if (found)
        printf("Found a solution (maybe not the best)!\n");
    else
        printf("Maze unsolveable!\n");

    free_stack(stack);

    return 0;
}