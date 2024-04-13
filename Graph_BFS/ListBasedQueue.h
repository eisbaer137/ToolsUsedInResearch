#ifndef __LIST_BASED_QUEUE_H__

#define __LIST_BASED_QUEUE_H__

#include <iostream>
#include "LinkedList.h"

/*
template <typename T>
class Node
{
public:
    Node();
    Node(T data);
    Node(const Node<T>& rhs);
    Node<T>& operator=(const Node<T>& rhs);
    ~Node();

public:
    T mData;
    Node<T>* mNext;
};

template <typename T>
Node<T>::Node()
{
    this->mNext = nullptr;
}

template <typename T>
Node<T>::Node(T data) : mData(data)
{
    this->mNext = nullptr;
}

template <typename T>
Node<T>::Node(const Node<T>& rhs)
{
    this->mData = rhs.mData;
    this->mNext = rhs.mNext;
}

template <typename T>
Node<T>& Node<T>::operator=(const Node<T>& rhs)
{
    this->mData = rhs.mData;
    this->mNext = rhs.mNext;
    
    return *this;
}

template <typename T>
Node<T>::~Node()
{

}

*/
// -------------------------------------------

template <typename T>
class Queue
{
public:
    Queue();
    Queue(const Queue<T>& rhs) = delete;
    Queue<T>& operator=(const Queue<T>& rhs) = delete;
    ~Queue();

    bool IsQueueEmpty();
    void Enqueue(T data);
    T Dequeue();
    T Peek();

private:
    Node<T>* mFront;
    Node<T>* mRear;
};

template <typename T>
Queue<T>::Queue()
{
    this->mFront = nullptr;
    this->mRear = nullptr;
}

template <typename T>
Queue<T>::~Queue()
{   
    Node<T>* delNode;
    while(this->mFront != nullptr)
    {
        delNode = this->mFront;
        this->mFront = this->mFront->mNext;
        delete delNode;
    }
}

template <typename T>
bool Queue<T>::IsQueueEmpty()
{
    if(this->mFront == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
void Queue<T>::Enqueue(T data)
{
    Node<T>* newNode = new Node<T>(data);

    if(this->IsQueueEmpty())
    {
        this->mFront = newNode;
        this->mRear = newNode;
    }
    else
    {
        this->mRear->mNext = newNode;
        this->mRear = newNode;
    }    
}

template <typename T>
T Queue<T>::Dequeue()
{
    Node<T>* delNode;
    T retData;

    if(this->IsQueueEmpty())
    {
        std::cout << "This queue is empty..." << std::endl;
        exit(-1);
    }

    delNode = this->mFront;
    retData = delNode->mData;
    this->mFront = this->mFront->mNext;

    delete delNode;

    return retData;
}

template <typename T>
T Queue<T>::Peek()
{
    if(this->IsQueueEmpty())
    {
        std::cout << "This queue is empty..." << std::endl;
        exit(-1);
    }
    return this->mFront->mData;
}

#endif
