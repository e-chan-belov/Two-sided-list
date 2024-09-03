#ifndef Header_h
#define Header_h
#include <iostream>

template <class T>
class Cell {
public:
    Cell* left;
    Cell* right;
    T memory;
};


template <class T>
class List {
private:
    Cell<T>* needle;
    std::size_t position;
public:
    List(std::size_t size = 1);
    List(const List& obj);
    List(T* pointer, std::size_t size);
    
    ~List();
    
    T& operator[](std::size_t index);
    const T operator[](std::size_t index) const;
    
    T push_back(T element);
    T push_front(T element);
    
    T pop(std::size_t index);
    std::size_t find(T element);
};

template <class T>
List<T>::List(std::size_t size) {
    if (size == 0) {
        throw "IMPOSSIBLE SIZE!";
    }
    
    needle = new Cell<T>;
    needle->right = NULL;
    for (position = size - 1; position > 0; position--) {
        needle->left = new Cell<T>;
        needle->left->right = needle;
        needle = needle->left;
    }
    needle->left = NULL;
}

template <class T>
List<T>::List(const List& obj) {
    Cell<T>* centre = new Cell<T>;
    needle = centre;
    Cell<T>* obj_pointer = obj.needle;
    
    while (obj_pointer->right != NULL) {
        needle->right = new Cell<T>;
        needle->memory = obj_pointer->memory;
        
        needle->right->left = needle;
        
        needle = needle->right;
        obj_pointer = obj_pointer->right;
    }
    needle->right = NULL;
    needle->memory = obj_pointer->memory;
    
    needle = centre;
    obj_pointer = obj.needle;
    while (obj_pointer->left != NULL) {
        needle->left = new Cell<T>;
        needle->memory = obj_pointer->memory;
        
        needle->left->right = needle;
        
        needle = needle->left;
        obj_pointer = obj_pointer->left;
    }
    needle->left = NULL;
    needle->memory = obj_pointer->memory;
    
    position = 0;
}

template <class T>
List<T>::List(T* pointer, std::size_t size) {
    needle = new Cell<T>;
    needle->right = NULL;
    for (position = size - 1; position > 0; position--) {
        needle->memory = pointer[position];
        
        needle->left = new Cell<T>;
        needle->left->right = needle;
        needle = needle->left;
    }
    needle->memory = pointer[position];
    needle->left = NULL;
}

template <class T>
List<T>::~List() {
    Cell<T>* centre = needle->left;
    Cell<T>* next;
    while (needle != NULL) {
        next = needle->right;
        delete needle;
        needle = next;
    }
    needle = centre;
    while (needle != NULL) {
        next = needle->left;
        delete needle;
        needle = next;
    }
}

template <class T>
T& List<T>::operator[](std::size_t index) {
    char flag = index > position ? 1 : -1;
    for (; index != position; position += flag) {
        if (needle == NULL) {
            throw "INCORRECT INDEX!";
        }
        if (flag == 1) {
            needle = needle->right;
        } else {
            needle = needle->left;
        }
    }
    return needle->memory;
}

template <class T>
const T List<T>::operator[](std::size_t index) const {
    char flag = index > position ? 1 : -1;
    for (; index != position; position += flag) {
        if (needle == NULL) {
            throw "INCORRECT INDEX!";
        }
        if (flag == 1) {
            needle = needle->right;
        } else {
            needle = needle->left;
        }
    }
    return needle->memory;
}

template <class T>
T List<T>::push_back(T element) {
    while (needle->left != NULL) {
        needle = needle->left;
    }
    needle->left = new Cell<T>;
    needle->left->right = needle;
    needle = needle->left;
    
    needle->memory = element;
    needle->left = NULL;
    position = 0;
    return element;
}

template <class T>
T List<T>::push_front(T element) {
    for (; needle->right != NULL; position++) {
        needle = needle->right;
    }
    needle->right = new Cell<T>;
    needle->right->left = needle;
    needle = needle->right;
    
    needle->memory = element;
    needle->right = NULL;
    return element;
}

#endif /* Header_h */
