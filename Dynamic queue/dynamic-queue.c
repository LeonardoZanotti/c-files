#include <stdio.h>
#include <stdlib.h>

typedef struct Node NodeData;
typedef struct Header Queue;
struct Node
{
    int data;
    struct Node *next;
};
struct Header
{
    NodeData *start;
    NodeData *end;
    int length;
};

// Auxiliar method
// Initialize the queue
void initialize_queue(Queue *L)
{
    (*L).start = NULL;
    (*L).end = NULL;
    (*L).length = 0;
}

// Auxiliar method
// Verify if queue is empty
int empty_queue(Queue *L)
{
    if (L == NULL || (*L).length == 0)
        return 1;
    return 0;
}

// Auxiliar method
// Verify the size of the queue
int size_queue(Queue *L)
{
    if (L == NULL)
        return 0;
    return (*L).length;
}

// Auxiliar method
// Read param value to use in the functions
void read_param(int *param)
{
    char input[3];
    printf("\nValue for the operation: ");
    scanf("%s", input);
    *param = atoi(input);
}

// Create queue
Queue *create_queue()
{
    Queue *L = (Queue *)malloc(sizeof(Queue));
    if (L != NULL)
        initialize_queue(L);
    printf("\nQueue created!\n");
    return L;
}

// Free the memory allocated to the queue
void free_queue(Queue *L)
{
    if (L != NULL)
    {
        while ((*L).start != NULL)
        {
            NodeData *N = (*L).start;
            (*L).start = (*(*L).start).next;
            free(N);
        }
        free(L);
    }
    printf("\nCleared queue from memory\n");
}

// Insert in the end of the queue
int insert_end(Queue *L, int data)
{
    if (L == NULL)
        return 0;
    NodeData *N = (NodeData *)malloc(sizeof(NodeData));
    if (N == NULL)
        return 0;
    (*N).data = data;
    (*N).next = NULL;
    if ((*L).start == NULL)
        (*L).start = N;
    else
        (*(*L).end).next = N;
    (*L).end = N;
    (*L).length++;
    printf("Inserted %d at the end of the queue\n", data);
    return 1;
}

// Remove element from the start of the queue
int remove_start(Queue *L)
{
    if (empty_queue(L))
    {
        return 0;
    }

    NodeData *N = (*L).start;
    (*L).start = (*N).next;
    (*L).length--;
    if ((*L).start == NULL)
        (*L).end = NULL;
    free(N);

    printf("Removed element from start of queue\n");
    return 1;
}

// Get first element of the queue
int get_first(Queue *L)
{
    if (empty_queue(L))
        return 0;

    int i, found = 0;

    NodeData *N = (*L).start;
    for (i = 0; i < size_queue(L); i++)
    {
        if ((*N).data == data)
        {
            *index = i;
            found = 1;
            break;
        }
        N = (*N).next;
    }

    if (found)
        return 1;

    return 0;
}

// Print all the queue data
int print_queue(Queue *L)
{
    if (!empty_queue(L))
    {
        printf("\nQueue:");
        for (NodeData *N = (*L).start; N != NULL; N = (*N).next)
            printf("\n%d", (*N).data);
        printf("\n");
    }
    return 0;
}

int main()
{
    char option[3];
    int optionInt = 0;
    Queue *queue;
    int searchResult;
    int param;

    while (optionInt != 7)
    {
        optionInt = 0;

        printf("\n1) Create queue\n");
        printf("2) Free queue\n");
        printf("4) Insert at the end\n");
        printf("6) Remove from the start\n");
        printf("10) Get first item\n");
        printf("11) Print the queue\n");
        printf("12) Exit\n");

        while (!(optionInt >= 1 && optionInt <= 7))
        {
            printf("\nChoose an option: ");
            scanf("%s", option);
            optionInt = atoi(option);
        }

        switch (optionInt)
        {
        case 1:
            queue = create_queue();
            break;
        case 2:
            free_queue(queue);
            break;
        case 3:
            read_param(&param);
            insert_end(queue, param);
            break;
        case 4:
            remove_start(queue);
            break;
        case 5:
            get_first(queue);
            break;
        case 6:
            print_queue(queue);
            break;
        case 7:
            free_queue(queue);
            printf("\nExiting...\n");
            break;
        default:
            break;
        }
    }

    return 0;
}

// References
// https://www.youtube.com/watch?q=_LWwqbHU8L0      Using OBS
// https://www.tads.ufpr.br/pluginfile.php/15801/mod_resource/content/1/operacoes_ed_codigofonte.pdf        // book
// https://www.youtube.com/watch?v=aEfOzz_KXl8&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=32
// https://www.youtube.com/watch?v=y93DzmBskGQ&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=33
// https://www.youtube.com/watch?v=RLu9QLd_xpY&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=34
// https://www.youtube.com/watch?v=0KXFoxSCEJE&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=35
// https://www.youtube.com/watch?v=4YXnrKJCWrE&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=37
// https://www.youtube.com/watch?v=aIFK1n9Sp30&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=38
// https://www.youtube.com/watch?v=yOjgEXbKtME&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=39