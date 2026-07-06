#define MYSET_TPP

#include "myset.h"
#include "iterator.h"

template<typename T>
MySet<T>::MySet() {}

template<typename T>
MySet<T>::MySet(const MySet<T>& set) {
    inorderToSet(set.root);
}

template<typename T>
MySet<T>::MySet(MySet<T>&& set) {
    root = set.root;
    length = set.length;

    set.root = nullptr;
    set.length = 0;
}

template<typename T>
MySet<T>::MySet(std::initializer_list<T> list) {
    for (T elem : list)
        add(elem);
}

template<typename T>
MySet<T>::~MySet() {
    clear();
}

template<typename T>
int MySet<T>::getLength() const {
    return length;
}

template<typename T>
bool MySet<T>::contains(const T& elem) const {
    bool flag = false;
    if (root)
        flag = containsNode(root, elem);
    return flag;
}

template<typename T>
void MySet<T>::add(const T& elem) {
    if (!root) {
        root = new Node<T>(elem);
        length++;
    } else
        addNode(root, elem);
}

template<typename T>
void MySet<T>::remove(const T& elem) {
    if (root)
        root = removeNode(root, elem);
}

template<typename T>
T* MySet<T>::toArray() const {
    T* array = new T[length];
    int index = 0;
    inorderToArray(root, array, index);
    return array;
}

template<typename T>
void MySet<T>::clear() {
    clearNode(root);
    root = nullptr;
    length = 0;
}

template<typename T>
Node<T>* MySet<T>::getRoot() const {
    return root;
}

template<typename T>
MySet<T>& MySet<T>::unionSets(const MySet<T>& set) {
    inorderToSet(set.root);
    return *this;
}

template<typename T>
MySet<T>& MySet<T>::intersection(const MySet<T>& set) {
    T* array = toArray();
    size_t sizeArray = length;
    for (size_t i = 0; i < sizeArray; ++i)
        if (!set.contains(array[i]))
            remove(array[i]);
    delete[] array;
    return *this;
}

template<typename T>
MySet<T>& MySet<T>::subtract(const MySet<T>& set) {
    T* array = toArray();
    size_t sizeArray = length;
    for (size_t i = 0; i < sizeArray; ++i)
        if (set.contains(array[i]))
            remove(array[i]);
    delete[] array;
    return *this;
}

template<typename T>
MySet<T>& MySet<T>::operator=(const MySet<T>& set) {
    if (this != &set) {
        clear();
        inorderToSet(set.root);
    }
    return *this;
}

template<typename T>
MySet<T>& MySet<T>::operator+=(const MySet<T>& set) {
    return unionSets(set);
}

template<typename T>
MySet<T>& MySet<T>::operator*=(const MySet<T>& set) {
    return intersection(set);
}

template<typename T>
MySet<T>& MySet<T>::operator/=(const MySet<T>& set) {
    return subtract(set);
}

template<typename _T>
std::ostream& operator<<(std::ostream& ostream, const MySet<_T>& set) {
    _T* array = set.toArray();
    size_t sizeArray = set.length;
    if (sizeArray > 0) {
        ostream << "{" << array[0];
        for (size_t i = 1; i < sizeArray; ++i)
            ostream << ", " << array[i];
        ostream << '}';
    } else
        ostream << "{ }";
    delete[] array;
    return ostream;
}

template<typename _T>
MySet<_T> operator+(const MySet<_T>& set1, const MySet<_T>& set2) {
    MySet<_T> setResult(set1);
    setResult.unionSets(set2);
    return setResult;
}

template<typename _T>
MySet<_T> operator*(const MySet<_T>& set1, const MySet<_T>& set2) {
    MySet<_T> setResult(set1);
    setResult.intersection(set2);
    return setResult;
}

template<typename _T>
MySet<_T> operator/(const MySet<_T>& set1, const MySet<_T>& set2) {
    MySet<_T> setResult(set1);
    setResult.subtract(set2);
    return setResult;
}

template<typename T>
Iterator<T> MySet<T>::iteratorBegin() {
    Iterator<T> iter(*this);
    return iter;
}

template<typename T>
Iterator<T> MySet<T>::iteratorEnd() {
    Iterator<T> iter;
    return iter;
}

template<typename T>
void MySet<T>::clearNode(Node<T>* node) {
    if (node) {
        clearNode(node->left);
        clearNode(node->right);
        delete node;
    }
}

template<typename T>
void MySet<T>::addNode(Node<T>* node, const T& elem) requires Comparable<T> {
    if (elem > node->data) {
        if (node->right)
            addNode(node->right, elem);
        else {
            node->right = new Node<T>(elem);
            node->right->parent = node;
            length++;
        }
    } else if (elem < node->data) {
        if (node->left)
            addNode(node->left, elem);
        else {
            node->left = new Node<T>(elem);
            node->left->parent = node;
            length++;
        }
    }
}

template<typename T>
void MySet<T>::inorderToArray(Node<T>* node, T* array, int& index) const {
    if (node) {
        inorderToArray(node->left, array, index);
        array[index++] = node->data;
        inorderToArray(node->right, array, index);
    }
}

template<typename T>
void MySet<T>::inorderToSet(Node<T>* node) {
    if (node) {
        inorderToSet(node->left);
        add(node->data);
        inorderToSet(node->right);
    }
}

template<typename T>
bool MySet<T>::containsNode(Node<T>* node, const T& elem) const requires Comparable<T>{
    bool flag = false;
    if (node->data == elem)
        flag = true;
    else {
        if (elem > node->data && node->right)
            flag = containsNode(node->right, elem);
        else if (elem < node->data && node->left)
            flag = containsNode(node->left, elem);
    }
    return flag;
}

template<typename T>
Node<T>* MySet<T>::removeNode(Node<T>* node, const T& elem) requires Comparable<T>{
    Node<T>* result = node;
    if (node) {
        if (elem > node->data) {
            node->right = removeNode(node->right, elem);
        } else if (elem < node->data) {
            node->left = removeNode(node->left, elem);
        } else {
            if (!node->left && !node->right) {
                delete node;
                result = nullptr;
                length--;
            } else if (!node->left) {
                result = node->right;
                result->parent = node->parent;
                delete node;
                length--;
            } else if (!node->right) {
                result = node->left;
                result->parent = node->parent;
                delete node;
                length--;
            } else {
                Node<T>* minNode = findMinNode(node->right);
                node->data = minNode->data;
                node->right = removeNode(node->right, minNode->data);
            }
        }
    }
    return result;
}

template<typename T>
Node<T>* MySet<T>::findMinNode(Node<T>* node) {
    Node<T>* result = node;
    if (node->left)
        result = findMinNode(node->left);
    return result;
}
