#include <iostream>
#include <string>
#include "Graph2.h"

using namespace std;

struct Crew
{
	Crew()
	{

	}
	Crew(unsigned int id, std::string name, std::string rank)
		: mIdx(id), mName(name), mRank(rank)
	{

	}
	Crew(const Crew& rhs)
	{
		this->mIdx = rhs.mIdx;
		this->mName = rhs.mName;
		this->mRank = rhs.mRank;
	}
	Crew& operator=(const Crew& rhs)
	{
		this->mIdx = rhs.mIdx;
		this->mName = rhs.mName;
		this->mRank = rhs.mRank;
		return *this;
	}
	~Crew()
	{

	}
	bool operator==(const Crew& rhs)
	{
		bool det = (this->mIdx == rhs.mIdx) && (this->mName == rhs.mName) && (this->mRank == rhs.mName);
		return det;
	}

	bool operator!=(const Crew& rhs)
	{
		return !operator==(rhs);
	}

	friend ostream& operator<<(ostream& os, const Crew& rhs);

	unsigned int mIdx;
	std::string mName;
	std::string mRank;
};

ostream& operator<<(ostream& os, const Crew& rhs)
{
	os << "ID : " << rhs.mIdx << std::endl;
	os << "Name : " << rhs.mName << std::endl;
	os << "Rank : " << rhs.mRank << std::endl;
	return os;
}

void putBrokenLines(int len)
{
	for(int i=0; i<len; i++)
	{
		cout << "-";
	}
	cout << endl;
}

int main(void)
{

	Crew cr0(20327, "Janeway", "Captain");
	Crew cr1(24936, "Chakotay", "Commander");
	Crew cr2(16350, "Tuvok", "Lt. Commander");
	Crew cr3(30125, "Torres", "Lieutenant");
	Crew cr4(31867, "Paris", "Lieutenant");
	Crew cr5(36923, "Kim", "Ensign");
	Crew cr6(50001, "EMH Doctor", "N/A");
	Crew cr7(70002, "Neelix", "N/A");
	Crew cr8(80001, "Seven", "N/A");
	Crew cr9(33476, "Wildman", "Ensign");

	Graph<10, Crew> crGraph;

	crGraph.SetVertex(0, cr0);
	crGraph.SetVertex(1, cr1);
	crGraph.SetVertex(2, cr2);
	crGraph.SetVertex(3, cr3);
	crGraph.SetVertex(4, cr4);
	crGraph.SetVertex(5, cr5);
	crGraph.SetVertex(6, cr6);
	crGraph.SetVertex(7, cr7);
	crGraph.SetVertex(8, cr8);
	crGraph.SetVertex(9, cr9);

	crGraph.AddEdge(0, 1); crGraph.AddEdge(0, 2); crGraph.AddEdge(0, 4);
	crGraph.AddEdge(0, 5); crGraph.AddEdge(0, 7); crGraph.AddEdge(0, 8);
	
	crGraph.AddEdge(1, 0); crGraph.AddEdge(1, 2); crGraph.AddEdge(1, 3);
	crGraph.AddEdge(1, 4); 

	crGraph.AddEdge(2, 0); crGraph.AddEdge(2, 1); crGraph.AddEdge(2, 9);

	crGraph.AddEdge(3, 1); crGraph.AddEdge(3, 4);

	crGraph.AddEdge(4, 0); crGraph.AddEdge(4, 1); crGraph.AddEdge(4, 3);
	crGraph.AddEdge(4, 5);

	crGraph.AddEdge(5, 0); crGraph.AddEdge(5, 4); crGraph.AddEdge(5, 6);

	crGraph.AddEdge(6, 5);

	crGraph.AddEdge(7, 0); crGraph.AddEdge(7, 8); crGraph.AddEdge(7, 9);

	crGraph.AddEdge(8, 0); crGraph.AddEdge(8, 7);

	crGraph.AddEdge(9, 2); crGraph.AddEdge(9, 7);


	crGraph.ShowGraphEdgeInfo();

	cout << "----- BFS Search of the Graph -----" << endl;
	cout << "Searching the given graph starting from vertex 0" << endl;
	crGraph.BFSShowGraph(0);
	putBrokenLines(30);
	cout << "Searching the given graph starting from vertex 1" << endl;
	crGraph.BFSShowGraph(1);
	putBrokenLines(30);
	cout << "Searching the given graph starting from vertex 5" << endl;
	crGraph.BFSShowGraph(5);


	return 0;
}
