#include <iostream>
#include <string>
#include "Graph.h"

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


int main(void)
{

	Crew cr0(0, "Janeway", "Captain");
	Crew cr1(1, "Chakotay", "Commander");
	Crew cr2(2, "Tuvok", "Lt. Commander");
	Crew cr3(3, "Torres", "Lieutenant");
	Crew cr4(4, "Paris", "Lieutenant");
	Crew cr5(5, "Kim", "Ensign");
	Crew cr6(6, "EMH Doctor", "N/A");
	Crew cr7(7, "Neelix", "N/A");
	Crew cr8(8, "Seven", "N/A");
	Crew cr9(9, "Wildman", "Ensign");

	Graph<10, Crew> crGraph;

	crGraph.AddEdge(cr0, cr1); crGraph.AddEdge(cr0, cr2); crGraph.AddEdge(cr0, cr4);
	crGraph.AddEdge(cr0, cr5); crGraph.AddEdge(cr0, cr7); crGraph.AddEdge(cr0, cr8);

	crGraph.AddEdge(cr1, cr0); crGraph.AddEdge(cr1, cr2); crGraph.AddEdge(cr1, cr3);
	crGraph.AddEdge(cr1, cr4);

	crGraph.AddEdge(cr2, cr0); crGraph.AddEdge(cr2, cr1); crGraph.AddEdge(cr2, cr9);

	crGraph.AddEdge(cr3, cr1); crGraph.AddEdge(cr3, cr4);

	crGraph.AddEdge(cr4, cr0); crGraph.AddEdge(cr4, cr1); crGraph.AddEdge(cr4, cr3);
	crGraph.AddEdge(cr4, cr5);

	crGraph.AddEdge(cr5, cr0); crGraph.AddEdge(cr5, cr4); crGraph.AddEdge(cr5, cr6);

	crGraph.AddEdge(cr6, cr5);

	crGraph.AddEdge(cr7, cr0); crGraph.AddEdge(cr7, cr8); crGraph.AddEdge(cr7, cr9);

	crGraph.AddEdge(cr8, cr0); crGraph.AddEdge(cr8, cr7);

	crGraph.AddEdge(cr9, cr2); crGraph.AddEdge(cr9, cr7);

	crGraph.ShowGraphEdgeInfo();

	cout << "----- DFS Search of the graph -----" << endl;

	cout << " starting from node 0" << endl;
	crGraph.DFSShowGraph(cr0);

	cout << endl << endl << "starting from node 1" << endl;
	crGraph.DFSShowGraph(cr1);

	cout << endl << endl << "starting from node 3" << endl;
	crGraph.DFSShowGraph(cr3);

	return 0;
}
