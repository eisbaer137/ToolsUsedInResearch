#ifndef __BINARY_TREE2_H__
#define __BINARY_TREE2_H__

#include <iostream>

template <typename U>
class Action
{
public:
    void operator()(const U& param)
    {
        std::cout << param;
    }
};

template <typename T>
class BTreeNode
{
public:	
    BTreeNode();
    BTreeNode(T data);

    BTreeNode(const BTreeNode<T>& rhs);
    BTreeNode<T>& operator=(const BTreeNode<T>& rhs);
    ~BTreeNode();

    T GetData();
    void SetData(T data);

    BTreeNode<T>* GetLeftSubTree();
    BTreeNode<T>* GetRightSubTree();

    void MakeLeftSubTree(BTreeNode<T>* sub);
    void MakeRightSubTree(BTreeNode<T>* sub);

    template <typename U>
    friend void DeleteTree(BTreeNode<U>* node);

    template <typename U>
    friend void PreorderTraverse(BTreeNode<U>* node, Action<U>& action);

    template <typename U>
    friend void InorderTraverse(BTreeNode<U>* node, Action<U>& action);

    template <typename U>
    friend void PostorderTraverse(BTreeNode<U>* node, Action<U>& action);


    BTreeNode<T>* RemoveLeftSubTree();
    BTreeNode<T>* RemoveRightSubTree();

    void ChangeLeftSubTree(BTreeNode<T>* sub);
    void ChangeRightSubTree(BTreeNode<T>* sub);

private:
    T mData;
    BTreeNode<T>* mLeft;
    BTreeNode<T>* mRight;
};

template <typename T>
BTreeNode<T>::BTreeNode()
{
    this->mLeft = nullptr;
    this->mRight = nullptr;
}
template <typename T>
BTreeNode<T>::BTreeNode(T data)
{
    this->mData = data;
    this->mLeft = nullptr;
    this->mRight = nullptr;
}

template <typename T>
BTreeNode<T>::BTreeNode(const BTreeNode<T>& rhs)
{
    this->mData = rhs.mData;
    this->mLeft = rhs.mLeft;
    this->mRight = rhs.mRight;
}

template <typename T>
BTreeNode<T>& BTreeNode<T>::operator=(const BTreeNode<T>& rhs)
{
    if(this != nullptr)
    {
        DeleteTree(this);
    }
    this->mData = rhs.mData;
    this->mLeft = rhs.mLeft;
    this->mRight = rhs.mRight;
}


template <typename T>
BTreeNode<T>::~BTreeNode()
{

}

template <typename T>
T BTreeNode<T>::GetData()
{
    return mData;
}

template <typename T>
void BTreeNode<T>::SetData(T data)
{
    this->mData = data;
}

template <typename T>
void DeleteTree(BTreeNode<T>* node)
{
    if(node == nullptr)
    {
        return;
    }
    DeleteTree(node->mLeft);
    DeleteTree(node->mRight);
    //std::cout << "node deleted..." << std::endl;
    delete node;
}

template <typename T>
BTreeNode<T>* BTreeNode<T>::GetLeftSubTree()
{
    return this->mLeft;
}

template <typename T>
BTreeNode<T>* BTreeNode<T>::GetRightSubTree()
{
    return this->mRight;
}

template <typename T>
void BTreeNode<T>::MakeLeftSubTree(BTreeNode<T>* sub)
{
    if(this->mLeft != nullptr)
       delete(this->mLeft);
    this->mLeft = sub;
}

template <typename T>
void BTreeNode<T>::MakeRightSubTree(BTreeNode<T>* sub)
{
    if(this->mRight != nullptr)
        delete(this->mRight);

    this->mRight = sub;
}

template <typename T>
void PreorderTraverse(BTreeNode<T>* node, Action<T>& action)
{
    if(node == nullptr)
    {
        return;
    }
    action(node->mData);
    PreorderTraverse(node->mLeft, action);
    PreorderTraverse(node->mRight, action);
}

template <typename T>
void InorderTraverse(BTreeNode<T>* node, Action<T>& action)
{
    if(node == nullptr)
    {
        return;
    }
    InorderTraverse(node->mLeft, action);
    action(node->mData);
    InorderTraverse(node->mRight, action);
}

template <typename T>
void PostorderTraverse(BTreeNode<T>* node, Action<T>& action)
{
    if(node == nullptr)
    {
        return;
    }
    PostorderTraverse(node->mLeft, action);
    PostorderTraverse(node->mRight, action);
    action(node->mData);
}

template <typename T>
BTreeNode<T>* BTreeNode<T>::RemoveLeftSubTree()
{
    BTreeNode<T>* delNode;

    if(this != nullptr)
    {
        delNode = this->mLeft;
        this->mLeft = nullptr;
    }

    return delNode;
}

template <typename T>
BTreeNode<T>* BTreeNode<T>::RemoveRightSubTree()
{
    BTreeNode<T>* delNode;

    if(this != nullptr)
    {
        delNode = this->mRight;
        this->mRight = nullptr;
    }

    return delNode;
}

template <typename T>
void BTreeNode<T>::ChangeLeftSubTree(BTreeNode<T>* sub)
{
    this->mLeft = sub;
}

template <typename T>
void BTreeNode<T>::ChangeRightSubTree(BTreeNode<T>* sub)
{
    this->mRight = sub;
}


#endif
