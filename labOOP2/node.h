#ifndef NODE_H
#define NODE_H

#include <concepts>

template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};

template<typename T>
struct Node{
    T data;
    Node* right = nullptr;
    Node* left = nullptr;
    Node* parent = nullptr;

    Node(const T&);
};

#ifndef NODE_TPP
#define NODE_TPP

#include "node.tpp"

#endif

#endif // NODE_H
