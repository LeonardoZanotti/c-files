#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Matrix node
typedef struct MatrixInfo
{
    float data;
    int row, col;
    struct MatrixInfo *next;
} MatrixNode;
typedef MatrixNode *SparseMatrix;

// List of matrixes
typedef struct ListNode
{
    SparseMatrix data;
    struct ListNode *next;
} Matrix;
typedef Matrix *MatrixList;

// Uma função que faz a alocação de memória para cada nodo criado para uma lista encadeada;
// Uma função que insere na lista encadeada um nodo alocado;
// Uma função que busca os dados em uma lista encadeada;
// Uma função que libera da memória uma lista encadeada;
// Uma função que lê os dados da matriz, via teclado, e inseri na lista encadeada somente os dados diferentes de zero;
// Uma função que soma duas matrizes;
// Uma função que subtrai duas matrizes;
// Uma função que multiplica duas matrizes;
// Uma função que gera a matriz transposta;
// Uma função que imprime todos os dados da matriz, inclusive os zeros;
// Uma função que imprime os elementos da diagonal principal, inclusive os zeros caso existam.

// Create a matrix list
MatrixList *create_matrix_list()
{
    MatrixList *L = (MatrixList *)malloc(sizeof(MatrixList));
    if (L != NULL)
        *L = NULL;
    return L;
}

// Create a sparse matrix
SparseMatrix *create_sparse_matrix()
{
    SparseMatrix *L = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    if (L != NULL)
    {
        *L = NULL;
    }
    return L;
}

// Insert matrix in the end of the matrix list
int insert_matrix_end(MatrixList *L, SparseMatrix *matrix)
{
    if (L == NULL)
        return 0;
    Matrix *M = (Matrix *)malloc(sizeof(Matrix));
    if (M == NULL)
        return 0;
    (*M).data = matrix;
    (*M).next = NULL;
    if ((*L) == NULL)
        *L = M;
    else
    {
        Matrix *MAux = *L;
        while ((*MAux).next != NULL)
            MAux = (*MAux).next;
        (*MAux).next = M;
    }
    return 1;
}

// Insert value in the end of the matrix
int insert_matrix_value_end(SparseMatrix *L, float data, int row, int col)
{
    if (L == NULL)
        return 0;
    MatrixNode *N = (MatrixNode *)malloc(sizeof(MatrixNode));
    if (N == NULL)
        return 0;
    (*N).data = data;
    (*N).row = row;
    (*N).col = col;
    (*N).next = NULL;
    if ((*L) == NULL)
        *L = N;
    else
    {
        MatrixNode *NAux = *L;
        while ((*NAux).next != NULL)
            NAux = (*NAux).next;
        (*NAux).next = N;
    }
    return 1;
}

// Clear the matrix nodes from memory
void free_matrix(SparseMatrix *S)
{
    if (S != NULL)
    {
        while ((*S) != NULL)
        {
            MatrixNode *N = *S;
            (*S) = (*S)->next;
            free(N);
        }
        free(S);
    }
}

// Clear the matrix list from memory
void free_matrix_list(MatrixList *L)
{
    if (L != NULL)
    {
        while ((*L) != NULL)
        {
            Matrix *M = *L;
            *L = (*L)->next;
            free_matrix((*M).data);
            free(M);
        }
        free(L);
    }
}

int main()
{
    char option[3];
    int optionInt = 0;
    MatrixList *matrixList = create_matrix_list();

    while (optionInt != 12)
    {
        optionInt = 0;

        printf("\n1) Create new matrix\n");
        printf("2) Clear matrix\n");
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
            create_new_matrix(matrixList);
            break;
        case 2:
            free_matrix(matrixList);
            break;
        case 12:
            free_matrix_list(matrixList);
            break;
        default:
            break;
        }
    }

    return 0;
}