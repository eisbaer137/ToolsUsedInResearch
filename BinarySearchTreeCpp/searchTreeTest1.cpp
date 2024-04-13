#include <iostream>
#include <string>
#include "BinaryTree2.h"
#include "BinarySearchTree.h"

using namespace std;

class Crew
{
public:
    Crew()
    {

    }
    Crew(int id, const std::string& name, const std::string& rank, const std::string& assigned)
        :   mId(id), mName(name), mRank(rank), mAssigned(assigned)
    {
        /*
        mId = id;
        mName = name;
        mRank = rank;
        mAssigned = assigned;
        */
    }


    Crew(const Crew& rhs)
    {
        this->mId = rhs.mId;
        this->mName = rhs.mName;
        this->mRank = rhs.mRank;
        this->mAssigned = rhs.mAssigned;
    }
    Crew& operator=(const Crew& rhs)
    {
        this->mId = rhs.mId;
        this->mName = rhs.mName;
        this->mRank = rhs.mRank;
        this->mAssigned = rhs.mAssigned;

        return *this;
    }
    ~Crew()
    {

    }
    bool operator<(const Crew& rhs)
    {
        return this->mId < rhs.mId ? true : false;
    }

    bool operator>(const Crew& rhs)
    {
        return this->mId > rhs.mId ? true : false;
    }

    bool operator==(const Crew& rhs)
    {
        if((this->mId == rhs.mId) && (this->mName == rhs.mName) && (this->mRank == rhs.mRank) && (this->mAssigned == rhs.mAssigned))
        {
            return true;
        }    
        else
        {
            return false;
        }
    }

    bool operator!=(const Crew& rhs)
    {
        return !operator==(rhs);
    }

    friend ostream& operator<<(ostream& os, const Crew& crew);

private:
    int mId;
    std::string mName;
    std::string mRank;
    std::string mAssigned;
};

ostream& operator<<(ostream& os, const Crew& crew)
{
    os << crew.mId << " : ";
    os << crew.mName << ", ";
    os << crew.mRank << ", ";
    os << crew.mAssigned << std::endl;
    return os;
}

void PutBrokenLine(int length)
{
    for(size_t i=0; i<length; ++i)
    {
        cout << "-";
    }
    cout << endl;
}

int main(void)
{   
    
    BTreeNode<Crew>* bstRoot;
    BTreeNode<Crew>* resNode;

    Crew cr1(12383, "Picard", "Captain", "USS Enterprise");
    Crew cr2(15784, "Riker", "Commander", "USS Enterprise");
    Crew cr3(13645, "Beverly", "Chief Medical Officer", "USS Enterprise");
    Crew cr4(20173, "Data", "Lt. Commander", "USS Enterprise");
    Crew cr5(23592, "Worf", "Lieutenant", "USS Enterprise");
    Crew cr6(21383, "La Forge", "Lt. Commander", "USS Enterprise");
    Crew cr7(17855, "Troi", "Lt. Commander", "USS Enterprise");

    Crew cr8(19038, "Janeway", "Captain", "USS Voyager");
    Crew cr9(23095, "Chakotay", "Commander", "USS Voyager");
    Crew cr10(99999, "EMH Doctor", "Chief Medical Officer", "USS Voyager");
    Crew cr11(88888, "Seven of Nine", "Science Officer", "USS Voyager");
    Crew cr12(10023, "Tuvok", "Lt. Commander", "USS Voyager");
    Crew cr13(29034, "B'lenna", "Lieutenant", "USS Voyager");
    Crew cr14(26027, "Paris", "Lieutenant", "USS Voyager");
    Crew cr15(28076, "Kim", "Ensign", "USS Voyager");
    Crew cr16(90001, "Neelix", "Moral Officer", "USS Voyager");


    BSTMakeAndInit<Crew>(&bstRoot);

    BSTInsertData<Crew>(&bstRoot, cr1);
    BSTInsertData<Crew>(&bstRoot, cr2);
    
    BSTInsertData<Crew>(&bstRoot, cr3);
    BSTInsertData<Crew>(&bstRoot, cr4);
    BSTInsertData<Crew>(&bstRoot, cr5);
    BSTInsertData<Crew>(&bstRoot, cr6);
    BSTInsertData<Crew>(&bstRoot, cr7);
    BSTInsertData<Crew>(&bstRoot, cr8);
    BSTInsertData<Crew>(&bstRoot, cr9);
    BSTInsertData<Crew>(&bstRoot, cr10);
    BSTInsertData<Crew>(&bstRoot, cr11);
    BSTInsertData<Crew>(&bstRoot, cr12);
    BSTInsertData<Crew>(&bstRoot, cr13);
    BSTInsertData<Crew>(&bstRoot, cr14);
    BSTInsertData<Crew>(&bstRoot, cr15);
    BSTInsertData<Crew>(&bstRoot, cr16);
    

    Action<Crew> action;


    cout << "----- Total Crew Manifest -----" << endl << endl;

    ShowAllData<Crew>(bstRoot, action);

    cout << endl; 
    PutBrokenLine(60);
    cout << endl;
    
    cout << "----- After Removing Voyager Crews -----" << endl << endl;

    resNode = BSTRemoveData<Crew>(&bstRoot, cr8);
    delete resNode;
    resNode = BSTRemoveData<Crew>(&bstRoot, cr9);
    delete resNode;
    resNode = BSTRemoveData<Crew>(&bstRoot, cr10);
    delete resNode;
    resNode = BSTRemoveData<Crew>(&bstRoot, cr11);
    delete resNode;
    resNode = BSTRemoveData<Crew>(&bstRoot, cr12);
    delete resNode;
    resNode = BSTRemoveData<Crew>(&bstRoot, cr13);
    delete resNode;
    resNode = BSTRemoveData<Crew>(&bstRoot, cr14);
    delete resNode;
    resNode = BSTRemoveData<Crew>(&bstRoot, cr15);
    delete resNode;
    resNode = BSTRemoveData<Crew>(&bstRoot, cr16);
    delete resNode;


    ShowAllData<Crew>(bstRoot, action);
    
    cout << endl;
    PutBrokenLine(60);
    cout << endl;

    // Destroy the tree
    DeleteTree(bstRoot);

    

    cout << endl << "so far so good..." << endl;
    return 0;
}
