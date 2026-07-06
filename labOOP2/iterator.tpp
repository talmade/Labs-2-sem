#define ITERATOR_TPP

#include <stdexcept>

#include "iterator.h"

template<typename T>
Iterator<T>::Iterator() {}

template<typename T>
Iterator<T>::Iterator(const MySet<T>& set) {
    if (set.getRoot())
        current = findMinNode(set.getRoot());
}

template<typename T>
Iterator<T> Iterator<T>::next() {
    if (current) {
        if (current->right)
            current = findMinNode(current->right);
        else if (current->parent)
            current = findBiggerParent(current);
        else
            current = nullptr;
    }
    return *this;
}

template<typename T>
T Iterator<T>::value() {
    if (!current)
        throw std::out_of_range("Iterator is at end");
    return current->data;
}

template<typename T>
bool Iterator<T>::isEnd() {
    bool result = 0;
    if (!current)
        result = 1;
    return result;
}

template<typename T>
Iterator<T>& Iterator<T>::operator++() {
    next();
    return *this;
}

template<typename T>
T& Iterator<T>::operator*() {
    if (!current)
        throw std::out_of_range("Iterator is at end");
    return current->data;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) {
    bool result = 0;
    if (current == other.current)
        result = 1;
    return result;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) {
    bool result = 0;
    if (current != other.current)
        result = 1;
    return result;
}

template<typename T>
Node<T>* Iterator<T>::findMinNode(Node<T>* node) {
    Node<T>* result = node;
    if (node->left)
        result = findMinNode(node->left);
    return result;
}

template<typename T>
Node<T>* Iterator<T>::findBiggerParent(Node<T>* node) requires Comparable<T>{
    Node<T>* result = nullptr;
    if (node->parent) {
        if (node->data > node->parent->data)
            result = findBiggerParent(node->parent);
        else
            result = node->parent;
    }
    return result;
}
