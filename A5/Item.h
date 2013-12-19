#ifndef ITEM_H
#define ITEM_H
template<typename ElemType> class Locator;

template<typename ElemType>
class Item {
private:
Locator<ElemType>* position;
int key;
ElemType elem;
public:
Item( const int k=0, const ElemType& e=ElemType(), Locator<ElemType>* p=NULL): key(k), elem(e), position(p) { }
//constructor
const int getKey() const { return key; }
const ElemType& getElem() const { return elem; }
Locator<ElemType>* getLocator() const {return position;}
void setKey( const int k) { key = k; }
void setElem( const ElemType& e) { elem = e; }
void setLocator(Locator<ElemType> &l) {position=&l;}

Item<ElemType> operator = (const Item<ElemType>& e){
        position=e.position;
        key=e.key;
        elem=e.elem;
    //    position->setItem_ptr(this); //rewrote assignment operator to update the locator to new position internally
}

int operator > (const Item<ElemType>& e){
    return key>e.getKey();}
int operator < (const Item<ElemType>& e){
    return key<e.getKey();}


};


template<typename ElemType> class Locator{

    Item<ElemType>* item_ptr;
    public:
    Locator(Item<ElemType>* i=NULL):item_ptr(i){}


    Item<ElemType>* getItem(){return item_ptr;}

    void setItem_ptr(Item<ElemType>* ptr){ item_ptr=ptr;}
};

template<typename ElemType> class PQComp{
public:

int operator ()( const Item<ElemType>& e1, const Item<ElemType>& e2) {

return e1.getKey() - e2.getKey();
}


};

template<typename ElemType>
ostream& operator <<(ostream& os, Item<ElemType>& i){
    os<<"key: "<<i.getKey()<<"  "<<"Elem: "<<i.getElem()<<endl;
}

class EmptyPriorityQueue{
public:
    string s;
    EmptyPriorityQueue(){
        s="EmptyPriorityQueue";
        }
};

#endif // ITEM_H
