#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List of routes
typedef struct RouteNode RouteNodeData;
typedef RouteNodeData *RoutesList;
struct RouteNode
{
    struct RouteNode *next;
    CitiesList route;
};

// Routes list
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