#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// List of routes (linked list)
typedef struct RouteNode RouteNodeData;
typedef RouteNodeData *RoutesList;
struct RouteNode
{
    struct RouteNode *next;
    CitiesList *route;
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

int see_cities(CitiesList *L)
{
    if (!empty_cities_list(L))
    {
        printf("\nCities of the route:");
        for (CityNodeData *N = (*L).start; N != NULL; N = (*N).next)
            printf("\n%s - %s", (*N).name, (*N).description);
        printf("\n");
    }
    return 0;
}

int see_routes(RoutesList *L)
{
    if (!empty_routes_list(L))
    {
        printf("\nRoutes:");
        for (RouteNodeData *N = *L; N != NULL; N = (*N).next)
        {
            printf("\n%s\n", ((*(*N).route)).destination);
            see_cities((*N).route);
        }
        printf("\n");
    }
    return 0;
}

int insert_routes_end(RoutesList *L, CitiesList *route)
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

int insert_cities_end(CitiesList *L, char name[30], char description[60])
{
    if (L == NULL)
        return 0;
    CityNodeData *N = (CityNodeData *)malloc(sizeof(CityNodeData));
    if (N == NULL)
        return 0;

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
        strcpy((*L).destination, "");
        (*L).length = 0;
    }
    return L;
}

void add_city_to_list(CitiesList *C)
{
    char cityName[30];
    char cityDescription[60];
    printf("City name: ");
    fgets(cityName, 30, stdin);
    cityName[strlen(cityName) - 1] = '\0';

    printf("City description: ");
    fgets(cityDescription, 60, stdin);
    cityDescription[strlen(cityDescription) - 1] = '\0';

    insert_cities_end(C, cityName, cityDescription);
}

int create_new_route(RoutesList *L)
{
    CitiesList *C = create_cities_list();
    insert_routes_end(L, C);

    char input[3];
    int inputInt = 1;

    while (inputInt == 1)
    {
        printf("\e[1;1H\e[2J");
        add_city_to_list(C);
        printf("\e[1;1H\e[2J");
        printf("\n[1] - Add new city to route\n");
        printf("\n[2] - Save route\n");
        scanf("%s", input);
        getchar();
        inputInt = atoi(input);
    }

    strcpy((*C).destination, (*(*C).end).name);

    see_cities(C);

    return 1;
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
}

void free_routes_list(RoutesList *L)
{
    if (L != NULL)
    {
        while ((*L) != NULL)
        {
            RouteNodeData *N = *L;
            *L = (*L)->next;
            free_cities_list((*N).route);
            free(N);
        }
        free(L);
    }
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
    RoutesList *routesList = create_routes_list();
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
            getchar();
            optionInt = atoi(option);
        }

        switch (optionInt)
        {
        case 1:
            create_new_route(routesList);
            break;
        case 2:
            break;
        case 3:
            see_routes(routesList);
            break;
        case 4:
            free_routes_list(routesList);
            break;
        default:
            break;
        }
    }

    return 0;
}