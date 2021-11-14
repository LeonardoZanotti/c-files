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
// Print the results of the search
void print_search_result(int searchResult, int response)
{
    if (response)
        printf("Found item: %d\n", searchResult);
    else
        printf("Not found!\n");
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

// Insert in the start of the queue
int insert_start(Queue *L, int data)
{
    if (L == NULL)
        return 0;
    NodeData *N = (NodeData *)malloc(sizeof(NodeData));
    if (N == NULL)
        return 0;
    (*N).data = data;
    (*N).next = (*L).start;
    if ((*L).start == NULL)
        (*L).end = N;
    (*L).start = N;
    (*L).length++;
    printf("Inserted %d at the start of the queue\n", data);
    return 1;
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

// Insert item sorted in the queue
int insert_sorted(Queue *L, int data)
{
    if (L == NULL)
        return 0;

    NodeData *N = (NodeData *)malloc(sizeof(NodeData));
    if (N == NULL)
        return 0;

    (*N).data = data;

    if (empty_queue(L))
    {
        (*N).next = NULL;
        (*L).start = N;
    }
    else
    {
        NodeData *previous, *actual = (*L).start;

        while (actual != NULL && (*actual).data < data)
        {
            previous = actual;
            actual = (*actual).next;
        }

        if (actual == (*L).start)
        {
            (*N).next = (*L).start;
            (*L).start = N;
        }
        else
        {
            if ((*previous).next == NULL)
                (*L).end = N;
            (*N).next = (*previous).next;
            (*previous).next = N;
        }
    }

    (*L).length++;
    printf("Inserted %d at in the queue sorted\n", data);

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

// Remove element from the end of the queue
int remove_end(Queue *L)
{
    if (empty_queue(L))
    {
        return 0;
    }

    NodeData *previous, *N = (*L).start;

    while ((*N).next != NULL)
    {
        previous = N;
        N = (*N).next;
    }

    if (N == (*L).start)
    {
        (*L).start = NULL;
        (*L).end = NULL;
    }
    else
    {
        (*previous).next = (*N).next;
        (*L).end = previous;
    }

    (*L).length--;
    free(N);

    printf("Removed element from end of queue\n");

    return 1;
}

// Remove element from the middle of the queue by index
int remove_middle(Queue *L, int index)
{
    if (empty_queue(L) || index >= size_queue(L))
    {
        return 0;
    }

    NodeData *previous, *N = (*L).start;

    for (int i = 0; i < index; i++)
    {
        previous = N;
        N = (*N).next;
    }

    if (N == (*L).start)
    {
        remove_start(L);
    }
    else if (N == (*L).end)
    {
        remove_end(L);
    }
    else
    {
        (*previous).next = (*N).next;
        (*L).length--;
        printf("\nThe element %d has been removed from index %d\n", (*N).data, index);
    }

    free(N);

    return 1;
}

// Find data by content
int search_by_content(Queue *L, int data, int *index)
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

// Find data by index
int search_by_index(Queue *L, int *data, int index)
{
    if (empty_queue(L) || index < 0 || index >= size_queue(L))
    {
        return 0;
    }

    NodeData *N = (*L).start;
    for (int i = 0; i < index; i++)
        N = (*N).next;

    *data = (*N).data;

    return 1;
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

    while (optionInt != 12)
    {
        optionInt = 0;

        printf("\n1) Create chained header queue\n");
        printf("2) Free chained header queue\n");
        printf("3) Insert at the start\n");
        printf("4) Insert at the end\n");
        printf("5) Insert sorted\n");
        printf("6) Remove from the start\n");
        printf("7) Remove from the end\n");
        printf("8) Remove from the middle\n");
        printf("9) Find by content\n");
        printf("10) Find by index\n");
        printf("11) Print the queue\n");
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
            queue = create_queue();
            break;
        case 2:
            free_queue(queue);
            break;
        case 3:
            read_param(&param);
            insert_start(queue, param);
            break;
        case 4:
            read_param(&param);
            insert_end(queue, param);
            break;
        case 5:
            read_param(&param);
            insert_sorted(queue, param);
            break;
        case 6:
            remove_start(queue);
            break;
        case 7:
            remove_end(queue);
            break;
        case 8:
            read_param(&param);
            remove_middle(queue, param);
            break;
        case 9:
            read_param(&param);
            int contentResponse = search_by_content(queue, param, &searchResult);
            print_search_result(searchResult, contentResponse);
            break;
        case 10:
            read_param(&param);
            int indexResponse = search_by_index(queue, &searchResult, param);
            print_search_result(searchResult, indexResponse);
            break;
        case 11:
            print_queue(queue);
            break;
        case 12:
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