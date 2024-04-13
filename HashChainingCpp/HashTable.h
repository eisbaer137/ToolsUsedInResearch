#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <iostream>
#include "LinkedList.h"

#define TBL_MAX 100

typedef unsigned int HashMethod(unsigned int key);

template <typename T>
struct Pair
{
    unsigned int mKey;
    T mData;
};


template <typename T>
struct HashTable
{
    HashTable(HashMethod* ftn)
    {
        hashFtn = ftn;
    }
    HashTable(const HashTable& rhs) = delete;
    HashTable<T>& operator=(const HashTable& src) = delete;
    ~HashTable()
    {

    }

    void TInsert(unsigned int key, T data);

    bool TSearch(unsigned int key, T& data);

    bool TDelete(unsigned int key, T& data); 

    unsigned int GetHashValue(unsigned int key)
    {
        return hashFtn(key);
    }
    LinkedList<Pair<T>> mTable[TBL_MAX];
    HashMethod* hashFtn;    
};

template <typename T>
void HashTable<T>::TInsert(unsigned int key, T data)
{
    Pair<T> elem = {key, data};
    unsigned int hVal = GetHashValue(key);
    T temp;
    if(TSearch(key, temp))
    {
        std::cout << "Error : key you entered already exists in the table..." << std::endl;
        return;
    }
    else
    {
        mTable[hVal].LInsert(elem);
    }
}

template <typename T>
bool HashTable<T>::TSearch(unsigned int key, T& data)
{
    unsigned int hVal = GetHashValue(key);
    Pair<T> elem;

    if(mTable[hVal].LFirst(elem))
    {
        if(elem.mKey == key)
        {
            data = elem.mData;
            return true;
        }
        else
        {
            while(mTable[hVal].LNext(elem))
            {
                if(elem.mKey == key)
                {
                    data = elem.mData;
                    return true;
                }
            }
        }
    } 

    return false;
}

template <typename T>
bool HashTable<T>::TDelete(unsigned int key, T& data)
{
    unsigned int hVal = GetHashValue(key);
    Pair<T> elem;

    if(mTable[hVal].LFirst(elem))
    {
        if(elem.mKey == key)
        {
            data = elem.mData;
            mTable[hVal].LRemove();
            return true;
        }
        else
        {
            while(mTable[hVal].LNext(elem))
            {
                if(elem.mKey == key)
                {
                    data = elem.mData;
                    mTable[hVal].LRemove();
                    return true;
                }
            }
        }
    }
    return false;
}

#endif
