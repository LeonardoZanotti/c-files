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
int full_queue(Queue *v)
{
    if (v == NULL)
        return -1;
    return (*v).end == MAX_VETOR;
}

// Auxiliar method
// Verify if queue is empty
int empty_queue(Queue *v)
{
    if (v == NULL)
        return -1;
    return (*v).end == 0;
}

// Auxiliar method
// Print the results of the search
void print_search_result(int searchResult)
{
    if (searchResult != -1)
    {
        printf("Found item: %d\n", searchResult);
    }
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
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    if (queue != NULL)
    {
        (*queue).start = 0;
        (*queue).end = 0;
    }

    printf("\nQueue created!\n");

    return queue;
}

// Free the memory allocated to the queue
void free_queue(Queue *v)
{
    free(v);
    printf("\nCleared queue from memory\n");
}

// Insert in the start of the queue
int insert_start(Queue *v, int data)
{
    if (!full_queue(v))
    {
        for (int i = (*v).end - 1; i >= 0; i--)
            (*v).data[i + 1] = (*v).data[i];

        (*v).data[0] = data;
        (*v).end++;

        printf("Inserted %d at the start of the queue\n", data);

        return 1;
    }
    return 0;
}

// Insert in the end of the queue
int insert_end(Queue *v, int data)
{
    if (!full_queue(v))
    {
        (*v).data[(*v).end] = data;
        (*v).end++;

        printf("Inserted %d at the end of the queue\n", data);

        return 1;
    }
    return 0;
}

// Insert item sorted in the queue
int insert_sorted(Queue *v, int data)
{
    if (!full_queue(v))
    {
        int k = 0, i = 0;

        while (k < (*v).end && (*v).data[k] < data)
        {
            k++;
        }

        if ((*v).end != 0)
        {
            for (i = (*v).end - 1; i >= k; i--)
            {
                (*v).data[i + 1] = (*v).data[i];
            }
        }

        (*v).data[k] = data;
        (*v).end++;

        printf("Inserted %d at in the queue sorted\n", data);

        return 1;
    }
    return 0;
}

// Remove element from the start of the queue
int remove_start(Queue *v)
{
    if (empty_queue(v))
    {
        return 0;
    }

    for (int i = 0; i < (*v).end; i++)
    {
        (*v).data[i] = (*v).data[i + 1];
    }

    (*v).end--;

    printf("Removed element from start of queue\n");

    return 1;
}

// Remove element from the end of the queue
int remove_end(Queue *v)
{
    if (empty_queue(v))
    {
        return 0;
    }

    (*v).end--;

    printf("Removed element from end of queue\n");

    return 1;
}

// Remove element from the middle of the queue by index
int remove_middle(Queue *v, int index)
{
    int i, data;
    if (!empty_queue(v))
    {
        if ((index >= 0) && (index < (*v).end))
        {
            if (index == 0)
            {
                remove_start(v);
                return 1;
            }
            else if (index == (*v).end - 1)
            {
                remove_end(v);
                return 1;
            }
            else
            {
                data = (*v).data[index];

                for (i = index; i < (*v).end; i++)
                    (*v).data[i] = (*v).data[i + 1];

                (*v).end--;

                printf("\nThe element %d has been removed from index %d\n", data, index);

                return 1;
            }
        }
        return -1;
    }
    return 0;
}

// Find data by content
int search_by_content(Queue *v, int data, int *index)
{
    int i, found = 0;

    for (i = 0; i < (*v).end - 1; i++)
    {
        if ((*v).data[i] == data)
        {
            *index = i;
            found = 1;
            break;
        }
    }

    if (found)
        return 1;

    return 0;
}

// Find data by index
int search_by_index(Queue *v, int *data, int index)
{
    if (v == NULL || index < 0 || index >= (*v).end)
    {
        return 0;
    }

    *data = (*v).data[index];

    return 1;
}

// Print all the queue data
int print_queue(Queue *v)
{
    int i;

    if (!empty_queue(v))
    {
        printf("\nQueue:");

        for (i = 0; i < (*v).end; i++)
            printf("\n%d", (*v).data[i]);

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

    while (optionInt != 12)
    {
        optionInt = 0;

        printf("\n1) Create static queue\n");
        printf("2) Free static queue\n");
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
            search_by_content(queue, param, &searchResult);
            print_search_result(searchResult);
            break;
        case 10:
            read_param(&param);
            search_by_index(queue, &searchResult, param);
            print_search_result(searchResult);
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
// https://www.youtube.com/watch?v=_LWwqbHU8L0      Using OBS
// https://www.tads.ufpr.br/pluginfile.php/15801/mod_resource/content/1/operacoes_ed_codigofonte.pdf        // book
// https://www.youtube.com/watch?v=lKwEQgV6nZk&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=3
// https://www.youtube.com/watch?v=S6rOYN-UiAA&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=4
// https://www.youtube.com/watch?v=rxVrRdF0MTE&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=5
// https://www.youtube.com/watch?v=UCDCEjRDYrE&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=6
// https://www.youtube.com/watch?v=zO8JAxb1GmA&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=7
// https://www.youtube.com/watch?v=IpL31ZkVZSI&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=8
// https://www.youtube.com/watch?v=3KwG_OAB98g&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=9
// https://www.youtube.com/watch?v=xFN6Nefpx0k&queue=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=10
