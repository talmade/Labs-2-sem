#ifndef ITERATOR_H
#define ITERATOR_H

#include "LinkedList.h"

struct Iterator{
    Node* current;
};

Iterator iteratorCreate(const LinkedList*);
int iteratorHasNext(const Iterator*);
TableParams* iteratorNext(Iterator*);

#endif // ITERATOR_H
