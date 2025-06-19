#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int   *data;     // buffer array
    size_t head;     // index of next element to dequeue
    size_t tail;     // index of next slot to enqueue
    size_t size;     // current number of elements
    size_t capacity; // total buffer capacity
} Queue;

//=====================================================================//
//Function Prototypes

void q_init(Queue *q, size_t cap);
void q_free(Queue *q);
bool q_is_empty(const Queue *q);
size_t q_size(const Queue *q);
static void q_resize(Queue *q, size_t new_cap);
void q_enqueue(Queue *q, int value);
int q_dequeue(Queue *q);
int q_peek(const Queue *q);

//=====================================================================//

int main(void) {
    Queue q;
    q_init(&q, 2);

    // enqueue 0..4
    for (int i = 0; i < 5; i++) {
        printf("Enqueue %d\n", i);
        q_enqueue(&q, i);
    }

    printf("Queue size: %zu\n", q_size(&q));
    printf("Front element: %d\n", q_peek(&q));

    // dequeue all
    while (!q_is_empty(&q)) {
        int v = q_dequeue(&q);
        printf("Dequeue %d\n", v);
    }

    q_free(&q);
    return 0;
}

//=====================================================================//
//Function Decalarations

// Initialize queue with given initial capacity (must be ≥1)
void q_init(Queue *q, size_t cap) {
    if (cap < 1) cap = 1;
    q->data = calloc(cap, sizeof(int));
    if (!q->data) {
        fprintf(stderr, "Error: calloc failed in q_init\n");
        exit(EXIT_FAILURE);
    }
    q->head = q->tail = q->size = 0;
    q->capacity = cap;
}

// Free queue’s internal buffer
void q_free(Queue *q) {
    free(q->data);
    q->data = NULL;
    q->capacity = q->size = q->head = q->tail = 0;
}

// Return true if queue is empty
bool q_is_empty(const Queue *q) {
    return q->size == 0;
}

// Return number of elements in queue
size_t q_size(const Queue *q) {
    return q->size;
}

// Resize buffer to new capacity (≥ current size)
void q_resize(Queue *q, size_t new_cap) {
    int *new_data = calloc(new_cap, sizeof(int));
    if (!new_data) {
        fprintf(stderr, "Error: calloc failed in q_resize\n");
        exit(EXIT_FAILURE);
    }
    // Copy elements in order from head
    for (size_t i = 0; i < q->size; i++) {
        new_data[i] = q->data[(q->head + i) % q->capacity];
    }
    free(q->data);
    q->data     = new_data;
    q->capacity = new_cap;
    q->head     = 0;
    q->tail     = q->size;
}

// Enqueue value at tail; resize if full
void q_enqueue(Queue *q, int value) {
    if (q->size == q->capacity) {
        q_resize(q, q->capacity * 2);
    }
    q->data[q->tail] = value;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
}

// Dequeue and return front value; error if empty
int q_dequeue(Queue *q) {
    if (q_is_empty(q)) {
        fprintf(stderr, "Error: dequeue from empty queue\n");
        exit(EXIT_FAILURE);
    }
    int val = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    // Optionally shrink buffer when too empty
    if (q->size > 0 && q->size == q->capacity / 4) {
        q_resize(q, q->capacity / 2);
    }
    return val;
}

// Peek at front without removing; error if empty
int q_peek(const Queue *q) {
    if (q_is_empty(q)) {
        fprintf(stderr, "Error: peek on empty queue\n");
        exit(EXIT_FAILURE);
    }
    return q->data[q->head];
}
