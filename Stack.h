#pragma once

template <class T>
struct stackNode
{
    T data;
    stackNode* next;
};
#include <exception>
struct MemoryException : public std::exception
{
    const char* what()
    {
        return "Unable to allocate memory!";
    }
};

struct EmptyStackException : public std::exception
{
    const char* what()
    {
        return "Popping an empty stack!";
    }
};

template <class T>
class Stack
{
public:
    Stack();
    virtual ~Stack();
    void push(T data);
    T pop();
    T peep()
    {
        if (this->isEmpty())
            throw EmptyStackException();
        return this->top->data;
    }
    bool isEmpty()
    {
        return count == 0;
    }
    int getCount()
    {
        return count;
    }
    void empty();

private:
    stackNode<T>* top;
    int count;
};