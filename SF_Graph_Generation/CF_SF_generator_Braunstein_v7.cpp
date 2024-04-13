// Configuration Model for simulating the Braunstein group's result 
// All self loops and multi-edges are re-wired.
// code written by H.H. Yoo

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include <set>
#include <vector>
#include <list>
#include <random>
#include <queue>
#include <algorithm>
#include "uni_random.h"

using namespace std;

long seed;
int kmin;
int Nodes;
int SampleNum;
double lambda; // the value of gamma
char outfile[300];

class nodePair // class for expressing the node pair of a link
{
public:
    int nodeA;
    int nodeB;
    nodePair(int a1=0, int b1=0) : nodeA(a1), nodeB(b1) // constructor setting
    { }
    nodePair& InputData(int a2, int b2)
    {
        nodeA = a2;
        nodeB = b2;
        return *this;
    }
    nodePair Flip() 
    {
        nodePair tRef;
        tRef.nodeA = nodeB;
        tRef.nodeB = nodeA;
        return tRef;
    }
    nodePair& operator=(const nodePair & ref)  // = operator overloading
    {
        nodeA = ref.nodeA;
        nodeB = ref.nodeB;
        return *this;
    }
    bool operator==(const nodePair & comp0) // == operator overloading
    {
        bool det = ((nodeA==comp0.nodeA) && (nodeB==comp0.nodeB)) ? true : false;
        return det;
    }
    void ShowData() const
    {
        cout<<"("<<nodeA<<","<<nodeB<<")"<<endl;
    }
    int FirstElem() { return nodeA; }

    int SecondElem() { return nodeB; }
};

int ReadCommandLine(int argc, char * argv[]);
void lookuptable2(int kmin_, int kmax_, double gamma_, double * prob_, int * donor_);
int ranPowerLaw2(int kmin_, int kmax_, double * prob_, int * donor_, long * seed_);
int myrandom (int i);
void MakingLinkSumEven(vector<int> * obj_);
void MultiGraph(set<int> * SCon_, vector<nodePair> VCon_, vector<nodePair> * MultiEdges_, vector<nodePair> * SelfLoops_);
void RemoveMultiEdges(set<int> * SCon_, vector<nodePair> * multiLink_, list<nodePair> * LList_, long * seed_);
void RemoveSelfLoops(set<int> * SCon_, vector<nodePair> * selfloop_, list<nodePair> * LList_, long * seed_);

int main(int argc, char * argv[])
{
    if(!ReadCommandLine(argc, argv))
        exit(1);
        
    int kmax;
    nodePair npTemp0, npTemp1, npTemp2;
    
    vector<int> degSeq; // A vector container for containing degree sequence
    vector<int>::iterator vt0;
    vector<int>::iterator vt1;
    
    vector<nodePair> Configuration; // for assigning stubs to nodes
    vector<nodePair> MultiEdges; // for storing the multiedge nodes
    vector<nodePair> SelfLoops; // for storing the selfloop nodes
    list<nodePair> LinkList; // link list for randomly picking up the link
    vector<nodePair>::iterator nt0, nt1;
    list<nodePair>::iterator lt0, lt1;
    
    set<int> * nodes = new set<int> [Nodes]; // Adjacency list
    set<int>::iterator pt0;
    
    int DSize;
    int pickup;
    int SeqSize;
    int temp1, temp2, temp3;
    int StubCounter;
    int ndx;
    int ids; // sample number index
    char buffer1[30]; // node number
    char buffer2[30]; // minimum degree
    char buffer3[30]; // gamma value
    char buffer4[30]; // id tag.
    
    FILE *fp_out;
    
    seed = -1L*getpid();
    
    if(lambda>=3.0)
        kmax = kmin*(int)(pow((double)Nodes, 1.0/(lambda-1.0)));
    else    
        kmax = kmin*(int)(sqrt((double)Nodes));
        
    DSize = kmax - kmin + 1; 
    double * p = new double[DSize];
    int * y = new int[DSize];
    for(int id0=0; id0<DSize; id0++)
    {
        p[id0] = 0.0;
        y[id0] = 0; 
    }
    lookuptable2(kmin, kmax, lambda, p, y); // making the lookuptable2
    {
        sprintf(buffer1, "%d", Nodes); sprintf(buffer2, "%d", kmin); sprintf(buffer3, "%1.1f", lambda); 
    }
    // start
    for(ids=0; ids<SampleNum; ids++)
    {
        // making the file name
        {
            sprintf(buffer4, "%d", ids+1); sprintf(outfile, "%s", "CF_SF_Braunstein_N");
            strcat(outfile, buffer1); strcat(outfile, "_kmin"); strcat(outfile, buffer2);
            strcat(outfile, "_g"); strcat(outfile, buffer3); strcat(outfile, "_id");
            strcat(outfile, buffer4); strcat(outfile, ".txt");
        }
        
        degSeq.clear();
        Configuration.clear();
        MultiEdges.clear();
        SelfLoops.clear();
        LinkList.clear();
        for(int id0=0; id0<Nodes; id0++){ nodes[id0].clear(); }
        
        for(int id0=0; id0<Nodes; id0++)
        {
            pickup = ranPowerLaw2(kmin, kmax, p, y, &seed);
            degSeq.push_back(pickup);
        }
    
        SeqSize = 0;
        for(vt0=degSeq.begin(); vt0!=degSeq.end(); vt0++)
            SeqSize += *vt0;
            
        if(SeqSize%2!=0)
        {
            MakingLinkSumEven(&degSeq);
            SeqSize++;
        }
    
        // making the stubs for wiring the nodes to get a network.
        StubCounter = 1;
        ndx = 0;
        for(vt0=degSeq.begin(); vt0!=degSeq.end(); vt0++)
        {
            temp1 = *vt0;
            for(int id1=1; id1<=temp1; id1++)
            {
                npTemp0.InputData(StubCounter, ndx);
                Configuration.push_back(npTemp0);
                StubCounter++;
            }
            ndx++;
        }
        //for(lt0=LinkList.begin(); lt0!=LinkList.end(); lt0++)
        //    lt0->ShowData();
    
        MultiGraph(nodes, Configuration, &MultiEdges, &SelfLoops);    // wiring the nodes: making the MultiGraph()
 
        for(int id0=0; id0<Nodes; id0++) // constructing the link list
        {
            for(pt0=nodes[id0].begin(); pt0!=nodes[id0].end(); pt0++)
            {
                npTemp1.InputData(id0, *pt0);
                LinkList.push_back(npTemp1);   
            }
        }   
        RemoveMultiEdges(nodes, &MultiEdges, &LinkList, &seed);             // rewiring the multi-edges
        RemoveSelfLoops(nodes, &SelfLoops, &LinkList, &seed);               // rewiring the self-loops
        // write the adjacency list out into the file 
        {
            fp_out = fopen(outfile, "w");
            for(int id0=0; id0<Nodes; id0++)
            {
                for(pt0=nodes[id0].begin(); pt0!=nodes[id0].end(); pt0++)
                {
                fprintf(fp_out, "%d\t%d\n", id0, *pt0);    
                }
            }
        fclose(fp_out);
        }
    } // end of the sample loop
    
    delete [] nodes;
    cout<<endl<<"so far so good~!"<<endl;
    return 0;
}

// definition of functions
void MakingLinkSumEven(vector<int> * obj_)
{
    int minVal;
    vector<int>::iterator vt;
    minVal = *(obj_->begin());
    for(vt=obj_->begin(); vt!=obj_->end(); vt++)
    {
        if(minVal>*vt)
            minVal = *vt;
    }
    vt = find(obj_->begin(), obj_->end(), minVal);
    obj_->erase(vt);
    obj_->push_back(minVal+1);
}

int myrandom(int i)
{
    return rand()%i;
}

void MultiGraph(set<int> * SCon_, vector<nodePair> VCon_, vector<nodePair> * MultiEdges_, vector<nodePair> * SelfLoops_)
{
    int tp0, tp1;
    int pk1, pk2;
    int gx, gy;
    nodePair npp0, npp1, n_temp; 
    random_device rd;
    mt19937 gen(rd());
    //random_shuffle(VCon_.begin(), VCon_.end(), myrandom);
    random_shuffle(VCon_.begin(), VCon_.end());
    while(!VCon_.empty())
    {
        npp0 = VCon_.back();
        VCon_.pop_back();
        npp1 = VCon_.back();
        VCon_.pop_back();
        gx = npp0.SecondElem(); gy = npp1.SecondElem();
        if(gx==gy)
        {
            n_temp.InputData(gx,gy);
            SelfLoops_->push_back(n_temp);
        }
        else if(SCon_[gx].count(gy) && SCon_[gy].count(gx))
        {
            n_temp.InputData(gx,gy);
            MultiEdges_->push_back(n_temp);
        }
        else
        {
            SCon_[gx].insert(gy);
            SCon_[gy].insert(gx);
        }        
    } 
}

void RemoveMultiEdges(set<int> * SCon_, vector<nodePair> * multiLink_, list<nodePair> * LList_, long * seed_)
{
    list<nodePair>::iterator ltx0, ltx1;
    nodePair npp0, npp1, npp2, npp3;
    int pickup_, LSize_, coinFlip;
    int edgeLeft, edgeRight, pLeft, pRight;
    while(!multiLink_->empty())
    {
        npp0 = multiLink_->back(); edgeLeft = npp0.FirstElem(); edgeRight = npp0.SecondElem();
        LSize_ = LList_->size();
        ltx0 = LList_->begin(); pickup_ = (int)((double)LSize_*ran3(seed_));
        advance(ltx0, pickup_);
        coinFlip = schwarz_und_weisse(ran3(seed_));
        if(coinFlip>0){ pLeft = ltx0->FirstElem(); pRight = ltx0->SecondElem(); }
        else { pLeft = ltx0->SecondElem(); pRight = ltx0->FirstElem(); }
        if(SCon_[edgeLeft].count(pLeft) || SCon_[edgeLeft].count(pRight) || SCon_[edgeRight].count(pLeft) || SCon_[edgeRight].count(pRight))
        {
            continue;
        }
        else
        {
            SCon_[edgeLeft].insert(pLeft); SCon_[pLeft].insert(edgeLeft); // recording newly established link data to the nodes[..] and link list
            SCon_[edgeRight].insert(pRight); SCon_[pRight].insert(edgeRight);
            npp2.InputData(edgeLeft, pLeft); LList_->push_back(npp2);
            npp2.InputData(pLeft, edgeLeft); LList_->push_back(npp2);
            npp3.InputData(edgeRight, pRight); LList_->push_back(npp3);
            npp3.InputData(pRight, edgeRight); LList_->push_back(npp3);
            
            SCon_[pLeft].erase(pRight); SCon_[pRight].erase(pLeft); //erasing the old link data from the nodes[..] and link list
            npp2 = ltx0->Flip();
            LList_->erase(ltx0);
            ltx1 = find(LList_->begin(), LList_->end(), npp2);
            LList_->erase(ltx1);
            multiLink_->pop_back();
        }
    } // end of while loop
} 

void RemoveSelfLoops(set<int> * SCon_, vector<nodePair> * selfloop_, list<nodePair> * LList_, long * seed_)
{
    list<nodePair>::iterator ltx0, ltx1;
    nodePair npp0, npp1, npp2, npp3;
    int pickup_, LSize_, coinFlip;
    int badNode, pLeft, pRight;
    while(!selfloop_->empty())
    {
        npp0 = selfloop_->back(); badNode = npp0.FirstElem();
        LSize_ = LList_->size();
        ltx0 = LList_->begin(); pickup_ = (int)((double)LSize_*ran3(seed_));
        advance(ltx0, pickup_);
        coinFlip = schwarz_und_weisse(ran3(seed_));
        if(coinFlip>0){ pLeft = ltx0->FirstElem(); pRight = ltx0->SecondElem(); }
        else { pLeft = ltx0->SecondElem(); pRight = ltx0->FirstElem(); }
        if(SCon_[badNode].count(pLeft) || SCon_[badNode].count(pRight))
        {
            continue;
        }
        else
        {   
            SCon_[badNode].insert(pLeft); SCon_[pLeft].insert(badNode); // recording newly established link data to the nodes[...] and link list
            SCon_[badNode].insert(pRight); SCon_[pRight].insert(badNode);
            npp1.InputData(badNode, pLeft); LList_->push_back(npp1);
            npp1.InputData(pLeft, badNode); LList_->push_back(npp1);
            npp2.InputData(badNode, pRight); LList_->push_back(npp2);
            npp2.InputData(pRight, badNode); LList_->push_back(npp2);
            
            SCon_[pLeft].erase(pRight); SCon_[pRight].erase(pLeft);
            npp3 = ltx0->Flip();
            LList_->erase(ltx0);
            ltx1 = find(LList_->begin(), LList_->end(), npp3);
            LList_->erase(ltx1);
            selfloop_->pop_back();            
        }
    } // end of while loop
}

void lookuptable2(int kmin_, int kmax_, double gamma_, double * prob_, int * donor_)
{
    queue <int> poor;
    queue <int> rich;
    
    int N;
    int rich_idx;
    int poor_idx;
    double Nd;
    double incr;
    double norm = 0.0;
    
    N = kmax_ - kmin_ + 1;
    Nd = (double)N;
    
    for(int id0=0; id0<N; id0++) // initialization 1: making the normalization const. & prepare the table
    {
        incr = pow((double)(id0+kmin_), (-1.0)*gamma_);
        norm += incr;
        prob_[id0] = 0.0;
        donor_[id0] = 0.0;
    }
    for(int id0=0; id0<N; id0++)  // initialization 2
    {
        prob_[id0] = Nd*pow((double)(id0+kmin_), (-1.0)*gamma_)/norm;
        if(prob_[id0]<1.0)
            poor.push(id0);
        else if(prob_[id0]>1.0)
            rich.push(id0);
    }
    while(!poor.empty())
    {
        poor_idx = poor.front();
        poor.pop();
        if(!rich.empty())
        {
            rich_idx = rich.front();
            rich.pop();
            donor_[poor_idx] = rich_idx + kmin_;
            prob_[rich_idx] -= (1.0-prob_[poor_idx]);
            if(prob_[rich_idx]<1.0)
                poor.push(rich_idx);
            else if(prob_[rich_idx]>1.0)
                rich.push(rich_idx);
        }
        else
        {
            donor_[poor_idx] = poor_idx + kmin_;
        }
    }
    for(;!rich.empty();)
        rich.pop();
} // end of lookuptable2

int ranPowerLaw2(int kmin_, int kmax_, double * prob_, int * donor_, long * seed_)
{
    int RetrValue;
    int K = kmax_ - kmin_ + 1;
    int rint;
    double r,d;
    
    r = ((double)K*ran3(seed_));
    rint = (int)r;
    
    if(rint==K) // handling problems at the edge
        rint = K-1;
    else if(rint==-1)
        rint = 0;
    
    d = r - (double)rint;
    if(d<prob_[rint])
        RetrValue = rint+kmin_;
    else  
        RetrValue = donor_[rint];
        
    return RetrValue;
}

int ReadCommandLine(int argc, char * argv[])
{
    for(int i=1; i<argc; i++)
    {
        if(strstr(argv[i], "-N"))
            Nodes = atoi(argv[i]+2);
        if(strstr(argv[i], "-m"))
            kmin = atoi(argv[i]+2);
        if(strstr(argv[i], "-S"))
            SampleNum = atoi(argv[i]+2);
        if(strstr(argv[i], "-g"))
            lambda = atof(argv[i]+2);
        if(strstr(argv[i], "-?"))
        {
            cout<<"-N: the size of nodes "<<endl;
            cout<<"-m: the minimum degree "<<endl;
            cout<<"-S: the number of networks you wish to create. "<<endl;
            cout<<"-g: the value of gamma "<<endl;
        }
    }
    return 1;
}
