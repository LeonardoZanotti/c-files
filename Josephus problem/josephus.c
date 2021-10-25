#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMES_SIZE 20

typedef struct Node NodeData;
typedef NodeData *List;
struct Node
{
    char data[NAMES_SIZE];
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
int insert_end(List *L, char data[NAMES_SIZE])
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
    printf("Soldier %s added\n", data);
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

    printf("\nThe soldier %s has been removed!", (*N).data);
    free(N);

    return 1;
}

// Find data by content
int search_by_content(List *L, char data[NAMES_SIZE], int *index)
{
    if (empty_list(L))
        return 0;

    int i, found = 0;

    NodeData *N = *L;
    for (i = 0; i < size_list(L); i++)
    {
        if (strcmp((*N).data, data) == 0)
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

int chooseSoldier(List *L, int startSoldierIndex, int num)
{
    if (empty_list(L))
        return 0;

    int i, indexToRemove;
    char escapedSoldier[NAMES_SIZE];
    NodeData *N = *L;

    for (i = 0; i < startSoldierIndex; i++)
        N = (*N).next;

    while (size_list(L) > 1)
    {
        for (i = 0; i < num; i++)
            N = (*N).next;

        NodeData *NAux = (*N).next;
        strcpy(escapedSoldier, (*NAux).data);

        search_by_content(L, (*N).data, &indexToRemove);
        remove_middle(L, indexToRemove);

        N = NAux;
    }
    printf("\nThe soldier %s has the one who escaped!\n", escapedSoldier);
    return 1;
}

int main()
{
    char input[3], soldierName[NAMES_SIZE];
    int soldierCounter = 1, sortNumber = -1, shouldPrint = 1;
    List *list = create_list();

    while (sortNumber < 0)
    {
        printf("\nNumber for the count: ");
        scanf("%s", input);
        sortNumber = atoi(input);
    }

    while (soldierName[0] != ':')
    {
        if (shouldPrint)
        {
            printf("\nName for the %d° soldier: ", soldierCounter);
            shouldPrint = 0;
        }
        fgets(soldierName, sizeof(soldierName), stdin);
        soldierName[strlen(soldierName) - 1] = '\0';
        if (strlen(soldierName) > 0 && soldierName[0] != ':')
        {
            insert_end(list, soldierName);
            soldierCounter++;
            shouldPrint = 1;
        }
    }

    do
    {
        printf("\nName of the start soldier: ");
        fgets(soldierName, sizeof(soldierName), stdin);
        soldierName[strlen(soldierName) - 1] = '\0';
    } while (!search_by_content(list, soldierName, &soldierCounter));

    chooseSoldier(list, soldierCounter, sortNumber);
    free_list(list);

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