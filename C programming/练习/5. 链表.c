#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// struct and global variables
struct Patient {
    int ID;
    char* name;
    int severity;
    struct Patient* next;
};

int size = 0;

// function prototypes
struct Patient *initializeHead(void);
void freePatients(struct Patient *head);
void addPatient(struct Patient *head);
void treatPatient(struct Patient *head);
void removePatient(struct Patient *head);
void displayPatients(struct Patient *head);
int findPatient(struct Patient *head, int ID);

// main function
int main()
{
    struct Patient *Head = initializeHead();
    while(1){
        char command;
        scanf(" %c", &command);  
        
        switch (command)
        {
        case 'A':
            addPatient(Head);
            break;
        case 'T':
            treatPatient(Head);
            break;
        case 'R':
            removePatient(Head);
            break;
        case 'D':
            displayPatients(Head);
            break;
        case 'Q':
            freePatients(Head);
            exit(0);
        }
    }
}

// functions
struct Patient *initializeHead(void){
    struct Patient *Head = (struct Patient *)malloc(sizeof(struct Patient));
    if (Head == NULL){
        printf("Memory allocation failed: %s\n", strerror(errno));
        exit(1);
    }

    Head->ID = -1;
    Head->name = NULL;
    Head->severity = 9999;
    Head->next = NULL;

    return Head;
}

void addPatient(struct Patient *head){
    int ID;
    int severity;
    char name[100];

    scanf("%d %s %d", &ID, name, &severity);
    
    if (findPatient(head, ID)) {  
        printf("Error: Patient %d already exists.\n", ID);
    }
    else {
        struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
        
        if (newPatient == NULL) {
            printf("Memory allocation failed: %s\n", strerror(errno));
            return;
        }
        
        newPatient->ID = ID;
        newPatient->name = strdup(name);
        if (newPatient->name == NULL) {
            printf("Memory allocation failed: %s\n", strerror(errno));
            free(newPatient);
            return;
        }
        newPatient->severity = severity;
        
        // find a right spot
        struct Patient *current = head;

        while (current->next != NULL && current->next->severity >= severity) {
            current = current->next;
        }
        
        newPatient->next = current->next;
        current->next = newPatient;

        size++;
        printf("Patient %d Added.\n", ID);
    }
}

int findPatient(struct Patient *head, int ID) {
    struct Patient *current = head->next;
    
    while (current != NULL) {
        if (current->ID == ID) {
            return 1;  
        }
        current = current->next;
    }
    return 0;  
}

void treatPatient(struct Patient *head){
    if (size==0 || head->next == NULL)  
        printf("Queue is empty.\n");
    else{
        struct Patient *treatedPatient = head->next;
        struct Patient *successor = head->next->next;

        head->next = successor;
        int ID = treatedPatient->ID;
        free(treatedPatient->name);
        free(treatedPatient);

        printf("Patient %d Treated.\n", ID);
        size--;
    }
}

void removePatient(struct Patient *head){
    int ID;
    scanf(" %d", &ID);
    
    if(size==0 || findPatient(head, ID)==0){
        printf("Error: Patient %d not found.\n", ID);
    }
    else{
        struct Patient *current = head;
        struct Patient *next = current->next;
        while (next!= NULL) {
            if (next->ID == ID) {
                current->next = next->next;
                free(next->name);
                free(next);
                size--;
                printf("Patient %d Removed.\n", ID);
                return;
            }

            current = next;
            next = next->next;
        }
    }
}

void displayPatients(struct Patient *head){
    if (size==0){
        printf("Queue is empty.\n");
    }
    else{
        struct Patient *current = head->next;
        while(current!=NULL){
            printf("%s %d\n", current->name, current->severity);
            current = current->next;
        }
    }
}

void freePatients(struct Patient *head){
    struct Patient *current = head->next;
    struct Patient *next;

    while (current!=NULL){
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }

    free(head);
}
