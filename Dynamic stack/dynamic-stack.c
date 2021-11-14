#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    char option[3];
    int optionInt = 0;
    Stack *stack;

    char input[3];
    int content;

    while (optionInt != 12)
    {
        optionInt = 0;

        printf("\n1) Create dynamic stack\n");
        printf("2) Free dynamic stack\n");
        printf("3) Insert at the start\n");
        printf("6) Remove from the start\n");
        printf("9) Find the top\n");
        printf("11) Print the stack\n");
        printf("12) Exit\n");

        while (!(optionInt >= 1 && optionInt <= 12))
        {
            printf("\nChoose an option: ");
            scanf("%s", option);
            optionInt = atoi(option);
        }

        switch (optionInt)
        {
        case 1:
            stack = create_stack();
            break;
        case 2:
            free_stack(stack);
            break;
        case 3:
            printf("\nValue for the operation: ");
            scanf("%s", input);
            int param = atoi(input);
            insert_start(stack, param);
            break;
        case 6:
            remove_start(stack);
            break;
        case 9:
            get_top_of_stack(stack, &content);
            printf("Value in the top of the stack is: %d\n", content);
            break;
        case 11:
            print_stack(stack);
            break;
        case 12:
            free_stack(stack);
            printf("\nExiting...\n");
            break;
        default:
            break;
        }
    }

    return 0;
}

// References
// https://www.youtube.com/watch?v=_LWwqbHU8L0      Using OBS
// https://www.tads.ufpr.br/pluginfile.php/15801/mod_resource/content/1/operacoes_ed_codigofonte.pdf        // book
// https://www.youtube.com/watch?v=2RCrd7gOUMM&stack=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=39
// https://www.youtube.com/watch?v=OIQJL-K2SUI&stack=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=40
// https://www.youtube.com/watch?v=X_-paXn4At8&stack=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=41
// https://www.youtube.com/watch?v=n7fKiYoCvUo&stack=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=42
// https://www.youtube.com/watch?v=9GGJH2sjOac&stack=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=43
// https://www.youtube.com/watch?v=RPf6DgjS3OM&stack=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=44
// https://www.youtube.com/watch?v=06sqFaB3gU0&stack=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=45
