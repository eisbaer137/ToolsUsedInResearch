#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__


#include "BinaryTree2.h"
#include <iostream>

template <typename T>
void BSTMakeAndInit(BTreeNode<T>** ppRoot)
{
    *ppRoot = nullptr;
}


template <typename T>
T BSTGetNodeData(BTreeNode<T>* bst)
{
    return bst->GetData();
}

template <typename T>
void BSTInsertData(BTreeNode<T>** ppRoot, T data)
{
    BTreeNode<T>* pNode = nullptr;          // parent node
    BTreeNode<T>* cNode = *ppRoot;          // current node
    BTreeNode<T>* nNode = nullptr;          // new node

    while(cNode != nullptr)
    {
        if(data == cNode->GetData())
        {
            return;
        }

        pNode = cNode;

        if(cNode->GetData() > data)
            cNode = cNode->GetLeftSubTree();
        else
            cNode = cNode->GetRightSubTree();
    }

    nNode = new BTreeNode<T>(data);          // make a new node

    if(pNode != nullptr)
    {
        if(data < pNode->GetData())
        {
            pNode->MakeLeftSubTree(nNode);
        }
        else
        {
            pNode->MakeRightSubTree(nNode);
        }
    }
    else        // if the new node is supposed to be the root node
    {
        *ppRoot = nNode;
    }
}

template <typename T>
BTreeNode<T>* BSTSearchData(BTreeNode<T>* bst, T target)
{
    BTreeNode<T>* cNode = bst;              // current node
    T cd;                                   // current data

    while(cNode != nullptr)
    {
        cd = cNode->GetData();

        if(target == cd)
        {
            return cNode;
        }
        else if(target < cd)
        {
            cNode = cNode->GetLeftSubTree();
        }
        else
        {
            cNode = cNode->GetRightSubTree();
        }
    }
    
    return nullptr;         // target is not in the given tree.
}


template <typename T>
BTreeNode<T>* BSTRemoveData(BTreeNode<T>** ppRoot, T target)
{
    // if a to-be-deleted node is the root node, then a exceptional care must be applied...
    BTreeNode<T>* pVRoot = new BTreeNode<T>();          // virtual root node of which left sub node is the root
    BTreeNode<T>* pNode = pVRoot;                       // parent node
    BTreeNode<T>* cNode = *ppRoot;
    BTreeNode<T>* dNode;

    // let the root node be a right child node of pVRoot.
    pVRoot->ChangeRightSubTree(*ppRoot);

    // search the node to be destroyed...
    while(cNode != nullptr && cNode->GetData() != target)
    {
        pNode = cNode;
        if(target < cNode->GetData())
            cNode = cNode->GetLeftSubTree();
        else
            cNode = cNode->GetRightSubTree();
    }

    if(cNode == nullptr)            // if there is no such node with target data. return nullptr
        return nullptr;

    dNode = cNode;                  // let dNode point the to-be-deleted node.

    // case 1 : to-be-deleted node is a terminal node.
    if((dNode->GetLeftSubTree() == nullptr) && (dNode->GetRightSubTree() == nullptr))
    {
        if(pNode->GetLeftSubTree() == dNode)
        {
            pNode->RemoveLeftSubTree();
        }
        else
        {
            pNode->RemoveRightSubTree();
        }
    }
    // case 2 : to-be-deleted node has one child node.
    else if(dNode->GetLeftSubTree() == nullptr || dNode->GetRightSubTree() == nullptr)
    {
        BTreeNode<T>* dcNode;           // it points a child of the to-be-deleted node.

        if(dNode->GetLeftSubTree() != nullptr)
        {
            dcNode = dNode->GetLeftSubTree();
        }
        else
        {
            dcNode = dNode->GetRightSubTree();
        }

        if(pNode->GetLeftSubTree() == dNode)
        {
            pNode->ChangeLeftSubTree(dcNode);
        }
        else
        {
            pNode->ChangeRightSubTree(dcNode);
        }
    }
    // case 3 : to-be-deleted node has two child nodes.
    else
    {
        BTreeNode<T>* mNode = dNode->GetRightSubTree();         // mNode points the right sub tree of the to-be-deleted node.
        BTreeNode<T>* mpNode = dNode;                           // mpNode points the parent of mNode.

        T delData;

        // To search for a substitute node for the to-be-deleted node
        while(mNode->GetLeftSubTree() != nullptr)
        {
            mpNode = mNode;
            mNode = mNode->GetLeftSubTree();
        }

        // To store the data of the substitute node into the to-be-deleted node
        delData = dNode->GetData();             // save data before deletion
        dNode->SetData(mNode->GetData());

        // To rewire nodes...
        if(mpNode->GetLeftSubTree() == mNode)
        {
            mpNode->ChangeLeftSubTree(mNode->GetRightSubTree());
        }
        else
        {
            mpNode->ChangeRightSubTree(mNode->GetRightSubTree());
        }

        dNode = mNode;
        dNode->SetData(delData);            // To restore the backed-up data
    }

    if(pVRoot->GetRightSubTree() != *ppRoot)
    {
        *ppRoot = pVRoot->GetRightSubTree();
    }

    delete pVRoot;
    return dNode;
}

template <typename T>
void ShowAllData(BTreeNode<T>* bst, Action<T>& action)
{
    //Action<T> action;
    InorderTraverse(bst, action);
}

#endif

