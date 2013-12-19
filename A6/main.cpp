int heap_tmp=0, heap_comp=0;
int key_tmp=0, key_comp=0;
int counter=0;

#include <iostream>
#include <strstream>
#include <string>
#include "Graph.h"
#include "AdaptPriorityQueueHeap.h""
using namespace std;


string itoa(int a){
    stringstream ss;
    ss<<a;
    string temp;
    ss>>temp;
    return temp;
}

void print_id(Locator<Vertex*>* l){
    cout<<l->getItem()->getElem()->getID();
}



int main()
{       // you can use the following code to test your graph.
    // you can also change your input file to do more testing
    // verify the results


    string str("random_sparse.txt");
    Graph graph(str);
    const int NUM_V=graph.getNumVertices();
    const int MAX_SIZE=99999999;
    Vertex* V_temp;
    graph.PrintGraph();
    int source_v;
    int dest_v;
    cout<<endl;
    cout<<"please input vertex source and destination id, value must be between 1 and "<<NUM_V<<endl;
    while(1){
        cin>>source_v;
        cin>>dest_v;
        --source_v;
        --dest_v;
        cin.clear();
        cin.ignore();
        if (source_v<NUM_V&&source_v>=0)
            if(dest_v<NUM_V&&dest_v>=0)
                break;
            else cout<<"destination not in range, try again\n";
        else cout<<"source not in range, try again\n";
    }
    const int s=source_v+1; // save values
    const int d=dest_v+1;

    if (source_v==dest_v)
        cout<<"source and destination equal the same\n";
    // for extracting minimum key
    AdaptPriorityQueueHeap<Vertex*> pq;
    AdaptPriorityQueueHeap<Vertex*> pq2;
    // for updating keys in pq hash value for locator index is just the id of the vertex-1
    Locator<Vertex*>* locatorArray=new Locator<Vertex*>[NUM_V];
    // for recording shortest path
    int* shortestPathParent=new int[NUM_V];
    for (int i=0;i<NUM_V;++i)
        shortestPathParent[i]=-5;//fill array with - values, make sure source does not have a false parent at 0
    // There should be another structure for collection of vertices S
    //get items to insert into pq
    vector<Vertex*> S=graph.getVertices();


    //insert vertexs and locators with max size as key
    for(int i=0;i<NUM_V;++i){
        V_temp=S[i];
        pq.insertItem(MAX_SIZE,V_temp,locatorArray[i]); //insert vertices into priority queue
    }
    Locator<Vertex*>* locArray=new Locator<Vertex*>[NUM_V];
    for(int i=0;i<NUM_V;++i)
        locArray[i]=locatorArray[i];

    //BEGIN DIKJSTRAS ALGORITHM
    pq.replaceKey(locatorArray[source_v],0);//set source weight to 0
    cout<<"\nsource is :";
    print_id(pq.min());//check to make sure pq is working correctly
    cout<<endl;
    print_id(pq.min());

    int curWeight=0; //weight of source
    int newWeight=0; //weight of source plus edge
    int oldWeight=0; //weight of dest from other parent
    while(!pq.isEmpty()){

        Vertex* temp_v=pq.minElement();
        curWeight=pq.minKey();
        vector<Edge*> out=temp_v->getOutEdges();
        source_v=temp_v->getID();

        //RELAX EDGES
        for(int i=0;i<out.size();++i){
            newWeight=curWeight+out[i]->getWeight();//cost to dest from cur
            dest_v=out[i]->geteVertP()->getID();
            oldWeight=locatorArray[dest_v-1].getItem()->getKey(); //old cost to node
            if (newWeight<oldWeight){//the new path is shorter than the old
                key_tmp=0;
                pq.replaceKey(locatorArray[dest_v-1],newWeight);//update weight
                key_comp=key_comp+key_tmp;
                ++counter;
                //update parent status
                shortestPathParent[dest_v-1]=source_v;
            }
        }
        pq2.insertItem(pq.minKey(),pq.minElement(),locArray[source_v-1]);//make new locator and queue to save locator access
        heap_tmp=0;
        pq.removeMin();
        heap_comp=heap_comp+heap_tmp;//comparison info
    }

    //Dikjstras algorithm finished
    //print information
    stringstream ss;
    string temp;//conversions
    string output="";//output formatting
    int distance=0;//total distance
    int parent=-1;
    int mediary=d;
    while(parent!=s){
        temp=itoa(mediary);
        output=")-->"+temp+output;
        if (shortestPathParent[mediary-1]>0)
            parent= shortestPathParent[mediary-1];
        else{
            cout<<"\nno path found\n";
            return 1;
        }
        //FIND WEIGHT
        Vertex* tmpV=locArray[parent-1].getItem()->getElem();
        vector<Edge*> tmp=tmpV->getOutEdges();
        int index=0;
        int pid=tmp[index]->geteVertP()->getID();
        while(pid!=mediary){
            ++index;
            pid=tmp[index]->geteVertP()->getID();
        }
        int edgeWeight=tmp[index]->getWeight();
        distance=distance+edgeWeight;
        temp=itoa(edgeWeight);
        output=temp+output;
        output="--("+output;
        mediary=parent;
    }

    cout<<output<<endl;
    cout<<"The shortest distance between the source "<<s<<" and the destination "<<d;
    cout<<" is "<<distance<<endl;

    cout<<"average number of heap comparisons for min removal: "<<heap_comp/NUM_V<<endl;
    cout<<"average number of comparisons for replace key: "<<key_comp/counter<<endl;
    return 0;
}
