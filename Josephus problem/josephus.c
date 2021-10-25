#include <stdio.h>
#include <stdlib.h>

typedef struct Node NodeData;
typedef NodeData *List;
struct Node
{
    int data;
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

// Insert in the start of the list
int insert_start(List *L, int data)
{
    if (L == NULL)
        return 0;
    NodeData *N = (NodeData *)malloc(sizeof(NodeData));
    if (N == NULL)
        return 0;
    (*N).data = data;
    if ((*L) == NULL)
    {
        (*N).next = N;
        *L = N;
    }
    else
    {
        NodeData *NAux = *L;
        while ((*NAux).next != (*L))
            NAux = (*NAux).next;
        (*NAux).next = N;
        (*N).next = (*L);
        (*L) = N;
    }
    printf("Inserted %d at the start of the list\n", data);
    return 1;
}

// Insert in the end of the list
int insert_end(List *L, int data)
{
    if (L == NULL)
        return 0;
    NodeData *N = (NodeData *)malloc(sizeof(NodeData));
    if (N == NULL)
        return 0;
    (*N).data = data;
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
    printf("Inserted %d at the end of the list\n", data);
    return 1;
}

// Insert item sorted in the list
int insert_sorted(List *L, int data)
{
    if (L == NULL)
        return 0;

    NodeData *N = (NodeData *)malloc(sizeof(NodeData));
    if (N == NULL)
        return 0;

    (*N).data = data;

    if (empty_list(L))
    {
        *L = N;
        (*N).next = N;
    }
    else
    {
        if ((*L)->data > data)
        {
            NodeData *actual = (*L);
            while ((*actual).next != (*L))
                actual = (*actual).next;
            (*N).next = (*L);
            (*actual).next = N;
            (*L) = N;
        }
        else
        {
            NodeData *previous = (*L), *actual = (*L)->next;
            while (actual != (*L) && (*actual).data < data)
            {
                previous = actual;
                actual = (*actual).next;
            }
            (*previous).next = N;
            (*N).next = actual;
        }
    }

    printf("Inserted %d at in the list sorted\n", data);

    return 1;
}

// Remove element from the start of the list
int remove_start(List *L)
{
    if (empty_list(L))
    {
        return 0;
    }

    if ((*L) == (*L)->next)
    {
        free(*L);
        (*L) = NULL;
    }
    else
    {
        NodeData *N = (*L), *actual = (*L);

        while ((*actual).next != (*L))
            actual = (*actual).next;

        (*actual).next = (*N).next;
        *L = (*N).next;
        free(N);
    }
    printf("Removed element from start of list\n");
    return 1;
}

// Remove element from the end of the list
int remove_end(List *L)
{
    if (empty_list(L))
    {
        return 0;
    }

    if ((*L) == (*L)->next)
    {
        free(*L);
        (*L) = NULL;
    }
    else
    {

        NodeData *previous, *N = *L;

        while ((*N).next != (*L))
        {
            previous = N;
            N = (*N).next;
        }

        (*previous).next = (*N).next;

        free(N);
    }

    printf("Removed element from end of list\n");

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

    printf("\nThe element %d has been removed from index %d\n", (*N).data, index);
    free(N);

    return 1;
}

// Find data by content
int search_by_content(List *L, int data, int *index)
{
    if (empty_list(L))
        return 0;

    int i, found = 0;

    NodeData *N = *L;
    for (i = 0; i < size_list(L); i++)
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
int search_by_index(List *L, int *data, int index)
{
    if (empty_list(L) || index < 0 || index >= size_list(L))
    {
        return 0;
    }

    NodeData *N = *L;
    for (int i = 0; i < index; i++)
        N = (*N).next;

    *data = (*N).data;

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
            printf("\n%d", (*N).data);
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
    int searchResult;
    int param;

    while (optionInt != 12)
    {
        optionInt = 0;

        printf("\n1) Create circular linked list\n");
        printf("2) Free circular linked list\n");
        printf("3) Insert at the start\n");
        printf("4) Insert at the end\n");
        printf("5) Insert sorted\n");
        printf("6) Remove from the start\n");
        printf("7) Remove from the end\n");
        printf("8) Remove from the middle\n");
        printf("9) Find by content\n");
        printf("10) Find by index\n");
        printf("11) Print the list\n");
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
            list = create_list();
            break;
        case 2:
            free_list(list);
            break;
        case 3:
            read_param(&param);
            insert_start(list, param);
            break;
        case 4:
            read_param(&param);
            insert_end(list, param);
            break;
        case 5:
            read_param(&param);
            insert_sorted(list, param);
            break;
        case 6:
            remove_start(list);
            break;
        case 7:
            remove_end(list);
            break;
        case 8:
            read_param(&param);
            remove_middle(list, param);
            break;
        case 9:
            read_param(&param);
            int contentResponse = search_by_content(list, param, &searchResult);
            print_search_result(searchResult, contentResponse);
            break;
        case 10:
            read_param(&param);
            int indexResponse = search_by_index(list, &searchResult, param);
            print_search_result(searchResult, indexResponse);
            break;
        case 11:
            print_list(list);
            break;
        case 12:
            free_list(list);
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
// https://www.tads.ufpr.br/pluginfile.php/15801/mod_resource/content/1/operacoes_ed_codigofonte.pdf       // book
// https://www.youtube.com/watch?v=p8OxiV4FYK4&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=22
// https://www.youtube.com/watch?v=p8OxiV4FYK4&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=23
// https://www.youtube.com/watch?v=IhCIGie5CEo&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=24
// https://www.youtube.com/watch?v=iC9oH8ysoAU&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=25
// https://www.youtube.com/watch?v=Kf1uPFvr_fc&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=26
// https://www.youtube.com/watch?v=A4Vz4Dcf9ww&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=27
// https://www.youtube.com/watch?v=bT2QSkNMecg&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=28