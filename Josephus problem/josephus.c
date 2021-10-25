#include <stdio.h>
#include <stdlib.h>

#define MAX_VETOR 20

typedef struct Node NodeData;
typedef NodeData *List;
struct Node
{
    char data[MAX_VETOR];
    struct Node *next;
};

// Auxiliar method
// Initialize the list
void initialize_list(List *L)
{
    *L = NULL;
}

// Auxiliar method
// Verify if list is empty
int empty_list(List *L)
{
    if (L == NULL || (*L) == NULL)
        return 1;
    return 0;
}

// Auxiliar method
// Verify the size of the list
int size_list(List *L)
{
    if (empty_list(L))
        return 0;
    int count = 0;
    NodeData *N = *L;
    do
    {
        count++;
        N = (*N).next;
    } while (N != (*L));
    return count;
}

// Create list
List *create_list()
{
    List *L = (List *)malloc(sizeof(List));
    if (L != NULL)
        initialize_list(L);
    printf("\nList created!\n");
    return L;
}

// Free the memory allocated to the list
void free_list(List *L)
{
    if (!empty_list(L))
    {
        NodeData *NAux, *N = *L;
        while ((*N).next != (*L))
        {
            NAux = N;
            N = (*N).next;
            free(NAux);
        }
        free(N);
        free(L);
    }
    printf("\nCleared list from memory\n");
}

// Insert in the end of the list
int insert_end(List *L, char data[MAX_VETOR])
{
    if (L == NULL)
        return 0;
    NodeData *N = (NodeData *)malloc(sizeof(NodeData));
    if (N == NULL)
        return 0;
    strcpy((*N).data, data);
    if ((*L) == NULL)
    {
        *L = N;
        (*N).next = N;
    }
    else
    {
        NodeData *NAux = *L;
        while ((*NAux).next != (*L))
            NAux = (*NAux).next;
        (*NAux).next = N;
        (*N).next = *L;
    }
    printf("Inserted %s at the end of the list\n", data);
    return 1;
}

// Remove element from the middle of the list by index
int remove_middle(List *L, int index)
{
    if (empty_list(L) || index >= size_list(L))
    {
        return 0;
    }

    NodeData *N = *L;

    if (index == 0)
    {
        if (N == (*N).next)
        {
            (*L) = NULL;
        }
        else
        {
            NodeData *last = *L;
            while ((*last).next != *L)
                last = (*last).next;
            (*last).next = (*L)->next;
            *L = (*L)->next;
        }
    }
    else
    {
        NodeData *previous = N;
        N = (*N).next;

        for (int i = 1; i < index; i++)
        {
            previous = N;
            N = (*N).next;
        }

        (*previous).next = (*N).next;
    }

    printf("\nThe element %s has been removed from index %d\n", (*N).data, index);
    free(N);

    return 1;
}

// Print all the list data
int print_list(List *L)
{
    if (!empty_list(L))
    {
        printf("\nList:");
        NodeData *N = *L;
        do
        {
            printf("\n%s", (*N).data);
            N = (*N).next;
        } while (N != (*L));
        printf("\n");
    }
    return 0;
}

int main()
{
    char option[3];
    int optionInt = 0;
    List *list;

    while (optionInt != 12)
    {
        optionInt = 0;
        while (optionInt <= 0)
        {
            printf("\nNumber for the count: ");
            scanf("%s", option);
            optionInt = atoi(option);
        }
    }

    return 0;
}

// References
// https://www.youtube.com/watch?v=_LWwqbHU8L0      Using OBS
// https://www.tads.ufpr.br/pluginfile.php/15801/mod_resource/content/1/operacoes_ed_codigofonte.pdf       // book
// https://www.youtube.com/watch?v=p8OxiV4FYK4&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=22
// https://www.youtube.com/watch?v=p8OxiV4FYK4&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=23
// https://www.youtube.com/watch?v=IhCIGie5CEo&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=24
// https://www.youtube.com/watch?v=iC9oH8ysoAU&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=25
// https://www.youtube.com/watch?v=Kf1uPFvr_fc&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=26
// https://www.youtube.com/watch?v=A4Vz4Dcf9ww&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=27
// https://www.youtube.com/watch?v=bT2QSkNMecg&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=28