#include <stdlib.h>
#include <stdio.h>

#include "LinkedList.h"

LinkedList *createLinkedList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = NULL;
    list->lastNode = NULL;
    return list;
}


void push(LinkedList *list, void *data, size_t dataSize) {
    // Allocate memory for node 
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newNode->data = malloc(dataSize);
    newNode->next = NULL;
    newNode->previous = list->lastNode;

    // Copy contents of new_data to newly allocated memory. 
    // Assumption: char takes 1 byte. 
    for (int i = 0; i < dataSize; i++) {
        *((char *)(newNode->data) + i) = *((char *)(data)+i);
    }

    if (list->head == NULL) {
        list->head = newNode;
        list->lastNode = newNode;
    }
    else {
        list->lastNode->next = newNode;
        list->lastNode = newNode;
    }
    list->size++;
}


// Returns a pointer to the data stored in the node.
void *getItem(LinkedList *list, int index) {
    if (index + 1 > list->size) {
        return NULL;
    }

    LinkedListNode *node = list->head;

    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    return node->data;
}


// Remove the last node of the linked list.
void removeLast(LinkedList *list) {
    if (list->lastNode == NULL) {
        return;
    }

    LinkedListNode *lastNodetemp = list->lastNode;

    if (list->size > 1) {
        list->lastNode->previous->next = NULL;
        list->lastNode = list->lastNode->previous;
    }
    else if (list->size == 1) {
        list->head = NULL;
        list->lastNode = NULL;
    }
    free(lastNodetemp);
    list->size--;
}

// Remove everything from the list.
void destroyList(LinkedList *list) {
    while (list->size > 0) {
        removeLast(list);
    }
    free(list);
}


// Print the LinkedList given the list and a function to print the data
// store in the linked list.
void printLinkedList(LinkedList *list, void (*fptr)(void *)) {
    if (list->head == NULL) {
        return;
    }
    LinkedListNode *node = list->head;
    while (node != NULL)
    {
        (*fptr)(node->data);
        node = node->next;
    }
    printf("\n");
}
