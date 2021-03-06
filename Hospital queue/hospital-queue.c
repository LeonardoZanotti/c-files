#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct PatientNode PatientNodeData;
typedef struct Node NodeData;
typedef struct Header Queue;
struct PatientNode
{
    char name[50];
    char phone[20];
    int urgency;
};
struct Node
{
    PatientNodeData data;
    struct Node *next;
};
struct Header
{
    NodeData *start;
    NodeData *end;
    int length;
};

// Auxiliar method
// Print data from patient
void print_patient(PatientNodeData patient, int index)
{
    printf("\n%3d° - %-50s - %-20s - %d", index, patient.name, patient.phone, patient.urgency);
}

// Auxiliar method
// Initialize the queue
void initialize_queue(Queue *Q)
{
    (*Q).start = NULL;
    (*Q).end = NULL;
    (*Q).length = 0;
}

// Auxiliar method
// Verify if queue is empty
int empty_queue(Queue *Q)
{
    if (Q == NULL || (*Q).length == 0)
        return 1;
    return 0;
}

// Auxiliar method
// Verify the size of the queue
int size_queue(Queue *Q)
{
    if (Q == NULL)
        return 0;
    return (*Q).length;
}

// Auxiliar method
// Read param value to use in the functions
void read_param(char query[50])
{
    printf("\nName of the patient: ");
    fgets(query, 50, stdin);
    query[strlen(query) - 1] = '\0';
}

// Create queue
Queue *create_queue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    if (Q != NULL)
        initialize_queue(Q);
    return Q;
}

// Free the memory allocated to the queue
void free_queue(Queue *Q)
{
    if (Q != NULL)
    {
        while ((*Q).start != NULL)
        {
            NodeData *N = (*Q).start;
            (*Q).start = (*(*Q).start).next;
            free(N);
        }
        free(Q);
    }
}

// Insert in the end of the queue
int insert_sorted(Queue *Q, char name[50], char phone[20], int urgency)
{
    if (Q == NULL)
        return 0;
    NodeData *N = (NodeData *)malloc(sizeof(NodeData));
    if (N == NULL)
        return 0;

    strcpy((*N).data.name, name);
    strcpy((*N).data.phone, phone);
    (*N).data.urgency = urgency;

    (*N).next = NULL;

    int position = 1;

    if (empty_queue(Q))
    {
        (*Q).start = N;
    }
    else
    {
        NodeData *previous, *actual = (*Q).start;

        while (actual != NULL && (*actual).data.urgency >= urgency)
        {
            previous = actual;
            actual = (*actual).next;
            position++;
        }

        if (actual == (*Q).start)
        {
            (*N).next = (*Q).start;
            (*Q).start = N;
        }
        else
        {
            (*N).next = (*previous).next;
            (*previous).next = N;
        }
    }

    if (position > (*Q).length)
        (*Q).end = N;

    (*Q).length++;

    printf("\nInserted %s in the %d° position\n", name, position);

    return 1;
}

// Remove element from the start of the queue
int remove_start(Queue *Q)
{
    if (empty_queue(Q))
        return 0;

    NodeData *N = (*Q).start;
    (*Q).start = (*N).next;
    (*Q).length--;
    if ((*Q).start == NULL)
        (*Q).end = NULL;
    free(N);

    return 1;
}

// Get first patient data from the element of the queue
PatientNodeData get_first(Queue *Q)
{
    return (*(*Q).start).data;
}

// Print all the queue data
int print_queue(Queue *Q)
{
    if (!empty_queue(Q))
    {
        printf("\nQueue:\n\n");
        printf("Start: %s\n", (*Q).start->data.name);
        printf("End: %s\n", (*Q).end->data.name);
        printf("Length: %d\n", (*Q).length);
        int index = 1;
        for (NodeData *N = (*Q).start; N != NULL; N = (*N).next)
        {
            print_patient((*N).data, index);
            index++;
        }
        printf("\n");
    }
    return 0;
}

void register_patient(Queue *Q)
{
    char name[50];
    char phone[20];
    int urgency;
    char urgencyStr[3];

    printf("\nPatient name: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';

    printf("Patient phone: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strlen(phone) - 1] = '\0';

    printf("Patient urgency: ");
    scanf("%3s", urgencyStr);
    urgency = atoi(urgencyStr);
    getchar();

    insert_sorted(Q, name, phone, urgency);
}

void search_patient(Queue *Q, char name[50])
{
    if (empty_queue(Q))
        printf("\nNot found!\n");
    else
    {
        int i, found = 0;

        NodeData *N = (*Q).start;
        for (i = 0; i < size_queue(Q); i++)
        {
            if (strcmp((*N).data.name, name) == 0)
            {
                found = 1;
                break;
            }
            N = (*N).next;
        }

        if (found)
        {
            print_patient((*N).data, i + 1);
            printf("\n");
        }
        else
            printf("\nNot found!\n");
    }
}

void get_next_patient(Queue *Q, FILE *file)
{
    if (!empty_queue(Q))
    {
        PatientNodeData firstPatient = get_first(Q);
        printf("\nNext patient:");
        print_patient(firstPatient, 1);
        fprintf(file, "%-50s - %-20s - %d\n", firstPatient.name, firstPatient.phone, firstPatient.urgency);
        remove_start(Q);
        printf("\n");
    }
}

void get_queue_size(Queue *Q)
{
    printf("\nQueue size: %d patients\n", size_queue(Q));
}

int main(int argc, char **argv)
{
    char option[3], query[50];
    int optionInt = 0;
    Queue *queue = create_queue();
    int param;

    FILE *file = fopen(argv[1], "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    fprintf(file, "%-50s - %-20s - %s\n", "Patient name", "Patient phone", "Patient urgency");

    printf("\e[1;1H\e[2J");

    while (optionInt != 5)
    {
        optionInt = 0;

        printf("\n1) Register patient\n");
        printf("2) Search patient\n");
        printf("3) Next patient\n");
        printf("4) Queue size\n");
        printf("5) Exit\n");

        while (!(optionInt >= 1 && optionInt <= 5))
        {
            printf("\nChoose an option: ");
            scanf("%3s", option);
            optionInt = atoi(option);
            getchar();
        }

        printf("\e[1;1H\e[2J");

        switch (optionInt)
        {
        case 1:
            register_patient(queue);
            break;
        case 2:
            read_param(query);
            search_patient(queue, query);
            break;
        case 3:
            get_next_patient(queue, file);
            break;
        case 4:
            get_queue_size(queue);
            print_queue(queue);
            break;
        case 5:
            free_queue(queue);
            fclose(file);
            printf("\nExiting...\n");
            break;
        default:
            break;
        }
    }

    return 0;
}