// multithreaded DAG computation problem
// written by H.H. Yoo on 8th July 2024

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>

typedef void (*functor)(std::vector<int>*, int*);

// node computing function
void ComputeArgs(std::vector<int>* args, int* result)
{
	if(args->size() == 1)
	{
		*result = *(args->begin()) * 2;
	}
	else
	{
		for(auto itr = args->begin(); itr != args->end(); ++itr)
		{
			*result += *itr;
		}
	}
}

struct Node
{
	std::vector<int> mInput;			// input vector
	int mOutput;						// output
	//functor mFunc = ComputeArgs;		// functor for calculation
};

// function, supposed to be delivered to each thread
void ComputeNode(int _curNode, std::vector<std::vector<int>>& _links, std::vector<Node>& _nodes, std::vector<std::thread>* _pthreads, int _numberOfNodes)
{
	std::vector<int> neighbors;
	int result = 0;
	
	// first, we need to check if the current node is start nodes or other nodes
	for(int i=0; i<_numberOfNodes; ++i)
	{
		if(std::find(_links[i].begin(), _links[i].end(), _curNode) != _links[i].end())
		{
			neighbors.push_back(i);
		}
	}

	if(neighbors.empty())	// if a node is starting node
	{
		ComputeArgs(&_nodes[_curNode].mInput, &result);
		_nodes[_curNode].mOutput = result;
	}
	else					// for intermediate and final nodes
	{
		for(int i=0; i< neighbors.size(); ++i)	// we need to wait till our neighbor nodes are done with tasks.
		{
			if((_pthreads->data() + neighbors[i])->joinable())	
			{
				(_pthreads->data() + neighbors[i])->join();
			}
		}
		
		for(auto itr = neighbors.begin(); itr != neighbors.end(); ++itr)
		{
			_nodes[_curNode].mInput.push_back(_nodes[*itr].mOutput);	// copy neighbor nodes' output to the current node's input
		}
		ComputeArgs(&_nodes[_curNode].mInput, &result);
		_nodes[_curNode].mOutput = result;
	}	
}


int main(void)
{
	// construct a Directed Acyclic Graph in vector<vector<int>> format.
	const int numberOfNodes = 10;
	std::vector<std::vector<int>> dagLinks;	// it stores the DAG links structure
	
	// for this example...
	dagLinks.reserve(numberOfNodes);
	dagLinks[0].push_back(3);
	dagLinks[1].push_back(3);
	dagLinks[2].push_back(3);	dagLinks[2].push_back(4);
	dagLinks[3].push_back(5);	dagLinks[3].push_back(6);
	dagLinks[4].push_back(6);	dagLinks[4].push_back(8);
	dagLinks[5].push_back(7);
	dagLinks[6].push_back(7);	dagLinks[6].push_back(8);
	//dagLinks[7]	: terminal node
	dagLinks[8].push_back(9);
	//dagLinks[9] : terminal node

	std::vector<Node> nodes(numberOfNodes);	// std::vector for nodes in the given DAG

	std::vector<std::thread> threads;	// std::vector<std::thread> for regulating each thread's operation

	// initialization, assuming we expect 10 arguments at best for each functor node. 
	for(int i=0; i<numberOfNodes; ++i)
	{
		nodes[i].mOutput = 0;
	}
	int val1;
	int val2;
	int val3;

	std::cout << "Input a integer value for node 0 : ";
	std::cin >> val1;
	std::cout << "Input a integer value for node 1 : ";
	std::cin >> val2;
	std::cout << "Input a integer value for node 3 : ";
	std::cin >> val3;


	// initial condition : set a input value at node 0, 1, 2 
	nodes[0].mInput.push_back(val1);
	nodes[1].mInput.push_back(val2);
	nodes[2].mInput.push_back(val3);

	 // computation loop
	for(size_t i=0; i < numberOfNodes; ++i)
	{
		threads.push_back(std::thread(ComputeNode, i, std::ref(dagLinks), std::ref(nodes), &threads, numberOfNodes));
	}

	for(size_t i=0; i < numberOfNodes; ++i)
	{
		if(threads[i].joinable())
		{
			threads[i].join();
		}
	}

	std::cout << std::endl << std::endl;

	// To check the result, find out the last nodes
	for(int i=0; i < numberOfNodes; ++i)
	{
		if(dagLinks[i].size() == 0)
		{
			std::cout << "terminal node " + std::to_string(i) + " has a output value : " << nodes[i].mOutput << std::endl;
		}
	}

	// print out the output of the entire nodes...
	
	std::cout << std::endl <<"output values of the entire nodes ..." << std::endl;
	for(size_t i=0; i<10; ++i)
	{
		std::cout << "node[" << i << "] : " << nodes[i].mOutput << std::endl;
	}
			 
	return 0;
}















