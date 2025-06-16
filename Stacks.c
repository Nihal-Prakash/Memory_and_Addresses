#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Stack structure using a dynamic array
typedef struct {
    int   *data;      // pointer to stack elements
    size_t top;       // index of next free slot (i.e. size of stack)
    size_t capacity;  // current capacity of the array
} Stack;


//=====================================================================//
//Function Prototypes

void stack_init(Stack *s, size_t capacity);
bool stack_is_empty(const Stack *s);
void stack_push(Stack *s, int value);
int stack_pop(Stack *s);
int stack_peek(const Stack *s);
void stack_free(Stack *s);

//=====================================================================//

int main(void) {
    Stack stk;
    stack_init(&stk, 4);

    // Push some values
    printf("Pushing: ");
    for (int i = 1; i <= 8; i++) {
        printf("%d ", i);
        stack_push(&stk, i);
    }
    printf("\n");

    // Peek at the top
    printf("Top element is: %d\n", stack_peek(&stk));

    // Pop all values
    printf("Popping: ");
    while (!stack_is_empty(&stk)) {
        printf("%d ", stack_pop(&stk));
    }
    printf("\n");

    stack_free(&stk);
    return 0;
}

//=====================================================================//
//Function Declaration

// Initialize the stack with a given initial capacity (must be > 0)
void stack_init(Stack *s, size_t capacity) {
    if (capacity == 0) capacity = 1;
    s->data = calloc(capacity, sizeof *s->data);
    if (!s->data) {
        fprintf(stderr, "Failed to allocate stack data\n");
        exit(EXIT_FAILURE);
    }
    s->top = 0;
    s->capacity = capacity;
}

// Return true if the stack is empty
bool stack_is_empty(const Stack *s) {
    return s->top == 0;
}

// Push a value onto the stack, resizing if necessary
void stack_push(Stack *s, int value) {
    if (s->top == s->capacity) {
        // double the capacity
        size_t new_cap = s->capacity * 2;
        int *new_data = realloc(s->data, new_cap * sizeof *s->data);
        if (!new_data) {
            fprintf(stderr, "Failed to reallocate stack data\n");
            exit(EXIT_FAILURE);
        }
        s->data     = new_data;
        s->capacity = new_cap;
    }
    s->data[s->top++] = value;
}

// Pop the top value; crashes if the stack is empty
int stack_pop(Stack *s) {
    if (stack_is_empty(s)) {
        fprintf(stderr, "Error: pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    return s->data[--s->top];
}

// Peek at the top value without popping; crashes if empty
int stack_peek(const Stack *s) {
    if (stack_is_empty(s)) {
        fprintf(stderr, "Error: peek from empty stack\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top - 1];
}

// Free all resources used by the stack
void stack_free(Stack *s) {
    free(s->data);
    s->data     = NULL;
    s->top      = s->capacity = 0;
}
