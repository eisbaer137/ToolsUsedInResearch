#ifndef __LINKED_LIST_H__

#define __LINKED_LIST_H__

#include <iostream>


// Node class using class template
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
    Node<T>* next()
    {
        return this->mNext;
    }

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
Node<T>::Node(T data)
{
    this->mData = data;
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


/*--------------------------------------------------------*/

// Linked List ADT Class
template <typename T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList<T>& rhs) = delete;
    LinkedList<T>& operator=(const LinkedList<T>& rhs) = delete;
    ~LinkedList();

public:
    void LInsert(T data);
    T LRemove();
    size_t LCount();
    void ShowElements();
    void RemoveElement(T data);
    //void SetSortMethod(int (*comp)(T d1, T d2));

public:
    void LDestroy();
    bool LFirst(T& data);
    bool LNext(T& data);

private:
    Node<T>* mHead;
    Node<T>* mCur;
    Node<T>* mPrev;
    size_t numOfElements;
    //bool (*comp)(T d1, T d2);
};

template <typename T>
LinkedList<T>::LinkedList()
    : mCur(nullptr), mPrev(nullptr), numOfElements(0)
{
    // To set a dummy node
    this->mHead = new Node<T>();
}

/*
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
    this->mHead = rhs.mHead;
    this->mCur = rhs.mCur;
    this->mPrev = rhs.mPrev;
    this->numOfElements = rhs.numOfElements;

    return *this;
}
*/

template <typename T>
LinkedList<T>::~LinkedList()
{
    this->LDestroy();
}

template <typename T>
void LinkedList<T>::LInsert(T data)
{
    Node<T>* newNode = new Node<T>(data);
    newNode->mNext = this->mHead->mNext;
    this->mHead->mNext = newNode;

    (this->numOfElements)++; 
}

template <typename T>
bool LinkedList<T>::LFirst(T& data)
{
    if(this->mHead->mNext == nullptr)
    {
        return false;
    }
    this->mPrev = this->mHead;
    this->mCur = this->mHead->mNext;
    data = this->mCur->mData;

    return true;
}

template <typename T>
bool LinkedList<T>::LNext(T& data)
{
    if(this->mCur->mNext == nullptr)
    {
        return false;
    }
    this->mPrev = this->mCur;
    this->mCur = this->mCur->mNext;
    data = this->mCur->mData;

    return true;
}

template <typename T>
T LinkedList<T>::LRemove()
{
    Node<T>* tempNode = this->mCur;
    T tempData = tempNode->mData;

    this->mPrev->mNext = this->mCur->mNext;
    this->mCur = this->mPrev;

    delete tempNode;
    (this->numOfElements)--;

    return tempData;
}

template <typename T>
void LinkedList<T>::LDestroy()
{
    Node<T>* tempNode;
    T tempData;
    const size_t num = this->numOfElements;

    if(this->mHead->mNext != nullptr)
    {
        this->mCur = this->mHead->mNext;
        for(size_t i=0; i < num; ++i)
        {
            tempNode = this->mCur;
            this->mCur  = this->mCur->mNext;
            //printf("%p \n", tempNode);
            delete tempNode;
            (this->numOfElements)--;
        }
    }
    //printf("dummy node addr : %p \n", this->mHead);
    delete this->mHead;
    this->mPrev = nullptr;
    this->mHead = nullptr;
    this->mCur = nullptr;
    if(this->numOfElements != 0)
    {
        std::cout << "something went wrong...the number of elements is not zero..." << std::endl;
    }
}

template <typename T>
void LinkedList<T>::ShowElements()
{
    if(this->mHead == nullptr)
        return;

    T data;
    if(LFirst(data))
    {
        std::cout << data << std::endl;

        while(LNext(data))
        {
            std::cout << data << std::endl;
        }
    }
}

template <typename T>
void LinkedList<T>::RemoveElement(T data)
{
    T val;
    bool det = false;

    if(LFirst(val))
    {
        if(val == data)
        {
            LRemove();
            det = true;
        }
        while(LNext(val))
        {
            if(val == data)
            {
                LRemove();
                det = true;
            }
        }
    }
    if(det == false)
        std::cout << "No such elements..." << std::endl;
    else if(det == true)
        std::cout << "Removing elements done..." << std::endl;

}

template <typename T>
size_t LinkedList<T>::LCount()
{
    return this->numOfElements;
}


#endif
