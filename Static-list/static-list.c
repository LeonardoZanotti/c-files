#include <stdio.h>
#include <stdlib.h>

#define MAX_VETOR 5

typedef struct Vetor
{
    int data[MAX_VETOR];
    int start, end;
} List_type;

// Insert in the end of the list
int insert_end(List_type *v, int data)
{
    if ((*v).end < MAX_VETOR)
    {
        (*v).data[(*v).end] = data;
        (*v).end++;
        return 1;
    }
    return 0;
}

// Remove element from the start of the list
int remove_start(List_type *v, int *data)
{
    return 0;
}

// Remove element from the end of the list
int remove_end(List_type *v, int *data)
{
    return 0;
}

// Remove element from the middle of the list by index
int remove_middle(List_type *v, int index)
{
    int i, data;
    if ((*v).end != 0)
    {
        if ((index >= 0) && (index < (*v).end))
        {
            if (index == 0)
            {
                if (remove_start(v, &data) == 1)
                    printf("\nThe element %d has been removed from index %d", data, index);
                return 1;
            }
            else if (index == (*v).end - 1)
            {
                if (remove_end(v, &data) == 1)
                    printf("\nThe element %d has been removed from index %d", data, index);
                return 1;
            }
            else
            {
                data = (*v).data[index];
                for (i = index; i < (*v).end; i++)
                    (*v).data[i] = (*v).data[i + 1];
                (*v).end--;
                printf("\nThe element %d has been removed from index %d", data, index);
                return 1;
            }
        }
        return -1;
    }
    return 0;
}

// Find data by content
int search_by_content(List_type v, int data, int *index)
{
    int i, found = 0;
    for (i = 0; i < v.end - 1; i++)
    {
        if (v.data[i] == data)
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

// Print all the list data
int print_list(List_type v)
{
    int i;
    if (v.end != 0)
    {
        for (i = 0; i < v.end; i++)
            printf("\n%d", v.data[i]);
        return 1;
    }
    return 0;
}

int main()
{
    char option[3];
    int optionInt = 0;

    while (optionInt != 12)
    {
        optionInt = 0;

        printf("\n1) Create static list\n");
        printf("2) Free static list\n");
        printf("3) Insert at the start\n");
        printf("4) Insert at the end\n");
        printf("5) Insert in the middle\n");
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
            printf("1");
            break;
        case 2:
            printf("2");
            break;
        case 3:
            printf("3");
            break;
        case 4:
            printf("4");
            break;
        case 5:
            printf("5");
            break;
        case 6:
            printf("6");
            break;
        case 7:
            printf("7");
            break;
        case 8:
            printf("8");
            break;
        case 9:
            printf("9");
            break;
        case 10:
            printf("10");
            break;
        case 11:
            printf("11");
            break;
        case 12:
            printf("12");
            break;
        default:
            break;
        }
    }

    return 0;
}

// Criar a lista
// Liberar a lista
// Verificar se lista cheia
// Verifica se lista vazia
// Inserir no início
// Inserir no meio(ordenado)
// Remover do início
// Remover do fim
// Consultar pelo conteúdo