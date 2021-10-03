#include <stdio.h>

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

// Remove element from the list by index
int remove_index(List_type *v, int index)
{
    int i, data;
    if ((*v).end != 0)
    {
        if ((index >= 0) && (index < (*v).end))
        {
            if (index == 0)
            {
                if (exclui_inicio_lista(v, &data) == 1)
                    printf("\nThe element %d has been removed from index %d", data, index);
                return 1;
            }
            else if (index == (*v).end - 1)
            {
                if (exclui_fim_lista(v, &data) == 1)
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