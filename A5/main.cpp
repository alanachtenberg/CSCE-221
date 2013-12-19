
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "AdaptPriorityQueueHeap.h"
#include "AdaptPriorityQueuelist.h"

/*

//key (distance), element (stops) to the city
2467 2 // SFO
3288 2 // LAX
621 1 // ORD
1423 1 // DFW
84 0 // JFK
371 0 // BOS
328 0 // PVD
0 0 // BWI
946 1 // MIA
*/
int hash_city(char c){
    return c-'A';
}

int main()
{

    Locator<int>* locators_l=new Locator<int>[26];
    Locator<int>* locators_h=new Locator<int>[26];
    AdaptPriorityQueuelist<int> PQlist;
    AdaptPriorityQueueHeap<int> PQheap;

    int l_size=PQlist.CreatePriorityQueue("test.txt",locators_l); //loc_size is the size of locator array
    int h_size=PQheap.CreatePriorityQueue("test.txt",locators_h); //loc_size is the size of locator array
    cout<<"Priority Queue Creation done\n\n"; // CreatePriorityQueue initialized locator array as well as filling Queue
    cout<<"list implementation"<<endl;
    printPQ(PQlist,locators_l, l_size); //uses min() and remove(min()) to display
    cout<<endl;//list and heap are not maintained after output
    cout<<"heap implementation"<<endl;
    printPQ(PQheap,locators_h,h_size); //perserves locators by saving temp value and reupdating still
    cout<<endl;

    PQlist.insertItem(2467,2,locators_l[hash_city('S')]);
    PQlist.insertItem(3288,2,locators_l[hash_city('L')]);
    PQlist.insertItem(621,1,locators_l[hash_city('O')]);
    PQlist.insertItem(1423,1,locators_l[hash_city('D')]);
    PQlist.insertItem(84,0,locators_l[hash_city('J')]);
    PQlist.insertItem(371,0,locators_l[hash_city('B')]);
    PQlist.insertItem(328,0,locators_l[hash_city('P')]);
    PQlist.insertItem(0,0,locators_l[hash_city('W')]);
    PQlist.insertItem(946,1,locators_l[hash_city('M')]);

    PQheap.insertItem(2467,2,locators_h[hash_city('S')]);
    PQheap.insertItem(3288,2,locators_h[hash_city('L')]);
    PQheap.insertItem(621,1,locators_h[hash_city('O')]);
    PQheap.insertItem(1423,1,locators_h[hash_city('D')]);
    PQheap.insertItem(84,0,locators_h[hash_city('J')]);
    PQheap.insertItem(371,0,locators_h[hash_city('B')]);
    PQheap.insertItem(328,0,locators_h[hash_city('P')]);
    PQheap.insertItem(0,0,locators_h[hash_city('W')]);
    PQheap.insertItem(946,1,locators_h[hash_city('M')]);

    AdaptPriorityQueuelist<int> temp_pql(PQlist); //save temp value to print
   // AdaptPriorityQueueHeap<int> temp_pqh=PQheap;

    printPQ(temp_pql,locators_l, l_size); //uses min() and remove(min()) to display
    cout<<endl<<endl;//list and heap are not maintained after output


    cout << "replace key of LAX by 2658:" << endl;
    PQheap.replaceKey(locators_h['L'-'A'],2658); //previously was 3288
    cout<<endl;
    printPQ(PQheap,locators_h,h_size); //perserves locators by saving temp value and reupdating still

    return 0;
}
