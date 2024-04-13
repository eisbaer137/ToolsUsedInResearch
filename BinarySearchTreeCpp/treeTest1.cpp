// test of binary tree template class BTreeNode<T>
// written by H. H. Yoo

#include <iostream>
#include <string>
#include "BinaryTree2.h"
#include "BinarySearchTree.h"

using namespace std;

class Crew
{
public:
	Crew(const string& name, const string& rank, const string& assignment)
		: mName(name), mRank(rank), mAssignment(assignment)	
	{
	
	}
	Crew()
	{ }
	Crew(const Crew& rhs)
	{
		this->mName = rhs.mName;
		this->mRank = rhs.mRank;
		this->mAssignment = rhs.mAssignment;
	}
	Crew& operator=(const Crew& rhs)
	{
		this->mName = rhs.mName;
		this->mRank = rhs.mRank;
		this->mAssignment = rhs.mAssignment;

		return *this;
	}
	//Crew& operator=(const Crew& rhs) = delete;
	~Crew()
	{

	}

	friend ostream& operator<<(ostream& os, const Crew& crew);
		
private:
	string mName;
	string mRank;
	string mAssignment;

};

ostream& operator<<(ostream& os, const Crew& crew)
{
	os << "name: " << crew.mName << std::endl;
	os << "rank: " << crew.mRank << std::endl;
	os << "assigned to " << crew.mAssignment << std::endl;
	os << "------------------------------" << std::endl;
	return os;
}

int main(void)
{
	Crew crew1("Kathryn Janeway", "Captain", "USS Voyager");
	Crew crew2("Chakotay", "Commander", "USS Voyager");
	Crew crew3("Tuvok", "Lt. Commander", "USS Voyager");
	Crew crew4("Tom Paris", "Lieutenant", "USS Voayger");
	Crew crew5("B'Elanna Torres", "Lieutenant", "USS Voyager");
	Crew crew6("Harry Kim", "Ensign", "USS Voyager");
	Crew crew7("Seven of nine", "n/a", "USS Voyager");
	Crew crew8("Neelix", "n/a", "USS Voyager");
	Crew crew9("EMH Doctor", "n/a", "USS Voyager");

	Action<Crew> action;

	BTreeNode<Crew>* pNode1 = new BTreeNode<Crew>(crew1);
	BTreeNode<Crew>* pNode2 = new BTreeNode<Crew>(crew2);
	BTreeNode<Crew>* pNode3 = new BTreeNode<Crew>(crew3);
	BTreeNode<Crew>* pNode4 = new BTreeNode<Crew>(crew4);
	BTreeNode<Crew>* pNode5 = new BTreeNode<Crew>(crew5);
	BTreeNode<Crew>* pNode6 = new BTreeNode<Crew>(crew6);
	BTreeNode<Crew>* pNode7 = new BTreeNode<Crew>(crew7);
	BTreeNode<Crew>* pNode8 = new BTreeNode<Crew>(crew8);
	BTreeNode<Crew>* pNode9 = new BTreeNode<Crew>(crew9);

	pNode1->MakeLeftSubTree(pNode2);
	pNode1->MakeRightSubTree(pNode3);

	pNode2->MakeLeftSubTree(pNode4);
	pNode2->MakeRightSubTree(pNode5);
	pNode3->MakeLeftSubTree(pNode6);
	pNode3->MakeRightSubTree(pNode7);

	pNode4->MakeLeftSubTree(pNode9);
	pNode6->MakeLeftSubTree(pNode8);

	
	cout << "---------- Crew manifest ----------" << endl << endl;

	PreorderTraverse<Crew>(pNode1, action);
	//InorderTraverse<Crew>(pNode1, action);
	//PostorderTraverse<Crew>(pNode1, action);

	cout << endl << "---------- End of list ----------" << endl;
	DeleteTree<Crew>(pNode1);


	return 0;
}
