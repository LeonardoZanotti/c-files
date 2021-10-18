#include <stdio.h>
#include <stdlib.h>

typedef struct Node NodeData;
typedef NodeData *List;
struct Node
{
    struct Node *previous;
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
    if (L == NULL)
        return 0;
    int count = 0;
    NodeData *N = *L;
    while (N != NULL)
    {
        count++;
        N = (*N).next;
    }
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
    if (L != NULL)
    {
        while ((*L) != NULL)
        {
            NodeData *N = *L;
            *L = (*L)->next;
            free(N);
        }
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
    (*N).previous = NULL;
    (*N).next = *L;
    if ((*L) != NULL)
        (*L)->previous = N;
    *L = N;
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
    (*N).next = NULL;
    if ((*L) == NULL)
    {
        (*N).previous = NULL;
        *L = N;
    }
    else
    {
        NodeData *NAux = *L;
        while ((*NAux).next != NULL)
            NAux = (*NAux).next;
        (*N).previous = NAux;
        (*NAux).next = N;
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
        (*N).previous = NULL;
        (*N).next = NULL;
        *L = N;
    }
    else
    {
        NodeData *previous, *actual = *L;

        while (actual != NULL && (*actual).data < data)
        {
            previous = actual;
            actual = (*actual).next;
        }

        if (actual == *L)
        {
            (*L)->previous = N;
            (*N).previous = NULL;
            (*N).next = *L;
            *L = N;
        }
        else
        {
            (*N).previous = previous;
            (*N).next = (*previous).next;
            (*previous).next = N;
            if (actual != NULL)
                (*actual).previous = N;
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

    NodeData *N = (*L);
    *L = (*N).next;
    if ((*N).next != NULL)
        (*(*N).next).previous = NULL;

    free(N);

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

    NodeData *N = *L;

    while ((*N).next != NULL)
    {
        N = (*N).next;
    }

    if ((*N).previous == NULL)
        (*L) = (*N).next;
    else
        (*(*N).previous).next = NULL;

    free(N);

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

    for (int i = 0; i < index; i++)
    {
        N = (*N).next;
    }

    if ((*N).previous == NULL)
        (*L) = (*N).next;
    else
        (*(*N).previous).next = (*N).next;

    if ((*N).next != NULL)
        (*(*N).next).previous = (*N).previous;

    printf("\nThe element %d has been removed from index %d\n", (*N).data, index);

    free(N);

    return 1;
}

// Find data by content
int search_by_content(List *L, int data, int *index)
{
    if (empty_list(L))
        return 0;

    *index = 0;
    NodeData *N = *L;

    while (N != NULL && (*N).data != data)
    {
        N = (*N).next;
        (*index)++;
    }

    if (N != NULL)
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
        for (NodeData *N = *L; N != NULL; N = (*N).next)
            printf("\n%d", (*N).data);
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

        printf("\n1) Create doubly linked list\n");
        printf("2) Free doubly linked list\n");
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
// https://www.youtube.com/watch?v=0BDMqra4D94&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=11
// https://www.youtube.com/watch?v=wfC61zUVaos&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=12
// https://www.youtube.com/watch?v=WvmBhiQjPZ0&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=13
// https://www.youtube.com/watch?v=fNP1GHLLKuY&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=14
// https://www.youtube.com/watch?v=67KZx_Rcfgw&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=15
// https://www.youtube.com/watch?v=rzPsfHZIlek&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=16