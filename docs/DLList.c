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

int main (void){



    return 0;
}

//Function Declarations

void dll_insert_head(Dlist *dll, int value){
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
