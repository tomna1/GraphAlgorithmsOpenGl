#ifndef LINKED_LIST___H
#define LINKED_LIST___H

typedef struct LinkedListNode {
	void *data;
	struct LinkedListNode *next;
	struct LinkedListNode *previous;
} LinkedListNode;

typedef struct LinkedList {
	int size;
	LinkedListNode *head;
	LinkedListNode *lastNode;
} LinkedList;

// Creates a new linked list with default values and returns a pointer it.
LinkedList *createLinkedList();

// Pushes a new object onto the linked list. Will copy the data of what the
// pointer points to.
void push(LinkedList *list, void *data, size_t dataSize);

// Returns a pointer to the data in the specified index. If the index is greater than size, returns
// NULL.
void *getItem(LinkedList *list, int index);

// Removes the last data value of the linked list. If the list is empty, it will not do anything
void removeLast(LinkedList *list);

// Destroys the entire linked list
void destroyList(LinkedList *list);

// Prints the entire linked list. Needs a function to print out each individual
// data item in the linked list.
void printLinkedList(LinkedList *list, void (*fptr)(void *));

#endif

