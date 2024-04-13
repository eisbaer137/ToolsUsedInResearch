#include <iostream>
#include "ListBasedQueue.h"

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
    Queue<Crew> crewQ;

    Crew cr1(10134, "Jean Luc Picard", "Captain", "USS Enterprise");
    Crew cr2(12043, "William Thomas Riker", "Commander", "USS Enterprise");
    Crew cr3(15037, "Beverly Crusher", "Commander", "USS Enterprise");
    Crew cr4(17098, "Deanna Troi", "Lt. Commander", "USS Enterprise");
    Crew cr5(22037, "Geordi LaForge", "Lt. Commander", "USS Enterprise");
    Crew cr6(16047, "Kathryn Janeway", "Captain", "USS Voyager");
    Crew cr7(18093, "Chakotay", "Commander", "USS Voyager");
    Crew cr8(7023, "Tuvok", "Lt. Commander", "USS Voyager");
    Crew cr9(34027, "Fox William Mulder", "Special Agent", "FBI Headquarters");
    Crew cr10(38076, "Dana Katherine Scully", "Special Agent", "FBI Headquarters");
    Crew cr11(25037, "Walter Sergei Skinner", "Assistant Director", "FBI Headquarters");

    crewQ.Enqueue(cr1);
    crewQ.Enqueue(cr2);
    crewQ.Enqueue(cr3);
    crewQ.Enqueue(cr4);
    crewQ.Enqueue(cr5);
    crewQ.Enqueue(cr6);
    crewQ.Enqueue(cr7);
    crewQ.Enqueue(cr8);
    crewQ.Enqueue(cr9);
    crewQ.Enqueue(cr10);
    crewQ.Enqueue(cr11);

    cout << "Let's peek our queue..." << endl;
    cout << crewQ.Peek();

    PutBrokenLine(60);

    while(!crewQ.IsQueueEmpty())
    {
        cout << crewQ.Dequeue();
    }
    
    PutBrokenLine(60);


    return 0;
}