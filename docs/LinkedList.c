// linked_list.c
#include <stdio.h>
#include <stdlib.h>

// Node structure for singly linked list
typedef struct Node{
    int data;
    struct Node* next;
} Node;

//Function Prototypes
Node* ll_create(int data);
void ll_insert_head(Node** head_ref, int data);
void ll_insert_tail(Node** head_ref, int data);
void ll_delete(Node** head_ref, int key);
Node* ll_search(Node* head, int key);
void ll_displayList(Node* head);
void ll_free(Node** head_ref);


int main(void) {
    Node* head = NULL;

    // Insert elements at head
    ll_insert_head(&head, 3);
    ll_insert_head(&head, 2);
    ll_insert_head(&head, 1);
    printf("List after inserting 1, 2, 3 at head:\n");
    ll_displayList(head);

    // Insert elements at tail
    ll_insert_tail(&head, 4);
    ll_insert_tail(&head, 5);
    printf("List after inserting 4, 5 at tail:\n");
    ll_displayList(head);

    // Delete a node
    ll_delete(&head, 3);
    printf("List after deleting 3:\n");
    ll_displayList(head);

    // ll_search for a node
    Node* found = ll_search(head, 4);
    if (found) {
        printf("Found node with data: %d\n", found->data);
    } else {
        printf("Node not found\n");
    }

    // Free the list
    ll_free(&head);
    return 0;
}

// Create a new node with given data
Node* ll_create(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert a node at the beginning of the list
void ll_insert_head(Node** head_ref, int data) {
    Node* newNode = ll_create(data);
    newNode->next = *head_ref;
    *head_ref = newNode;
}

// Insert a node at the end of the list
void ll_insert_tail(Node** head_ref, int data) {
    Node* newNode = ll_create(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
    } else {
        Node* temp = *head_ref;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Delete the first occurrence of key in the list
void ll_delete(Node** head_ref, int key) {
    Node* temp = *head_ref;
    Node* prev = NULL;

    // If head node holds the key
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    // Search for the key
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not found
    if (temp == NULL) return;

    // Unlink the node and free it
    prev->next = temp->next;
    free(temp);
}

// Search for a node with given key
Node* ll_search(Node* head, int key) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == key) return current;
        current = current->next;
    }
    return NULL;
}

// Display the entire list
void ll_displayList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free all nodes in the list
void ll_free(Node** head_ref) {
    Node* current = *head_ref;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

