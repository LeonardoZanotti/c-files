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
// Remover do meio
// Consultar pelo conteúdo
// Consultar pela posição
// Imprimir Lista(Esta operação não foi apresentada pelo prof.André.)