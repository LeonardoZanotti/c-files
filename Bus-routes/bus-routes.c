#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// recoding getch to work in Linux
// thanks to https://gist.github.com/jerry2yu/2591964
#define cls system("clear")
#include <termios.h>
#include <unistd.h>
int getch();
int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

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

// List cities
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

// List routes
int see_routes(RoutesList *L)
{
    if (!empty_routes_list(L))
    {
        printf("\nRoutes:");
        for (RouteNodeData *N = *L; N != NULL; N = (*N).next)
        {
            printf("\n%s", ((*(*N).route)).destination);
            // see_cities((*N).route);
        }
        printf("\n\n");
    }
    return 0;
}

// Insert route in the end of the Route list
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

// Insert city in the end of some route
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
        CityNodeData *CuritibaN = (CityNodeData *)malloc(sizeof(CityNodeData));
        if (N == NULL)
            return 0;

        strcpy((*CuritibaN).name, "Curitiba");
        strcpy((*CuritibaN).description, "Grande quantidade de pinheiros");
        (*CuritibaN).previous = NULL;
        (*CuritibaN).next = N;
        (*N).previous = CuritibaN;
        (*L).start = CuritibaN;
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

// Create a route list
RoutesList *create_routes_list()
{
    RoutesList *L = (RoutesList *)malloc(sizeof(RoutesList));
    if (L != NULL)
        *L = NULL;
    return L;
}

// Create a city list
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

// Get the data to create new city and call the function that creates the city
void add_city_to_list(CitiesList *C)
{
    char cityName[30];
    char cityDescription[60];
    printf("City name: ");
    fgets(cityName, sizeof(cityName), stdin);
    cityName[strlen(cityName) - 1] = '\0';

    printf("City description: ");
    fgets(cityDescription, sizeof(cityDescription), stdin);
    cityDescription[strlen(cityDescription) - 1] = '\0';

    insert_cities_end(C, cityName, cityDescription);
}

// Menu to insert new cities in a route
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
        printf("[1] - Add new city to route\n");
        printf("\n[2] - Save route\n\n");
        scanf("%3s", input);
        getchar();
        inputInt = atoi(input);
    }

    strcpy((*C).destination, (*(*C).end).name);

    see_cities(C);

    return 1;
}

// Clear the cities list from memory
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

// Clear the routes list from memory
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

// Remove routes from the middle of the list
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

    free_cities_list((*N).route);
    free(N);

    return 1;
}

// Search routes by the destination
int search_routes_by_content(RoutesList *L, char destination[30], int *index)
{
    if (empty_routes_list(L))
        return 0;

    if (strcmp(destination, "exit") == 0)
    {
        *index = -1;
        return 1;
    }

    int i, found = 0;

    RouteNodeData *N = *L;
    for (i = 0; i < size_routes_list(L); i++)
    {
        if (strcmp((*(*N).route).destination, destination) == 0)
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

// Menu that shows the routes and then enter the view cities menu
int visit_routes(RoutesList *L)
{
    if (empty_routes_list(L))
        return 0;

    char option[30];
    int index;
    do
    {
        printf("\e[1;1H\e[2J");
        printf("Which route do you want to visit?\n(type \"exit\" to cancel)\n");
        see_routes(L);
        fgets(option, sizeof(option), stdin);
        option[strlen(option) - 1] = '\0';
    } while (!search_routes_by_content(L, option, &index));

    if (index == -1)
        return 0;

    RouteNodeData *N = *L;
    for (int i = 0; i < index; i++)
    {
        N = (*N).next;
    }

    char c = '0';
    CityNodeData *CN = (*(*N).route).start;

    do
    {
        if ((int)c == 68 || c == '1')
        {
            if ((*CN).previous != NULL)
                CN = (*CN).previous;
        }
        else if ((int)c == 67 || c == '2')
        {
            if ((*CN).next != NULL)
                CN = (*CN).next;
        }

        printf("\e[1;1H\e[2J");
        printf("City name: %s\n", (*CN).name);
        printf("City description: %s\n\n", (*CN).description);
        printf("previous [1 - <-]\tnext [-> - 2]\n");
        printf("0 to exit\n");

        c = getch();
    } while (c != '0');

    return 1;
}

// Menu to remove routes
int remove_route(RoutesList *L)
{
    if (empty_routes_list(L))
        return 0;

    char option[30];
    int index;

    do
    {
        printf("\e[1;1H\e[2J");
        printf("Which route do you want to remove?\n(type \"exit\" to cancel)\n");
        see_routes(L);
        fgets(option, sizeof(option), stdin);
        option[strlen(option) - 1] = '\0';
    } while (!search_routes_by_content(L, option, &index));

    if (index != -1)
        remove_routes_middle(L, index);

    return 1;
}

int main()
{
    char option[3];
    RoutesList *routesList = create_routes_list();
    int optionInt = 0;

    printf("\e[1;1H\e[2J");

    while (optionInt != 4)
    {
        optionInt = 0;

        printf("1) Create route\n");
        printf("2) Remove route\n");
        printf("3) Visit route\n");
        printf("4) Exit\n");

        while (!(optionInt >= 1 && optionInt <= 4))
        {
            printf("\nChoose an option: ");
            scanf("%3s", option);
            getchar();
            optionInt = atoi(option);
        }

        switch (optionInt)
        {
        case 1:
            create_new_route(routesList);
            break;
        case 2:
            remove_route(routesList);
            break;
        case 3:
            visit_routes(routesList);
            break;
        case 4:
            free_routes_list(routesList);
            break;
        default:
            break;
        }

        printf("\n");
    }

    return 0;
}