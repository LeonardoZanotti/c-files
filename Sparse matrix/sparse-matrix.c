#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PRECISION 0.00001

// Matrix size - rows and cols
typedef struct RowCol
{
    int rows, cols;
} MatrixSize;

// Matrix node
typedef struct MatrixInfo
{
    float data;
    MatrixSize info;
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
// Get matrix by index
Matrix *get_matrix_by_index(MatrixList *L, int index)
{
    Matrix *M = (*L);
    for (int i = 1; i < index; i++)
        M = (*M).next;
    return M;
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
MatrixSize size_matrix(SparseMatrix *S)
{
    MatrixSize info;
    info.rows = 0;
    info.cols = 0;

    if (!empty_matrix(S))
    {

        MatrixNode *N = (*S);
        for (; N != NULL; N = (*N).next)
        {
            if ((*N).info.rows > info.rows)
                info.rows = (*N).info.rows;
            if ((*N).info.cols > info.cols)
                info.cols = (*N).info.cols;
        }
    }

    return info;
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
    printf("Created new matrix at index %d\n", size_matrix_list(L));
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
    (*N).info.rows = row;
    (*N).info.cols = col;
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
        int i, j;

        MatrixNode *N = (*S);
        MatrixSize info = size_matrix(S);

        if (diagonal)
        {
            printf("\nDiagonal of matrix:\n[");
            for (i = 1; i <= info.rows; i++)
            {
                printf("\n");
                for (j = 1; j <= info.cols; j++)
                {
                    if (i == j)
                    {
                        while ((*N).next && ((*N).info.rows < i || (*N).info.cols < j))
                            N = (*N).next;

                        if ((*N).info.rows == i && (*N).info.cols == j)
                            printf("%4.1f ", (*N).data);
                        else
                            printf("%4.1f ", 0.0);
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
            for (i = 1; i <= info.rows; i++)
            {
                printf("\n");
                for (j = 1; j <= info.cols; j++)
                {
                    if ((*N).info.rows == i && (*N).info.cols == j)
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

void show_matrix(MatrixList *L, int matrixIndex)
{
    char input[3];

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
    MatrixSize info = size_matrix(S);
    for (i = 0; i < info.rows * info.cols; i++)
    {
        if (fequal((*N).data, value, PRECISION))
        {
            *row = (*N).info.rows;
            *col = (*N).info.cols;
            found = 1;
            break;
        }
        if (!(*N).next)
            break;
        N = (*N).next;
    }

    if (found)
        return 1;

    return 0;
}

void search_matrix(MatrixList *L)
{
    char input[3];
    int matrixIndex, row = -1, col = -1;
    float inputFloat;

    printf("\e[1;1H\e[2J");
    printf("Value to search: ");
    scanf("%3s", input);
    getchar();
    inputFloat = atof(input);

    Matrix *M = (*L);
    SparseMatrix *S = (*M).data;
    for (matrixIndex = 1; matrixIndex <= size_matrix_list(L); matrixIndex++)
    {
        if (search_value_in_matrix(S, inputFloat, &row, &col))
            break;
        if ((*M).next)
        {
            M = (*M).next;
            S = (*M).data;
        }
    }

    if (row > -1)
    {
        see_matrix(S, 0);
        printf("\nFound value %4.1f at field [%d, %d] in the matrix %d\n", inputFloat, row, col, matrixIndex);
    }
    else
        printf("\nNot found\n");
}

void add_value_to_matrix(SparseMatrix *S, int row, int col, int last)
{
    char input[20];
    float inputFloat;
    printf("Value for field [%d, %d] of the matrix: ", row, col);
    scanf("%20s", input);
    getchar();
    inputFloat = atof(input);
    if (last || inputFloat != 0.0)
        insert_matrix_value_end(S, inputFloat, row, col);
}

void create_new_matrix(MatrixList *L)
{
    printf("\e[1;1H\e[2J");

    SparseMatrix *S = create_sparse_matrix();
    insert_matrix_end(L, S);

    char input[3];
    int row, col;

    printf("\nNumber of rows of the matrix: ");

    scanf("%10s", input);
    getchar();
    row = atoi(input);

    printf("Number of cols of the matrix: ");

    scanf("%10s", input);
    getchar();
    col = atoi(input);

    printf("\n");

    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            add_value_to_matrix(S, i, j, (i == row && j == col));
        }
    }

    see_matrix(S, 0);
}

// void create_new_matrix(MatrixList *M)
// {
//     SparseMatrix *S = create_sparse_matrix();
//     insert_matrix_end(M, S);

//     char input[3];
//     int inputInt = 1, row = 1, col = 1;

//     while (inputInt == 1 || inputInt == 2)
//     {
//         printf("\e[1;1H\e[2J");

//         if (inputInt == 1)
//         {
//             add_value_to_matrix(S, row, col);
//             printf("\e[1;1H\e[2J");
//         }

//         if (inputInt == 2)
//         {
//             col = 1;
//             row++;
//         }
//         else
//             col++;

//         printf("[1] - Add value to field [%d, %d] of the matrix\n", row, col);
//         printf("\n[2] - New row\n");
//         printf("\n[3] - Save matrix\n\n");

//         scanf("%3s", input);
//         getchar();
//         inputInt = atoi(input);
//     }

//     see_matrix(S, 0);
// }

void read_params(MatrixList *L, int *matrix1, int *matrix2, int twoParams)
{
    char input[3], text[7] = "";
    (*matrix1) = -1;
    (*matrix2) = -1;

    if (twoParams)
        strcpy(text, "first ");

    while ((*matrix1) < 1 || (*matrix1) > size_matrix_list(L))
    {
        printf("\e[1;1H\e[2J");
        printf("Index of the %smatrix: ", text);
        scanf("%3s", input);
        getchar();
        (*matrix1) = atoi(input);
    }

    if (twoParams)
    {
        while ((*matrix2) < 1 || (*matrix2) > size_matrix_list(L))
        {
            printf("\e[1;1H\e[2J");
            printf("Index of the second matrix: ");
            scanf("%3s", input);
            getchar();
            (*matrix2) = atoi(input);
        }
    }
}

void add_matrix(MatrixList *L, int index1, int index2)
{
    Matrix *M1 = get_matrix_by_index(L, index1);
    Matrix *M2 = get_matrix_by_index(L, index2);

    MatrixSize info1 = size_matrix((*M1).data);
    MatrixSize info2 = size_matrix((*M2).data);

    if (info1.rows != info2.rows || info1.cols == info2.cols)
    {
        printf("The matrixes should have the same size!");
    }
    else
    {
        printf("sum");
    }
}

void subtract_matrix(MatrixList *L, int index1, int index2)
{
    Matrix *M1 = get_matrix_by_index(L, index1);
    Matrix *M2 = get_matrix_by_index(L, index2);

    MatrixSize info1 = size_matrix((*M1).data);
    MatrixSize info2 = size_matrix((*M2).data);

    if (info1.rows != info2.rows || info1.cols == info2.cols)
    {
        printf("The matrixes should have the same size!");
    }
    else
    {
        printf("sub");
    }
}

void transposed_matrix(MatrixList *L, int index)
{
    printf("\n");
    Matrix *M = get_matrix_by_index(L, index);
    SparseMatrix *T = create_sparse_matrix(), *S = (*M).data;
    insert_matrix_end(L, T);

    MatrixNode *N = (*S);
    MatrixSize info = size_matrix(S);

    for (int i = 1; i <= info.cols; i++)
    {
        for (int j = 1; j <= info.rows; j++)
        {
            do
            {
                if ((*N).info.rows == j && (*N).info.cols == i)
                {
                    insert_matrix_value_end(T, (*N).data, (*N).info.cols, (*N).info.rows);
                    break;
                }
                N = (*N).next;
            } while (N);
            N = (*S);
        }
    }
    see_matrix(T, 0);
}

void see_diagonal_of_matrix(MatrixList *L, int index)
{
    Matrix *M = get_matrix_by_index(L, index);
    see_matrix((*M).data, 1);
}

int main()
{
    char option[3];
    int optionInt = 0, matrix1 = -1, matrix2 = -1;
    MatrixList *matrixList = create_matrix_list();

    printf("\e[1;1H\e[2J");

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
            read_params(matrixList, &matrix1, &matrix2, 0);
            show_matrix(matrixList, matrix1);
            break;
        case 3:
            search_matrix(matrixList);
            break;
        case 4:
            read_params(matrixList, &matrix1, &matrix2, 1);
            add_matrix(matrixList, matrix1, matrix2);
            break;
        case 5:
            read_params(matrixList, &matrix1, &matrix2, 1);
            subtract_matrix(matrixList, matrix1, matrix2);
            break;
        case 6:
            read_params(matrixList, &matrix1, &matrix2, 1);
            // multiply_matrix(matrixList, matrix1, matrix2);
            break;
        case 7:
            read_params(matrixList, &matrix1, &matrix2, 0);
            transposed_matrix(matrixList, matrix1);
            break;
        case 8:
            read_params(matrixList, &matrix1, &matrix2, 0);
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