#include <stdio.h>
#include <stdlib.h>

// Matrix node
typedef struct MatrixNode
{
    float data;
    int row, col;
    struct MatrixNode *next;
} SparseMatrix;

// List of matrixes
typedef struct ListNode
{
    SparseMatrix data;
    struct ListNode *next;
} Matrix;
typedef Matrix *MatrixList;

// Uma  função  que  faz  a  alocação  de  memória  para  cada  nodo  criado  para  uma  lista encadeada;
// Uma função que insere na lista encadeada um nodo alocado;
// Uma função que busca os dados em uma lista encadeada;
// Uma função que libera da memória uma lista encadeada;
// Uma função que lê os dados da matriz, via teclado, e inseri na lista encadeada somente os dados diferentes de zero;
// Uma função que soma duas matrizes;
// Uma função que subtrai duas matrizes;
// Uma função que multiplica duas matrizes;
// Uma função que gera a matriz transposta;
// Uma função que imprime todos os dados da matriz, inclusive os zeros;
// Uma  função  que  imprime  os  elementos  da  diagonal  principal,  inclusive  os  zeros  caso existam.

int main()
{
    char option[3];
    int optionInt = 0;
    MatrixList *list;

    while (optionInt != 12)
    {
        optionInt = 0;

        printf("\n1) Create chained list\n");
        printf("2) Free chained list\n");
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
        default:
            break;
        }
    }

    return 0;
}