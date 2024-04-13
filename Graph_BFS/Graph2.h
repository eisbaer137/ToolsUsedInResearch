#ifndef __GRAPH2_H__

#define __GRAPH2_H__

#include <iostream>
#include <vector>
#include "LinkedList.h"
#include "ListBasedQueue.h"

template <unsigned int size, typename T>
class Graph
{
public:
    Graph();
    Graph(const Graph<size, T>& rhs) = delete;
    Graph<size, T>& operator=(const Graph<size, T>& rhs) = delete;
    ~Graph();

public:
    void SetVertex(unsigned int vertex, T data);
    void AddEdge(unsigned int vertex, unsigned int neighbor);
    void ShowGraphEdgeInfo() const;
    void BFSShowGraph(unsigned int startV);

private:
    bool CheckVisitHistory(unsigned int startV);

private:
    unsigned int mNumVertices;
    unsigned int mNumEdges;
    LinkedList<unsigned int>* mAdjList;
    std::vector<bool> mVisitInfo;
    std::vector<T> mDataReservoir;
};

template <unsigned int size, typename T>
Graph<size, T>::Graph()
    : mNumVertices(size), mNumEdges(0)
{
    mAdjList = new LinkedList<unsigned int>[size];
    mVisitInfo.resize(size);
    mDataReservoir.resize(size);
    for(size_t i=0; i<size; ++i)
    {
        mVisitInfo[i] = false;
    }
}

template <unsigned int size, typename T>
Graph<size, T>::~Graph()
{
    delete [] mAdjList;
}

template <unsigned int size, typename T>
void Graph<size, T>::SetVertex(unsigned int vertex, T data)
{
    mDataReservoir[vertex] = data;
}

template <unsigned int size, typename T>
void Graph<size, T>::AddEdge(unsigned int vertex, unsigned int neighbor)
{
    mAdjList[vertex].LInsert(neighbor);
    (this->mNumEdges)++;
}

template <unsigned int size, typename T>
void Graph<size, T>::ShowGraphEdgeInfo() const
{
    unsigned int temp;

    for(unsigned int i=0; i < this->mNumVertices; ++i)
    {
        std::cout << "Vertices connected to a vertex " << i << " : ";

        if(mAdjList[i].LFirst(temp))
        {
            std::cout << temp << " ";

            while(mAdjList[i].LNext(temp))
            {
                std::cout << temp << " ";
            }
        }
        std::cout << std::endl;
    }
}

template <unsigned int size, typename T>
bool Graph<size, T>::CheckVisitHistory(unsigned int visitV)
{
    if(mVisitInfo[visitV] == false)
    {
        mVisitInfo[visitV] = true;
        std::cout << mDataReservoir[visitV] << std::endl;
        return true;
    }
    return false;
}

template <unsigned int size, typename T>
void Graph<size, T>::BFSShowGraph(unsigned int startV)
{
    Queue<unsigned int> queue;
    unsigned int visitV = startV;
    unsigned int nextV;

    this->CheckVisitHistory(visitV);

    while(this->mAdjList[visitV].LFirst(nextV) == true)
    {
        if(this->CheckVisitHistory(nextV) == true)
        {
            queue.Enqueue(nextV);
        }

        while(this->mAdjList[visitV].LNext(nextV) == true)
        {
            if(this->CheckVisitHistory(nextV) == true)
            {
                queue.Enqueue(nextV);
            }
        }

        if(queue.IsQueueEmpty() == true)
        {
            break;
        }
        else
        {
            visitV = queue.Dequeue();
        }
    }

    for(unsigned int i = 0; i < this->mNumVertices; ++i)
    {
        this->mVisitInfo[i] = false;
    }
}



#endif
