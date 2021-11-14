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
    SparseMatrix *data;
    struct ListNode *next;
} Matrix;
typedef Matrix *MatrixList;

// Auxiliar method
// Verify if matrix list is empty
int empty_matrix_list(MatrixList *L)
{
    return (L == NULL || (*L) == NULL);
}

// Auxiliar method
// Verify if matrix is empty
int empty_matrix(SparseMatrix *S)
{
    return (S == NULL || (*S) == NULL);
}

// Auxiliar method
// Check matrix size
int size_matrix(SparseMatrix *S)
{
    if (empty_matrix(S))
        return 0;

    int row = 1, col = 1;

    MatrixNode *N = (*S);
    for (; N != NULL; N = (*N).next)
    {
        if ((*N).row > row)
            row = (*N).row;
        if ((*N).col > col)
            col = (*N).col;
    }

    return row * col;
}

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

// List matrix values
int see_matrix(SparseMatrix *S)
{
    if (!empty_matrix(S))
    {
        int row = 0, col = 0, i, j;

        MatrixNode *N = (*S);
        for (; N != NULL; N = (*N).next)
        {
            if ((*N).row > row)
                row = (*N).row;
            if ((*N).col > col)
                col = (*N).col;
        }

        N = *S;
        printf("\nMatrix:\n[");
        for (i = 1; i <= row; i++)
        {
            printf("\n");
            for (j = 1; j <= col; j++)
            {
                if ((*N).row == i && (*N).col == j)
                {
                    printf("%4.1f ", (*N).data);
                    if ((*N).next)
                        N = (*N).next;
                }
                else
                    printf("%4.1f ", 0.0);
            }
        }
        printf("\n]\n");
    }
    return 0;
}

// Search value in the matrixes
int search_value_in_matrix(SparseMatrix *S, float value, int *index)
{
    if (empty_matrix(S))
        return 0;

    int i, found = 0;

    MatrixNode *N = *S;
    for (i = 0; i < size_matrix(S); i++)
    {
        if ((*N).data = value)
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

void search_matrix(MatrixList *L)
{
    char input[3];
    int matrixIndex = 0, valueIndex = -1;
    float inputFloat;

    printf("\e[1;1H\e[2J");
    printf("Value to search: ");
    scanf("%s", input);
    getchar();
    inputFloat = atoi(input);

    Matrix *M = (*L);
    SparseMatrix *S = (*M).data;
    while (!search_value_in_matrix(S, inputFloat, valueIndex))
    {
        if (valueIndex != -1)
            break;
        M = (*M).next;
        S = (*M).data;
        matrixIndex++;
    }

    see_matrix(S);
    valueIndex != -1
        ? printf("Found value %f at index %d in the matrix %d", inputFloat, valueIndex, matrixIndex)
        : printf("Not found");
}

void add_value_to_matrix(SparseMatrix *S, int row, int col)
{
    char input[20];
    float inputFloat;
    printf("Value for field [%d, %d] of the matrix: ", row, col);
    scanf("%s", input);
    getchar();
    inputFloat = atof(input);
    if (inputFloat != 0.0)
        insert_matrix_value_end(S, inputFloat, row, col);
}

void create_new_matrix(MatrixList *M)
{
    SparseMatrix *S = create_sparse_matrix();
    insert_matrix_end(M, S);

    char input[3];
    int inputInt = 1, row = 1, col = 1;

    while (inputInt == 1 || inputInt == 2)
    {
        printf("\e[1;1H\e[2J");

        if (inputInt == 1)
        {
            add_value_to_matrix(S, row, col);
            printf("\e[1;1H\e[2J");
        }

        if (inputInt == 2)
        {
            col = 1;
            row++;
        }
        else
            col++;

        printf("[1] - Add value to field [%d, %d] of the matrix\n", row, col);
        printf("\n[2] - New row\n");
        printf("\n[3] - Save matrix\n\n");

        scanf("%s", input);
        getchar();
        inputInt = atoi(input);
    }

    see_matrix(S);
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
        printf("2) See matrix\n");
        printf("3) Search in matrix\n");
        printf("4) Sum matrix\n");
        printf("5) Subtract matrix\n");
        printf("6) Multiply matrix\n");
        printf("7) Transposed matrix\n");
        printf("8) See diagonal of matrix\n");
        printf("9) Exit\n");

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
            show_matrix(matrixList);
            break;
        case 3:
            search_matrix(matrixList);
            break;
        case 9:
            free_matrix_list(matrixList);
            break;
        default:
            break;
        }
    }

    return 0;
}