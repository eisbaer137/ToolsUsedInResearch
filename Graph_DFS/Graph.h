#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>
#include "LinkedList.h"
#include "ArrayBasedStack.h"

template <unsigned int size, typename T>
class Graph
{
public:
    Graph();
    Graph(const Graph<size, T>& rhs) = delete;
    Graph<size, T>& operator=(const Graph<size, T>& src) = delete;
    ~Graph();

public:
    void AddEdge(T node, T neighbor);
    void ShowGraphEdgeInfo() const;

    void DFSShowGraph(T startV);

private:
    bool CheckVisitHistory(T visitV);

private:
    unsigned int mNumVertices;       // the number of vertices in a graph
    unsigned int mNumEdges;          // the number of edges in a graph
    LinkedList<T>* mAdjList;
    std::vector<bool> mVisitInfo;
};


template <unsigned int size, typename T>
Graph<size, T>::Graph()
    : mNumVertices(size), mNumEdges(0)
{
    mAdjList = new LinkedList<T>[size];
    mVisitInfo.resize(size);
    for(size_t i=0; i<size; ++i)
    {
        mVisitInfo[i] = false;
    }
}

template <unsigned int size, typename T>
Graph<size, T>::~Graph()
{
    if(mAdjList != nullptr)
        delete [] mAdjList;
}

template <unsigned int size, typename T>
void Graph<size, T>::AddEdge(T node, T neighbor)
{
    unsigned int idx = node.mIdx;
    //unsigned int idxN = neighbor.mIdx;
    mAdjList[idx].LInsert(neighbor);
    //mAdjList[idxN].LInsert(node);
    (this->mNumEdges)++;
}

template <unsigned int size, typename T>
void Graph<size, T>::ShowGraphEdgeInfo() const
{
    T temp;

    for(unsigned int i=0; i < this->mNumVertices; ++i)
    {
        std::cout << "Vertices connected to a vertex " << i << std::endl;
        if(mAdjList[i].LFirst(temp))
        {
            std::cout << temp << std::endl;
            
            while(mAdjList[i].LNext(temp))
            {
                std::cout << temp << std::endl;
            }
        }
        std::cout << "------------------------------" << std::endl;
    }
}

template <unsigned int size, typename T>
bool Graph<size, T>::CheckVisitHistory(T visitV)
{
    unsigned int idx = visitV.mIdx;
    if(mVisitInfo[idx] == false)
    {
        mVisitInfo[idx] = true;
        std::cout << visitV << std::endl;
        return true;
    }
    return false;
}

template <unsigned int size, typename T>
void Graph<size, T>::DFSShowGraph(T startV)
{
    Stack<T> stack;
    T visitV = startV;
    T nextV;
    bool visitFlag = false;
    CheckVisitHistory(visitV);

    unsigned int visitIdx = visitV.mIdx;

    while(mAdjList[visitIdx].LFirst(nextV) == true)
    {
        visitFlag = false;

        if(CheckVisitHistory(nextV) == true)
        {
            stack.SPush(visitV);
            visitV = nextV;
            visitIdx = visitV.mIdx;
            visitFlag = true;
        }
        else
        {
            while(mAdjList[visitIdx].LNext(nextV) == true)
            {
                if(CheckVisitHistory(nextV) == true)
                {
                    stack.SPush(visitV);
                    visitV = nextV;
                    visitIdx = visitV.mIdx;
                    visitFlag = true;
                    break;
                }
            }
        }

        if(visitFlag == false)
        {
            if(stack.IsStackEmpty() == true)
            {
                break;
            }
            else
            {
                visitV = stack.SPop();
                visitIdx = visitV.mIdx;
            }
        }
    }

    for(size_t i=0; i < this->mNumVertices; ++i)
    {
        this->mVisitInfo[i] = false;
    }
}



#endif
