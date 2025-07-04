#include <stdio.h>
#include <stdlib.h>

typedef struct DlistNode{
    int data;
    struct DlistNode* next;
    struct DlistNode* prev;
}DlistNode;

typedef struct Dlist {
    DlistNode* sentinel;
    size_t size;
}Dlist;

void dll_init(Dlist *dll) {
    dll->sentinel = malloc(sizeof(DlistNode));
    if (!dll->sentinel) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    dll->sentinel->next = dll->sentinel;
    dll->sentinel->prev = dll->sentinel;
    dll->size = 0;
}

