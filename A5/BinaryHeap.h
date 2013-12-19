
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifndef HEAP_H
#define HEAP_H
using namespace std;
class EmptyHeap{ //exception
    public:

    string s;
    EmptyHeap(std::string ss):s(ss){};
    EmptyHeap(){
    s="error empty heap!";};
};


template<typename ElemType, typename Comp>
class BinaryHeap {
private:


Comp comp;
// Comp is a comparator class
// and comp(a,b) will compare arguments a and b
int curSize;
//number of elements in heap
ElemType* array;
//(dynamic) heap array
int length;
//the length of the array
static const int DEF_SIZE = 26;

bool orderOK;

void getNewArray(int newSize) {
    array = new ElemType[newSize];
    length = newSize;
}

public: // templated class BinaryHeap (cont)
BinaryHeap( int size = DEF_SIZE) {
//constructor
curSize = 0;
getNewArray(size);
orderOK=true;
}

ElemType& findMin() throw (EmptyHeap) {
if ( isEmpty() )
throw EmptyHeap();
return array[0];
}
bool isEmpty( ) const { return curSize == 0; }
void buildHeap();
void insert(const ElemType& x);
void deleteMin() throw (EmptyHeap);
void checkSize();
void toss(const ElemType& x);
void walkDown(int hole);
};



template<typename ElemType, typename Comp>
void BinaryHeap<ElemType,Comp>::insert( const ElemType& x) {
    if (!orderOK) { //establish heap order later
        toss(x);
        return;
    }

    checkSize( );//walk up (establish heap order now)
    int hole = curSize++;
    for ( ; hole > 0 && array[(hole-1)/2] > x; hole = (hole-1)/2){
        array[hole] = array[(hole-1)/2];
         array[hole].getLocator()->setItem_ptr(&array[hole]);
}
    array[hole] = x;
    array[hole].getLocator()->setItem_ptr(&array[hole]);

}

// double the heap array if it is full
template<typename ElemType, typename Comp>
void BinaryHeap<ElemType,Comp>::checkSize( ) {
    if (curSize == length) {
        ElemType* oldArray = array;
        getNewArray(2*curSize);
        for (int i = 0; i < curSize; i++)
            array[i] = oldArray[i];
            delete [] oldArray;
    }
}

// insert into array without maintaining heap order
template<typename ElemType, typename Comp>
void BinaryHeap<ElemType,Comp>::toss(const ElemType& x) {
    checkSize( );
    array[ curSize++ ] = x;
    if(array[(curSize-1)/2] > x)
        orderOK =false;
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType,Comp>::deleteMin( ) throw (EmptyHeap) {
array[0] = array[ --curSize ]; //decrease size
//array[0].getLocator()->setItem_ptr(&array[0]);
walkDown(0);
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType,Comp>::walkDown(int hole) {

    int child;
    ElemType key = array[hole];
    for ( ; 2*hole+1 < curSize; hole = child) {
        child = 2*hole+1;
        if (child != curSize-1 && comp(array[child], array[child+1]) > 0)
            child++;// right child = 2*hole+2
        if (comp(key, array[child]) > 0){ array[hole]=array[child];
        array[0].getLocator()->setItem_ptr(&array[0]);
        }
        else break;
}
array[hole] = key;
array[hole].getLocator()->setItem_ptr(&array[hole]);
//access pointer from array to tell the locator to point back to array
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType,Comp>::buildHeap( ) {
for (int i = (curSize-2)/2; i >= 0; i--)
    walkDown(i);
orderOK =true;
}




#endif // ITEM_H

