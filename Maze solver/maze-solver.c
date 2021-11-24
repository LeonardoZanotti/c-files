#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
    {
        *stack = NULL;
    }

    printf("\nStack created!\n");

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
    printf("\nCleared stack from memory\n");
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
    printf("Inserted %d at the start of the stack\n", data);
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
    printf("Removed element from start of stack\n");
    return 1;
}

// Get element from the top of the stack
int get_top_of_stack(Stack *v, int *content)
{
    if (empty_stack(v))
        return 0;
    *content = (*v)->data;
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

void read_file(char path[])
{
}

int main(int argc, char **argv)
{
    char ch;
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    while ((ch = fgetc(file)) != EOF)
    {
        switch (ch)
        {
        case '0':
            printf("%s", WALL);
            break;
        case '1':
            printf("%s", FREE);
            break;
        case '2':
            printf("%s", EXIT);
            break;
        case '3':
            printf("%s", PLAYER);
            break;
        default:
            printf("\n");
            break;
        }
    }
    fclose(file);
    return 0;
}