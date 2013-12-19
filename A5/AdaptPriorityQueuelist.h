#include <vector>
#include <fstream>
#include <sstream>
#include "BinaryHeap.h"
#include "Item.h"
#include <list>
#include <algorithm>
// include the templated class Item here
// include the templated class PQComp here

using namespace std;



template<typename ElemType>
class AdaptPriorityQueuelist
{
protected:
    typedef Item<ElemType> item;
    typedef PQComp<ElemType> pqcomp;
    pqcomp comp;
private:

    list<item> T;
    static const int
    DEF_SIZE = 26;
    bool sorted;

public: // class PriorityQueue cont.
    AdaptPriorityQueuelist( int size = DEF_SIZE) : T(size),sorted(true) { }
    AdaptPriorityQueuelist(AdaptPriorityQueuelist& pq){
        T=pq.T;
        sorted=pq.sorted;}
    bool isEmpty() const
    {
        return T.empty();
    }
    void insertItem(const int k,const ElemType& e, Locator<ElemType>& l)
    {
        item i=item(k, e);
        i.setLocator(l);//set pointer before because insert creates a copy
        if(comp(i,T.front()))
            sorted=false;
        T.push_back(i);
        l.setItem_ptr(&T.back()); //set new position in locator
    }
    const ElemType& minElement() throw (EmptyPriorityQueue)
    {
        if (T.empty())
            throw EmptyPriorityQueue();
        if (!sorted){
            T.sort();
            sorted=true;
            }
        return T.front().getElem();
    }
    const int minKey() throw (EmptyPriorityQueue)
    {
        if (T.isEmpty())
            throw EmptyPriorityQueue();
        if (!sorted){
            T.sort();
            sorted=true;
            }
        return T.front().getKey();
    }
    Locator<ElemType>* min()throw (EmptyPriorityQueue)
    {
        if (T.empty())
            throw EmptyPriorityQueue();
         if (!sorted){
            T.sort();
            sorted=true;
            }
        return T.front().getLocator();
}


    void remove(Locator<ElemType>& l){
             if (T.empty())
            throw EmptyPriorityQueue();
            replaceKey(l,-999999); //replace key with negative vaule
         if (!sorted){
            T.sort();
            sorted=true;
            }
        T.pop_front();
        l.setItem_ptr(NULL);
    }


    Locator<ElemType> replaceKey(Locator<ElemType>&l, int k){
            l.getItem()->setKey(k);
            T.sort();//reorder
            sorted=true;
            return l;
    }

    int CreatePriorityQueue(string filename, Locator<ElemType>* loc_array){
        T.clear();
        int counter=0;
        string temp;
        int key=0;
        ElemType elem=0; // no initialization for ambiguity
        ifstream in (filename.c_str());
        vector<int> keys; //store all keys
        vector<ElemType> elems; //and all elements
        getline(in,temp,' ');
        while (!in.eof()&&in.good()){ //
            ++counter;
            key=atoi(temp.c_str());
            keys.push_back(key);
            getline(in,temp);
            elem=atoi(temp.c_str()); //stringstream conversion wouldnt work for some reason
            elems.push_back(elem);
            getline(in,temp,' ');
            }
         //now that we know total size of list we can create dynamic array

        for (int i=0;i<counter;++i){ //insert one by one with the vectors and arrays as arguments
            int k=keys[i];
            int e=elems[i];
            insertItem(keys[i],elems[i],loc_array[i]);
        }
        return counter;
    }


};

template<typename ElemType>
void printPQ(AdaptPriorityQueuelist<ElemType>& pq, Locator<ElemType>* l, int size){
    Locator<ElemType>* temp=new Locator<ElemType>[size];
    for (int i=0;i<size;++i)
        temp[i]=l[i];//save old vaules
    Item<ElemType>* e;
    while(!pq.isEmpty()){
        e=pq.min()->getItem();
        cout<<*e;//output minimum
        pq.remove(*pq.min());//remove minimum
    }
     for (int i=0;i<size;++i)
        l[i]=temp[i];//save old vaules
    delete temp; //delete temp vaules

}

