#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

#define WALL "\u2589"
#define VISITED "\u2591"
#define FREE " "
#define PLAYER "\u263A"
#define EXIT "\u2573"

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
        *stack = NULL;

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
int stackable_item(int row, int col, int mazeSize)
{
    return row * mazeSize + col;
}

// get the row from a stack item
int get_item_row(StackNode *item, int mazeSize)
{
    return (*item).data / mazeSize;
}

// get the col from a stack item
int get_item_col(StackNode *item, int mazeSize)
{
    return (*item).data % mazeSize;
}

int main(int argc, char **argv)
{
    char ch;
    int mazeSize = 0, mazeSize1 = 0, mazeSize2 = 0, found = 0, end;

    Stack *stack = create_stack();

    // open the file with the maze
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    // file validation (see if is a square)
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch != '\n')
        {
            mazeSize++;
            mazeSize2++;
        }
        else
        {
            if (mazeSize1 != 0 && mazeSize != mazeSize1)
            {
                printf("The maze must be a square!\n");
                exit(1);
            }
            mazeSize1 = mazeSize;
            mazeSize = 0;
        }
    }

    if (mazeSize != sqrt(mazeSize2))
    {
        printf("The maze must be a square!\n");
        exit(1);
    }

    rewind(file);

    // fill the matrix with file data
    char maze[mazeSize][mazeSize];
    int row = 0, col = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch != '\n')
        {
            if (ch == '3')
                insert_start(stack, stackable_item(row, col, mazeSize));
            maze[row][col] = ch;
            col++;
        }
        else
        {
            row++;
            col = 0;
        }
    }

    // solve the maze
    do
    {
        printf("\e[1;1H\e[2J");
        usleep(50000); // sleep 0.5 seconds

        row = get_item_row(*stack, mazeSize);
        col = get_item_col(*stack, mazeSize);
        end = 1;

        maze[row][col] = '4';

        // check left
        if (col > 0 && (maze[row][col - 1] == '1' || maze[row][col - 1] == '2'))
            insert_start(stack, stackable_item(row, col - 1, mazeSize));

        // check right
        else if (col < mazeSize - 1 && (maze[row][col + 1] == '1' || maze[row][col + 1] == '2'))
            insert_start(stack, stackable_item(row, col + 1, mazeSize));

        // check up
        else if (row > 0 && (maze[row - 1][col] == '1' || maze[row - 1][col] == '2'))
            insert_start(stack, stackable_item(row - 1, col, mazeSize));

        // check down
        else if (row < mazeSize - 1 && (maze[row + 1][col] == '1' || maze[row + 1][col] == '2'))
            insert_start(stack, stackable_item(row + 1, col, mazeSize));

        // return because path is blocked
        else
            remove_start(stack);

        if (empty_stack(stack))
            break;

        row = get_item_row(*stack, mazeSize);
        col = get_item_col(*stack, mazeSize);
        found = maze[row][col] == '2';
        maze[row][col] = '3';

        if ((col > 0 && maze[row][col - 1] == '2') ||
            (col < mazeSize - 1 && maze[row][col + 1] == '2') ||
            (row > 0 && maze[row - 1][col] == '2') ||
            (row < mazeSize - 1 && maze[row + 1][col] == '2'))
            end = 0;

        for (row = 0; row < mazeSize; row++)
        {
            for (col = 0; col < mazeSize; col++)
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

    fclose(file);
    free_stack(stack);

    return 0;
}