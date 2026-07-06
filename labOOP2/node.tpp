#define NODE_TPP
#include "node.h"

template<typename T>
Node<T>::Node(const T& value): data(value) {}
