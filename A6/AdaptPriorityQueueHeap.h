#include <vector>
#include <fstream>
#include <sstream>
#include "BinaryHeap.h"
#include "Item.h"




template<typename ElemType>
class AdaptPriorityQueueHeap
{
protected:
    typedef Item<ElemType> item;
    typedef PQComp<ElemType> pqcomp;

private:

    BinaryHeap<item, pqcomp> T;
    static const int
    DEF_SIZE = 300;

public: // class PriorityQueue cont.
    AdaptPriorityQueueHeap( int size = DEF_SIZE) : T(size) { }
    bool isEmpty()
    {
        return T.isEmpty();
    }
    void insertItem( int k, ElemType e, Locator<ElemType>& l)
    {
        item i(k, e, &l);
        i.setLocator(l);//set pointer before because insert creates a copy
        T.insert(i);
    }
    ElemType& minElement() throw (EmptyPriorityQueue)
    {
        if (T.isEmpty())
            throw EmptyPriorityQueue();
        return T.findMin().getElem();
    }
    int minKey() throw (EmptyPriorityQueue)
    {
        if (T.isEmpty())
            throw EmptyPriorityQueue();
        return T.findMin().getKey();
    }
    Locator<ElemType>* min()throw (EmptyPriorityQueue)
    {
        if (T.isEmpty())
            throw EmptyPriorityQueue();
        return T.findMin().getLocator();
    }
    void removeMin() throw (EmptyPriorityQueue)
    {
        if (T.isEmpty())
            throw EmptyPriorityQueue();
        T.deleteMin();
    }
    item& minItem() throw (EmptyPriorityQueue)
    {
        if(T.isEmpty())
            throw EmptyPriorityQueue();
        return T.findMin();
    }

    Locator<ElemType> remove(Locator<ElemType>& l)
    {
        l.getItem()->setKey(-999999); //negative key to give smallest value
        T.buildHeap();//reorder
        T.deleteMin();//remove minimum  which should now be l
        return l;
    }

    Locator<ElemType> replaceKey(Locator<ElemType>&l, int k)
    {
        l.getItem()->setKey(k);
        T.buildHeap();//reorder
    }

    int CreatePriorityQueue(string filename, Locator<ElemType>* loc_array)
    {
        int counter=0;
        string temp;
        int key=0;
        ElemType elem=0; // no initialization for ambiguity
        ifstream in (filename.c_str());
        vector<int> keys; //store all keys
        vector<ElemType> elems; //and all elements
        getline(in,temp,' ');
        while (!in.eof()&&in.good())  //
        {
            ++counter;
            key=atoi(temp.c_str());
            keys.push_back(key);
            getline(in,temp);
            elem=atoi(temp.c_str()); //stringstream conversion wouldnt work for some reason
            elems.push_back(elem);
            getline(in,temp,' ');
        }
        //now that we know total size of list we can create dynamic array

        for (int i=0; i<counter; ++i) //insert one by one with the vectors and arrays as arguments
        {
            int k=keys[i];
            int e=elems[i];
            insertItem(keys[i],elems[i],loc_array[i]);
        }
        return counter;
    }



};

template<typename ElemType>
void printPQ(AdaptPriorityQueueHeap<ElemType>& pq, Locator<ElemType>* l, int size)
{
    Locator<ElemType>* temp=new Locator<ElemType>[size];
    for (int i=0; i<size; ++i)
        temp[i]=l[i];//save old vaules
    Item<ElemType>* e;
    while(!pq.isEmpty())
    {
        e=pq.min()->getItem();
        cout<<*e;//output minimum
        pq.remove(*pq.min());//remove minimum
    }
    for (int i=0; i<size; ++i)
        l[i]=temp[i];//save old vaules
    delete temp; //delete temp vaules


}




