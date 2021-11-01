#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List of routes (linked list)
typedef struct RouteNode RouteNodeData;
typedef RouteNodeData *RoutesList;
struct RouteNode
{
    struct RouteNode *next;
    CitiesList route;
};

// Routes list (doubly linked list with header)
typedef struct CityNode CityNodeData;
typedef struct Header CitiesList;
struct CityNode
{
    struct CityNode *previous;
    struct CityNode *next;
    char name[30];
    char description[60];
};
struct Header
{
    CityNodeData *start;
    CityNodeData *end;
    char destination[30];
    int length;
};

// Auxiliar method
// Verify if routes list is empty
int empty_routes_list(RoutesList *L)
{
    if (L == NULL || (*L) == NULL)
        return 1;
    return 0;
}

// Auxiliar method
// Verify the size of the routes list
int size_routes_list(RoutesList *L)
{
    if (L == NULL)
        return 0;
    int count = 0;
    RouteNodeData *N = *L;
    while (N != NULL)
    {
        count++;
        N = (*N).next;
    }
    return count;
}

// Auxiliar method
// Verify if list is empty
int empty_cities_list(CitiesList *L)
{
    if (L == NULL || (*L).length == 0)
        return 1;
    return 0;
}

// Auxiliar method
// Verify the size of the list
int size_cities_list(CitiesList *L)
{
    if (L == NULL)
        return 0;
    return (*L).length;
}

RoutesList *create_routes_list()
{
    RoutesList *L = (RoutesList *)malloc(sizeof(RoutesList));
    if (L != NULL)
        *L = NULL;
    return L;
}

CitiesList *create_cities_list()
{
    CitiesList *L = (CitiesList *)malloc(sizeof(CitiesList));
    if (L != NULL)
    {

        (*L).start = NULL;
        (*L).end = NULL;
        strcpy((*L).destination, NULL);
        (*L).length = 0;
    }
    return L;
}

void free_routes_list(RoutesList *L)
{
    if (L != NULL)
    {
        while ((*L) != NULL)
        {
            RouteNodeData *N = *L;
            *L = (*L)->next;
            free(N);
        }
        free(L);
    }
    printf("\nCleared header list from memory\n");
}

void free_cities_list(CitiesList *L)
{
    if (L != NULL)
    {
        while ((*L).start != NULL)
        {
            CityNodeData *N = (*L).start;
            (*L).start = (*(*L).start).next;
            free(N);
        }
        free(L);
    }
    printf("\nCleared doubly linked list from memory\n");
}

int insert_routes_end(RoutesList *L, CitiesList route)
{
    if (L == NULL)
        return 0;
    RouteNodeData *N = (RouteNodeData *)malloc(sizeof(RouteNodeData));
    if (N == NULL)
        return 0;
    (*N).route = route;
    (*N).next = NULL;
    if ((*L) == NULL)
        *L = N;
    else
    {
        RouteNodeData *NAux = *L;
        while ((*NAux).next != NULL)
            NAux = (*NAux).next;
        (*NAux).next = N;
    }
    return 1;
}

int insert_cities_end(CitiesList *L, char name[30], char description[30])
{
    if (L == NULL)
        return 0;
    CityNodeData *N = (CityNodeData *)malloc(sizeof(CityNodeData));
    if (N == NULL)
        return 0;

    char name[30];
    char description[60];
    strcpy((*N).name, name);
    strcpy((*N).description, description);
    (*N).next = NULL;
    if ((*L).start == NULL)
    {
        (*N).previous = NULL;
        (*L).start = N;
    }
    else
    {
        (*N).previous = (*L).end;
        (*(*L).end).next = N;
    }
    (*L).end = N;
    (*L).length++;
    return 1;
}

int remove_routes_middle(RoutesList *L, int index)
{
    if (empty_routes_list(L) || index >= size_routes_list(L))
    {
        return 0;
    }

    RouteNodeData *previous, *N = *L;

    for (int i = 0; i < index; i++)
    {
        previous = N;
        N = (*N).next;
    }

    if (N == (*L))
        (*L) = (*N).next;
    else
        (*previous).next = (*N).next;

    free(N);

    return 1;
}

int remove_cities_middle(CitiesList *L, int index)
{
    if (empty_cities_list(L) || index >= size_cities_list(L))
    {
        return 0;
    }

    CityNodeData *N = (*L).start;

    for (int i = 0; i < index; i++)
    {
        N = (*N).next;
    }

    if (N == (*L).start)
    {
        (*L).start = (*N).next;
        (*L).length--;
        if ((*L).start == NULL)
            (*L).end = NULL;
        else
            (*(*L).start).previous = NULL;
    }
    else if (N == (*L).end)
    {
        (*(*N).previous).next = (*N).next;
        (*L).end = (*N).previous;
    }
    else
    {
        (*(*N).next).previous = (*N).previous;
        (*(*N).previous).next = (*N).next;
    }

    (*L).length--;
    free(N);

    return 1;
}

int main()
{
    char option[3];
    int optionInt = 0;

    while (optionInt != 4)
    {
        optionInt = 0;

        printf("\n1) Create route\n");
        printf("2) Remove route\n");
        printf("3) Visit route\n");
        printf("4) Exit\n");

        while (!(optionInt >= 1 && optionInt <= 4))
        {
            printf("\nChoose an option: ");
            scanf("%s", option);
            optionInt = atoi(option);
        }

        switch (optionInt)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
        }
    }

    return 0;
}