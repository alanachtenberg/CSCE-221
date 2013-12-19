#include "BinaryHeap.h"
#include "Item.h"
// include the templated class Item here
// include the templated class PQComp here

class EmptyPriorityQueue{
public:
    string s;
    EmptyPriorityQueue(){
        s="EmptyPriorityQueue";
        }
};

template<typename ElemType>
class PriorityQueue
{
protected:
    typedef Item<ElemType> item;
    typedef PQComp<ElemType> pqcomp;

private:

    BinaryHeap<item, pqcomp> T;
    static const int
    DEF_SIZE = 10;

public: // class PriorityQueue cont.
    PriorityQueue( int size = DEF_SIZE) : T(size) { }
    bool isEmpty() const
    {
        return T.isEmpty();
    }
    void insertItem(const int k,const ElemType& e)
    {
        item i(k, e);
        T.insert(i);

    }
    const ElemType& minElement() throw (EmptyPriorityQueue)
    {
        if (T.isEmpty())
            throw EmptyPriorityQueue();
        return T.findMin().getElem();
    }
    const int minKey() throw (EmptyPriorityQueue)
    {
        if (T.isEmpty())
            throw EmptyPriorityQueue();
        return T.findMin().getKey();
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
        return T.findMin();}
};

