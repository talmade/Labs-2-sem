#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

#include "AppParams.h"

typedef struct Node {
    TableParams data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t size;
} LinkedList;

Node* allocForNode();
LinkedList* allocForList();
LinkedList* listCreate();
void listPushBack(LinkedList*, TableParams*);
void freeNode(Node*);
void freeList(LinkedList*);
size_t getSizeList(const LinkedList*);

#endif // LINKEDLIST_H
