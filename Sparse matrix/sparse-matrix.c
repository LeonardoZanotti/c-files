#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PRECISION 0.00001

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
// Check if two float numbers are equal
int fequal(float a, float b, float precision)
{
    return fabs(a - b) < precision;
}

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
// Verify the size of the matrix list
int size_matrix_list(MatrixList *L)
{
    if (L == NULL)
        return 0;
    int count = 0;
    Matrix *M = *L;
    while (M != NULL)
    {
        count++;
        M = (*M).next;
    }
    return count;
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
void see_matrix(SparseMatrix *S, int diagonal)
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

        if (diagonal)
        {
            printf("\nDiagonal of matrix:\n[");
            for (i = 1; i <= row; i++)
            {
                printf("\n");
                for (j = 1; j <= col; j++)
                {
                    if ((*N).row == i && (*N).col == j)
                    {
                        if (i == j)
                            printf("%4.1f ", (*N).data);
                        else
                            printf("%4s ", "");
                        if ((*N).next)
                            N = (*N).next;
                    }
                    else
                        printf("%4s ", "");
                }
            }
            printf("\n]\n");
        }
        else
        {
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
    }
}

void show_matrix(MatrixList *L)
{
    char input[3];
    int matrixIndex = 0;

    while (matrixIndex < 1 || matrixIndex > size_matrix_list(L))
    {
        printf("\e[1;1H\e[2J");
        printf("Index of the matrix to show: ");
        scanf("%3s", input);
        getchar();
        matrixIndex = atof(input);
    }

    Matrix *M = (*L);
    SparseMatrix *S = (*M).data;
    for (int i = 1; i < matrixIndex; i++)
    {
        M = (*M).next;
        S = (*M).data;
    }

    see_matrix(S, 0);
}

// Search value in the matrixes
int search_value_in_matrix(SparseMatrix *S, float value, int *row, int *col)
{
    if (empty_matrix(S))
        return 1;

    int i, found = 0;

    MatrixNode *N = *S;
    for (i = 0; i < size_matrix(S); i++)
    {
        if (fequal((*N).data, value, PRECISION))
        {
            *row = (*N).row;
            *col = (*N).col;
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
    int matrixIndex = 1, row = -1, col = -1;
    float inputFloat;

    printf("\e[1;1H\e[2J");
    printf("Value to search: ");
    scanf("%3s", input);
    getchar();
    inputFloat = atof(input);

    Matrix *M = (*L);
    SparseMatrix *S = (*M).data;
    while (!search_value_in_matrix(S, inputFloat, &row, &col))
    {
        if (M == NULL || (*M).next == NULL)
            break;
        M = (*M).next;
        S = (*M).data;
        matrixIndex++;
    }

    see_matrix(S, 0);
    (row > -1)
        ? printf("\nFound value %4.2f at field [%d, %d] in the matrix %d\n", inputFloat, row, col, matrixIndex)
        : printf("\nNot found\n");
}

void add_value_to_matrix(SparseMatrix *S, int row, int col)
{
    char input[20];
    float inputFloat;
    printf("Value for field [%d, %d] of the matrix: ", row, col);
    scanf("%20s", input);
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

        scanf("%3s", input);
        getchar();
        inputInt = atoi(input);
    }

    see_matrix(S, 0);
}

void read_params(int *matrix1, int *matrix2, int twoParams)
{
    char input[3], text[7] = "";

    if (twoParams)
        strcpy(text, "first ");

    printf("Index of the %smatrix: ", text);
    scanf("%3s", input);
    getchar();
    (*matrix1) = atoi(input);

    if (twoParams)
    {
        printf("Index of the second matrix: ");
        scanf("%3s", input);
        getchar();
        (*matrix2) = atoi(input);
    }
}

void see_diagonal_of_matrix(MatrixList *L, int index)
{
    Matrix *M = (*L);
    for (int i = 1; i < index; i++)
        M = (*M).next;

    see_matrix((*M).data, 1);
}

int main()
{
    char option[3];
    int optionInt = 0, matrix1 = -1, matrix2 = -1;
    MatrixList *matrixList = create_matrix_list();

    while (optionInt != 9)
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
            scanf("%3s", option);
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
        case 4:
            read_params(&matrix1, &matrix2, 1);
            // sum_matrix(matrixList, matrix1, matrix2);
            break;
        case 5:
            read_params(&matrix1, &matrix2, 1);
            // subtract_matrix(matrixList, matrix1, matrix2);
            break;
        case 6:
            read_params(&matrix1, &matrix2, 1);
            // multiply_matrix(matrixList, matrix1, matrix2);
            break;
        case 7:
            read_params(&matrix1, &matrix2, 0);
            // transposed_matrix(matrixList, matrix1);
            break;
        case 8:
            read_params(&matrix1, &matrix2, 0);
            see_diagonal_of_matrix(matrixList, matrix1);
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