#ifndef __ARRAY_BASED_STACK_H__
#define __ARRAY_BASED_STACK_H__

#include <iostream>
#include <vector>

template <typename T>
class Stack
{
public:
    Stack();
    Stack(const Stack& rhs) = delete;
    Stack<T>& operator=(const Stack& src) = delete;
    ~Stack();
    bool IsStackEmpty();
    void SPush(T data);
    T SPop();
    T SPeek();

private:
    std::vector<T> arrayStack;
    int topIndex;
};

template <typename T>
Stack<T>::Stack()
{
    topIndex = -1;
}

template <typename T>
Stack<T>::~Stack()
{
    
}

template <typename T>
bool Stack<T>::IsStackEmpty()
{
    if(this->topIndex == -1)
        return true;
    else    
        return false;
}

template <typename T>
void Stack<T>::SPush(T data)
{
    this->arrayStack.push_back(data);
    (this->topIndex)++;
}

template <typename T>
T Stack<T>::SPop()
{
    int idx;
    if(this->IsStackEmpty())
    {
        std::cout << "Stack is empty...." << std::endl;
        exit(-1);
    }
    idx = this->topIndex;
    (this->topIndex)--;

    return this->arrayStack[idx];
}

template <typename T>
T Stack<T>::SPeek()
{
    if(this->IsStackEmpty())
    {
        std::cout << "Stack is empty..." << std::endl;
        exit(-1);
    }

    return this->arrayStack[this->topIndex];
}




#endif
