#include <stdio.h>
#include <stdlib.h>

typedef struct DlistNode{
    int item;
    struct DlistNode* next;
    struct DlistNode* prev;
}DlistNode;

typedef struct Dlist{
    DlistNode* head;
    DlistNode* tail;
}Dlist;

//Function Prototypes
void dll_insert_head(Dlist *dll, int value);
void dll_delete_head(Dlist *dll);
void dll_insert_tail(Dlist *dll, int value);
void dll_delete_tail(Dlist *dll);
void print_list_forward(Dlist *dll);
void print_list_backward(Dlist *dll);

int main (void){

    Dlist test_list = {NULL,NULL};

    //Tests
    printf("Adding numbers from 1 to 15\n");
    for (int i = 1; i <= 15; i++) {
        dll_insert_head(&test_list, i);
        print_list_forward(&test_list);        
    }
    
    printf("Deleting the first 5 numbers \n");
    for(int i = 0; i < 5; i++) {
        dll_delete_head(&test_list);
    } 

    print_list_forward(&test_list);

    printf("Deleting the last 5 numbers \n");
    for(int i = 0; i < 5; i++) {
        dll_delete_tail(&test_list);
    }

    print_list_backward(&test_list);

    printf("Inserting 5 numbers at the end \n");
    for (int i = 1; i <= 5; i++) {
        dll_insert_tail(&test_list, i);
    }

    print_list_forward(&test_list);
    
    return 0;
}

//Function Declarations

void dll_insert_head(Dlist *dll, int value) {
    DlistNode* new_node = (DlistNode*)malloc(sizeof(DlistNode));
    if (!new_node) return; //Allocation failed

    new_node->item = value;
    new_node->prev = NULL;
    new_node->next = dll->head;

    if (dll->head) {
        dll->head->prev = new_node;
    } else {

        dll->tail = new_node;
    }

    dll->head = new_node; 

}

void dll_delete_head(Dlist *dll) {
    if (dll->head != NULL) {
        DlistNode *to_delete = dll->head;
        dll->head = to_delete->next;
        if (dll->head) {
            dll->head->prev = NULL;
        } else {
            // List is now empty
            dll->tail = NULL;
        }
        free(to_delete);
    }
}

void dll_delete_tail(Dlist *dll) {
    if (!dll || !dll->tail) 
        return;

    DlistNode *to_delete = dll->tail;

    if (to_delete->prev) {
        dll->tail = to_delete->prev;
        dll->tail->next = NULL;
    } else {
        dll->head = dll->tail = NULL;
    }

    free(to_delete);
}

void dll_insert_tail(Dlist *dll, int value) {
    DlistNode* new_node = (DlistNode*)malloc(sizeof(DlistNode));
    if(!new_node) return;

    new_node->item = value;
    new_node->next = NULL;
    new_node->prev = dll->tail;

    dll->tail->next = new_node;
    dll->tail = new_node;
}

void print_list_forward(Dlist *dll) {
    DlistNode* current = dll->head;
    printf("Forward: ");
    while (current) {
        printf("%d ", current->item);
        current = current->next;
    }
    printf("\n");
}

void print_list_backward(Dlist *dll) {
    DlistNode* current = dll->tail;
    printf("Backward: ");
    while (current) {
        printf("%d ", current->item);
        current = current->prev;
    }
    printf("\n");
}

