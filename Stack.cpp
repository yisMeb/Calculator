#include <iostream>
using namespace std;
#include <stdlib.h>
#include "stack.h"


template <class T>
Stack<T>::Stack() {
    this->top = NULL;
    this->count = 0;
}

template <class T>
Stack<T>::~Stack() {
    this->empty();
}

template <class T>
void Stack<T>::push(T data) {
    stackNode<T>* p = new (nothrow) stackNode<T>;
    if (p == NULL)
        throw MemoryException();
    p->data = data;
    p->next = this->top;
    this->top = p;
    count++;
}

template <class T>
T Stack<T>::pop() {
    if (this->isEmpty())
        throw EmptyStackException();
    stackNode<T>* p = this->top;
    this->top = p->next;
    T item = p->data;
    delete p;
    count--;
    return item;
}

template <class T>
void Stack<T>::empty() {
    if (this->isEmpty())
        return;
    stackNode<T>* temp;
    while (top != NULL)
    {
        temp = top->next;
        delete top;
        top = temp;
    }
    count = 0;
}
