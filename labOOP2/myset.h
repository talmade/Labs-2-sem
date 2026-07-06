#ifndef MYSET_H
#define MYSET_H

#include <initializer_list>
#include <iostream>

#include "iterator.h"
#include "node.h"


template<typename T>
class MySet {
public:
    MySet();
    MySet(const MySet<T>& set);
    MySet(MySet<T>&& set);
    explicit MySet(std::initializer_list<T> list);
    ~MySet();
public:
    int getLength() const;
    bool contains(const T& elem) const;
    void add(const T& elem);
    void remove(const T& elem);
    T* toArray() const;
    void clear();
    Node<T>* getRoot() const;
public:
    MySet<T>& unionSets(const MySet<T>& set);
    MySet<T>& intersection(const MySet<T>& set);
    MySet<T>& subtract(const MySet<T>& set);
public:
    MySet<T>& operator=(const MySet<T>& set);
    MySet<T>& operator+=(const MySet<T>& set);
    MySet<T>& operator*=(const MySet<T>& set);
    MySet<T>& operator/=(const MySet<T>& set);
public:
    template<typename _T>
    friend std::ostream& operator<<(std::ostream& ostream, const MySet<_T>& set);

    template<typename _T>
    friend MySet<_T> operator+(const MySet<_T>& set1, const MySet<_T>& set2);

    template<typename _T>
    friend MySet<_T> operator*(const MySet<_T>& set1, const MySet<_T>& set2);

    template<typename _T>
    friend MySet<_T> operator/(const MySet<_T>& set1, const MySet<_T>& set2);
public:
    Iterator<T> iteratorBegin();
    Iterator<T> iteratorEnd();
private:
    Node<T>* root = nullptr;
    int length = 0;
private:
    void clearNode(Node<T>* node);
    void addNode(Node<T>* node, const T& elem) requires Comparable<T>;
    void inorderToArray(Node<T>* node, T* arr, int& index) const;
    void inorderToSet(Node<T>* node);
private:
    bool containsNode(Node<T>* node, const T& elem) const requires Comparable<T>;
private:
    Node<T>* removeNode(Node<T>* node, const T& elem) requires Comparable<T>;
    Node<T>* findMinNode(Node<T>* node);
};

#ifndef MYSET_TPP
#define MYSET_TPP

#include "myset.tpp"

#endif

#endif // MYSET_H
