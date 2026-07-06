#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"

template<typename T>
class MySet;

template<typename T>
class Iterator {
public:
    Iterator();
    Iterator(const MySet<T>& set);
public:
    Iterator<T> next();
    T value();
    bool isEnd();
public:
    Iterator<T>& operator++();
    T& operator*();
    bool operator==(const Iterator<T>& other);
    bool operator!=(const Iterator<T>& other);
private:
    Node<T>* current = nullptr;
private:
    Node<T>* findMinNode(Node<T>* node);
    Node<T>* findBiggerParent(Node<T>* node) requires Comparable<T>;
};

#ifndef ITERATOR_TPP
#define ITERATOR_TPP

#include "iterator.tpp"

#endif

#endif // ITERATOR_H
