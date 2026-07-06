#include <stdlib.h>

#include <string.h>

#include "LinkedList.h"
#include "stringMemory.h"
#include "constants.h"


LinkedList* listCreate() {
    LinkedList* list = allocForList();
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void listPushBack(LinkedList* list, TableParams* params) {
    Node* node = allocForNode();
    node->data = *params;
    node->data.republic = allocForString(SIZE_BUFFER);
    strncpy(node->data.republic, params->republic, SIZE_BUFFER - 1);
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

Node* allocForNode() {return (Node*) malloc(sizeof(Node));}

LinkedList* allocForList() {return (LinkedList*) malloc(sizeof(LinkedList));}

void freeNode(Node* node) {free(node);}

void freeList(LinkedList* list) {
    Node *cur = list->head;

    while (cur != NULL) {
        Node *temp = cur;
        cur = cur->next;
        freeString(temp->data.republic);
        freeNode(temp);
    }

    free(list);
}

size_t getSizeList(const LinkedList* list) {
    return list->size;
}
