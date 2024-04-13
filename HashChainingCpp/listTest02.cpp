#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

typedef unsigned int nid;

class Crew
{
public:
    Crew()
    {

    }
    Crew(std::string name, nid id, std::string assigned)
        : mName(name), mId(id), mAssigned(assigned)
    {

    }
    Crew(const Crew& rhs)
    {
        this->mName = rhs.mName;
        this->mId = rhs.mId;
        this->mAssigned = rhs.mAssigned;
    }
    Crew& operator=(const Crew& rhs)
    {
        this->mName = rhs.mName;
        this->mId = rhs.mId;
        this->mAssigned = rhs.mAssigned;
        return *this;
    }
    ~Crew()
    {

    }
    bool operator==(const Crew& src)
    {
        bool det = (this->mName == src.mName) && (this->mId == src.mId) && (this->mAssigned == src.mAssigned);
        return det;
    }

    bool operator!=(const Crew& src)
    {
        return !operator==(src);
    }


    friend ostream& operator<<(ostream& os, const Crew& src);

private:
    std::string mName;
    nid mId;
    std::string mAssigned;
};

ostream& operator<<(ostream& os, const Crew& src)
{
    os << "Name : " << src.mName << "\n";
    os << "ID : " <<  src.mId << "\n";
    os << "Assigned to " << src.mAssigned << std::endl;

    return os;
}

int main(void)
{
	
    Crew cr1("Jean Luc Picard", 31011, "USS Enterprise");
    Crew cr2("Williamg Thomas Riker", 42077, "USS Enterprise");
    Crew cr3("Data", 52084, "USS Enterprise");
    Crew cr4("Geordi LaForge", 51051, "USS Enterprise");
    Crew cr5("Worf", 58094, "USS Enterprise");
    Crew cr6("Deanna Troi", 47037, "USS Enterprise");
    Crew cr7("Beverly Crusher", 38074, "USS Enterprise");
	/*
    LinkedList<Crew> lst2;

    lst2.LInsert(cr1);
    lst2.LInsert(cr2);
    lst2.LInsert(cr3);
    lst2.LInsert(cr4);
    lst2.LInsert(cr5);
    lst2.LInsert(cr6);
    lst2.LInsert(cr7);

    lst2.ShowElements();

    lst2.RemoveElement(cr5);
    lst2.RemoveElement(cr7);
    cout << "-----------------------------" << endl;
    lst2.ShowElements();
    cout << "The number of crews after reassignment : " << lst2.LCount() << endl;
	*/

	LinkedList<Crew> lst3[10];
	lst3[0].LInsert(cr1);
	lst3[0].LInsert(cr2);	
	
	lst3[1].LInsert(cr3);
	lst3[1].LInsert(cr4);

	lst3[2].LInsert(cr5);
	lst3[2].LInsert(cr6);

	lst3[3].LInsert(cr7);

	for(int i=0; i<10; i++)
	{
		cout << "slot : " << i << " has " << lst3[i].LCount() << " elements... " << endl;
	}

	for(int i=0; i<10; i++)
	{
		if(lst3[i].LCount() != 0)
			cout<< "Slot : " << i << endl;
		lst3[i].ShowElements();
	}
	
	// Removing some crews..
	lst3[2].RemoveElement(cr6);
    // end-of-crew-removal

    cout << "Let's do it again..." << endl;

	for(int i=0; i<10; i++)
	{
		cout << "slot : " << i << " has " << lst3[i].LCount() << " elements... " << endl;
	}

	for(int i=0; i<10; i++)
	{
		if(lst3[i].LCount() != 0)
			cout<< "Slot : " << i << endl;
		lst3[i].ShowElements();
	}


    return 0;
}
