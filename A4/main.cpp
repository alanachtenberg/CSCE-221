#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "BinaryTree.h"

void Node_traversal(BinaryNode* node, int* node_count, int* total_search)
{

    if (node->getLeft() != NULL)
        Node_traversal(node->getLeft(), node_count, total_search);
    *node_count+=1;
    *total_search=*total_search+node->getSearchCost();
    cout<<"traversal "<<node->getElem()<<" ["<<node->getSearchCost()<<"]\n";

    if (node->getRight()!= NULL)
        Node_traversal(node->getRight(), node_count, total_search);

}

void Node_printvec(BinaryNode* node, int** vec, int level, int& placement)
{



    if (node->getLeft() != NULL)
    {
        Node_printvec(node->getLeft(),vec,level+1, placement);
    }
    vec[level][placement]=node->getElem();
    if (node->getRight()!= NULL)
    {

        Node_printvec(node->getRight(),vec, level+1, ++placement);
    }
}


int main(int argc, char ** argv)
{
    string file="4p.txt";
    int c;

    while ((c = getopt(argc, argv, "f:")) != -1)
        switch (c)
        {
        case 'f':
            file=optarg;
            break;
        case '?':
            if (optopt == 'c')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
            {
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            }
            else
            {
                fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
            }
            return 1;
        default:
            abort ();
        }


    cout<<"command line file input option example -f 1p.txt\ndefault is 3p\n";

    string fileopen="test_files/"+file;
    ifstream in(fileopen);
    if (!in.is_open())
        cout<<"file failed to open\n";

    BinaryTree tree;
    string input;
    cout<<"input:\n";
    while ( getline(in,input))
    {
        if (in.eof())
            break;
        tree.insert(atoi(input.c_str()));
        cout<<input<<endl;
    }
    cout<<endl;



    int node_count=0;
    int total_search=0;
    int test=tree.get_Root()->getElem();
 //   cout<<" testing root  ------"<<test<<"   "<<tree.get_Root()->getSearchCost()<<endl;

    int rem=0;
    char option='0';

    cout<<"would you like to remove a node y or n\n";
        while(1){
            cin>>option;
            if (option=='y'||option=='n')
                break;
            cin.clear();
            cin.ignore(1000,'\n');
        }
    if (option=='y'){
        cout<<"input integer to remove from tree\n";
        while (1){
            cin>>rem;
            if (rem>0 && rem<100000)
                break;
            cin.clear();
            cin.ignore(1000,'\n');
            rem=0;
        }

        tree.remove(rem);
}
    Node_traversal(tree.get_Root(), &node_count, &total_search );

    file="results/"+file;
    cout<<"printing results to "<<file<<endl;
    ofstream out(file);
    ofstream res("results/info.txt",ios_base::app); // data collection
    res<<node_count;
    res<<" "<<(double)total_search/node_count<<endl;

    out<<"node count: "<<node_count<<endl;
    out<<"average search cost: "<<(double)total_search/node_count<<endl;

    if (tree.height()<17)
    {
        int* printvec[100];
        for (int i=0; i<100; ++i)
        {
            int* a =new int[100000] {0};
            printvec[i]=a;
        }

        int level=0;
        int placement=0;
        Node_printvec(tree.get_Root(), printvec , level, placement);
        for (int i=0; i<tree.height(); ++i)
        {
            for (int j=0; j<pow(2,tree.height()-1); ++j)
            {
                if (printvec[i][j]!=0)
                    out<<printvec[i][j]<<" ";
                else
                    out<<"_ ";
            }
            out<<" ENDL\n";
        }
    }
    else out<<"tree height was greater than 16 gracefully declined to destroy text editor\n";




    return 0;
}
