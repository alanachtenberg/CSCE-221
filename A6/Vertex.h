#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"

using namespace std;

class Graph;
class Edge;

class Vertex
{

private:
    vector<Edge*> inList; // source vertex
    vector<Edge*> outList; // end vertex
    int id;
    friend class Graph;
public:

    Vertex()
    {
        id=-1;
    }
    Vertex(int sid)
    {
        id=sid;
    };
    Vertex(Vertex& v)
    {
        id=v.id;
        inList=v.inList;
        outList=v.outList;
    }
    Vertex& operator=(Vertex& v)
    {
        id=v.id;
        inList=v.inList;
        outList=v.outList;
        return *this;

    }
    int getID() const
    {
        return id;
    }
    vector<Edge*> getOutEdges() const
    {
        return outList;
    }
    vector<Edge*> getInEdges() const
    {
        return inList;
    }
};

#endif
