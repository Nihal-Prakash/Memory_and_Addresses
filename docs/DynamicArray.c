/*
 * dynamic_array.c
 *
 * A basic implementation of a dynamic array in C.
 * Supports:
 *   - Initialization
 *   - Appending (push back)
 *   - Getting/setting elements
 *   - Removing an element at a given index
 *   - Freeing the array’s memory
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;         // Pointer to the elements
    size_t size;       // How many elements are currently stored
    size_t capacity;   // How many elements can be stored before needing resize
} DynamicArray;

//Funtion Prototypes

void initArray(DynamicArray *arr, size_t capacity);
void insertArray(DynamicArray *arr, int value);
int getAt(const DynamicArray *arr, size_t idx);
void setAt(DynamicArray *arr, size_t idx, int value);
void removeAt(DynamicArray *arr, size_t idx);
void freeArray(DynamicArray *arr);

int main(void) {
    DynamicArray arr;

    // 1) Initialize with a small capacity (say, 2)
    initArray(&arr, 2);
    printf("Initialized array with capacity = %zu\n", arr.capacity);

    // 2) Append a few values
    for (int i = 0; i < 8; i++) {
        insertArray(&arr, i * 10);
        printf("After inserting %d, size = %zu, capacity = %zu\n",
               i * 10, arr.size, arr.capacity);
    }

    // 3) Print all elements
    printf("\nCurrent elements:\n");
    for (size_t i = 0; i < arr.size; i++) {
        printf("  arr[%zu] = %d\n", i, getAt(&arr, i));
    }

    // 4) Modify an element
    printf("\nSetting arr[3] = 1234\n");
    setAt(&arr, 3, 1234);
    printf("  arr[3] is now %d\n", getAt(&arr, 3));

    // 5) Remove element at index 5
    printf("\nRemoving element at index 5 (value = %d)\n", getAt(&arr, 5));
    removeAt(&arr, 5);
    printf("After removal, size = %zu, capacity = %zu\n", arr.size, arr.capacity);

    // 6) Print elements again
    printf("\nElements after removal:\n");
    for (size_t i = 0; i < arr.size; i++) {
        printf("  arr[%zu] = %d\n", i, getAt(&arr, i));
    }

    // 7) Clean up
    freeArray(&arr);
    printf("\nArray freed. size = %zu, capacity = %zu\n",
           arr.size, arr.capacity);

    return 0;
}

//Function Declaration
void initArray(DynamicArray *arr, size_t capacity) {
    if (capacity == 0) {
        capacity = 1;  // Ensure we always have space for at least one element
    }
    arr->data = calloc(capacity, sizeof(int));
    if (!arr->data) {
        fprintf(stderr, "Error: calloc failed in initArray\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = capacity;
}

void insertArray(DynamicArray *arr, int value) {
    // If we've filled up capacity, double the buffer size
    if (arr->size == arr->capacity) {
        size_t newCapacity = arr->capacity * 2;
        arr->data = realloc(arr->data, sizeof(int) * newCapacity);
        arr->capacity = newCapacity;
    }

    // Add the new value at the end
    arr->data[arr->size] = value;
    arr->size++;
}

int getAt(const DynamicArray *arr, size_t idx) {
    // In production, check: idx < arr->size
    return arr->data[idx];
}

void setAt(DynamicArray *arr, size_t idx, int value) {
    // In production, check: idx < arr->size
    arr->data[idx] = value;
}

void removeAt(DynamicArray *arr, size_t idx) {
    // In production, check: idx < arr->size
    // Shift all elements after idx one position to the left
    for (size_t i = idx; i + 1 < arr->size; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    // Optionally: shrink capacity if size is much smaller than capacity
    // (Not implemented here, but you could halve capacity when size < capacity/4)
}

void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}
