// #pragma once
#include "Vertex.h"

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <vector>

using namespace std;


class Vertex;

class Edge
{

private:

    Vertex *sVertP; // source vertex pointer
    Vertex *eVertP;  // end vertex pointer
    int weight; // edge weight
public:

    Edge()
    {
        sVertP=NULL;
        eVertP=NULL;
        weight==-1;
    }
    Edge(Vertex* svert, Vertex* evert,int weit)
    {
        sVertP=svert;
        eVertP=evert;
        weight=weit;
    }
    Edge(Edge& e)
    {
        sVertP=e.sVertP;
        eVertP=e.eVertP;
        weight=e.weight;
    }
    Edge& operator = (Edge& e)
    {
        sVertP=e.sVertP;
        eVertP=e.eVertP;
        weight=e.weight;
    }

    int getWeight()
    {
        return weight;
    }
    Vertex* getsVertP()
    {
        return sVertP;
    }
    Vertex* geteVertP()
    {
        return eVertP;
    }
};

#endif
