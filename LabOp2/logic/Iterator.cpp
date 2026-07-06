#include "Iterator.h"

Iterator iteratorCreate(const LinkedList* list) {
    Iterator iterator;
    iterator.current = list->head;

    return iterator;
}

int iteratorHasNext(const Iterator* iterator) {return iterator->current != NULL;}

TableParams* iteratorNext(Iterator* iterator) {
    TableParams* data = &iterator->current->data;
    iterator->current = iterator->current->next;

    return data;
}

