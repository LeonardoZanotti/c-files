#include <stdio.h>
#include <stdlib.h>

#define MAX_VETOR 5

typedef struct queue
{
    int data[MAX_VETOR];
    int start, end, length;
} Queue;

// Auxiliar method
// Verify if queue is full
int size_queue(Queue *q)
{
    if (q == NULL)
        return -1;
    return (*q).length;
}

// Auxiliar method
// Verify if queue is full
int full_queue(Queue *q)
{
    if (q == NULL)
        return -1;
    return (*q).length == MAX_VETOR;
}

// Auxiliar method
// Verify if queue is empty
int empty_queue(Queue *q)
{
    if (q == NULL)
        return -1;
    return (*q).length == 0;
}

// Auxiliar method
// Read param value to use in the functions
void read_param(int *param)
{
    char input[3];
    printf("\nValue for the operation: ");
    scanf("%3s", input);
    *param = atoi(input);
}

// Create queue
Queue *create_queue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    if (queue != NULL)
    {
        (*queue).start = 0;
        (*queue).end = 0;
        (*queue).length = 0;
    }

    printf("\nQueue created!\n");

    return queue;
}

// Free the memory allocated to the queue
void free_queue(Queue *q)
{
    free(q);
    printf("\nCleared queue from memory\n");
}

// Insert in the end of the queue
int insert_end(Queue *q, int data)
{
    if (!full_queue(q))
    {
        (*q).data[(*q).end] = data;
        (*q).end++;
        (*q).length++;

        printf("Inserted %d at the end of the queue\n", data);

        return 1;
    }
    return 0;
}

// Remove element from the start of the queue
int remove_start(Queue *q)
{
    if (empty_queue(q))
        return 0;

    for (int i = 0; i < (*q).end; i++)
    {
        (*q).data[i] = (*q).data[i + 1];
    }

    (*q).end--;
    (*q).length--;

    printf("Removed element from start of queue\n");

    return 1;
}

// Get first element of the queue
int get_first(Queue *q)
{
    if (empty_queue(q))
        return 0;
    printf("First item of the queue is: %d\n", (*q).data[(*q).start]);
    return 1;
}

// Print all the queue data
int print_queue(Queue *q)
{
    int i;

    if (!empty_queue(q))
    {
        printf("\nQueue:");

        for (i = 0; i < (*q).end; i++)
            printf("\n%d", (*q).data[i]);

        printf("\n");

        return 1;
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

        printf("\n1) Create static queue\n");
        printf("2) Free static queue\n");
        printf("3) Insert at the end\n");
        printf("4) Remove from the start\n");
        printf("5) Get first item\n");
        printf("6) Print the queue\n");
        printf("7) Exit\n");

        while (!(optionInt >= 1 && optionInt <= 7))
        {
            printf("\nChoose an option: ");
            scanf("%3s", option);
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
// https://www.youtube.com/watch?v=aEfOzz_KXl8&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=32
// https://www.youtube.com/watch?v=y93DzmBskGQ&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=33
// https://www.youtube.com/watch?v=RLu9QLd_xpY&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=34
// https://www.youtube.com/watch?v=0KXFoxSCEJE&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=35
// https://www.youtube.com/watch?v=4YXnrKJCWrE&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=37
// https://www.youtube.com/watch?v=aIFK1n9Sp30&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=38
// https://www.youtube.com/watch?v=yOjgEXbKtME&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=39