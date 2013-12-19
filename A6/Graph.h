#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

//class Edge;
//class Vertex;

class Graph
{

private:
    int numvert;
    vector<Vertex*> vertList;
    vector<Edge*> edgeList;
public:



    Graph(string filename)
    {
        numvert=0;
        ifstream ifs(filename.c_str());
        int vertnum;
        ifs>>vertnum;

        for(int i=0; i<vertnum; i++) // push all vertices into the vertex vector before assigning the in and out list
            addVertex();

        int svert,evert,weit;
        ifs>>svert;
        while(svert!=-1)//check for end of input
        {
            ifs>>evert;
            while(evert!=-1)//check for end of input
            {
                ifs>>weit; // one weight means one edge
                addEdge(svert,evert,weit);
                ifs>>evert;
            }
            ifs>>svert;
        }
        ifs.close();
    }
    ~Graph()
    {
        for(int i = 0; i < vertList.size(); i++)
            delete vertList[i];
        for(int i = 0; i < edgeList.size(); i++)
            delete edgeList[i];
    }

    vector<Vertex*> getVertices() const
    {
        return vertList;
    }
    vector<Vertex*> getAdjacentList(Vertex* v){
        vector<Vertex*> temp_list;
        vector<Edge*> out=v->getOutEdges();
        for (int i=0; i<out.size(); ++i)
            temp_list.push_back(out[i]->geteVertP());
        return temp_list;
    }
    int getNumVertices()
    {
        return numvert;
    }
    int addEdge(int source, int dest, int weight){
         Edge *tempedge = new Edge(vertList[source-1],vertList[dest-1],weight); // new edge
                edgeList.push_back(tempedge);
                vertList[source-1]->outList.push_back(tempedge); // update verticy to contain edge info
                vertList[dest-1]->inList.push_back(tempedge);
    }
    int addVertex()
    {
        Vertex *vert = new Vertex(++numvert); //vertex id is just 1 to number of vertices
        vertList.push_back(vert);
        return numvert;
    }
    void PrintAdjList(Vertex* v)
    {
        cout<<v->getID()<<" : ";
        vector<Edge*> out=v->getOutEdges();
        for (int i=0; i<out.size(); ++i)
            cout<<out[i]->geteVertP()->id<<" ";
        cout<<"\n\n";
    }
    void PrintGraph() // print out all the edges and associated vertices in the entire graph
    {
        cout<<"ADJACENY LIST STYLE:\n";
        for (int i=0; i<vertList.size(); ++i)
        {
            PrintAdjList(vertList[i]);

        }
    }
};
#endif
