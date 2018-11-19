#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"
using namespace std;

bool graph::importGraph(ifstream &in)
{
    string vertex1, vertex2;
    int dist;

    while (in >> vertex1 >> vertex2 >> dist)
    {
        insert(vertex1, vertex2, dist);
    }

    return true;
}

graph::graph()
{
    vertices = new hashTable(500000);
    capacity = 0;
}

void graph::insert(const string &vertex1, const string &vertex2, int dist)
{
    vertex *temp1, *temp2;
    edge newEdge;

    if (!vertices->contains(vertex1))
    {
        temp1 = new vertex;
        temp1->name = vertex1;
        temp1->known = false;
        temp1->dist = INT_MAX;
        vertexList.push_back(temp1);
        vertices->insert(vertex1, temp1);
        capacity++;
    }
    else
    {
        temp1 = (vertex *)vertices->getPointer(vertex1);
    }

    if (!vertices->contains(vertex2))
    {
        temp2 = new vertex;
        temp2->name = vertex2;
        temp2->known = false;
        temp2->dist = INT_MAX;
        vertexList.push_back(temp2);
        vertices->insert(vertex2, temp2);
        capacity++;
    }
    else
    {
        temp2 = (vertex *)vertices->getPointer(vertex2);
    }
    newEdge.dest = temp2;
    newEdge.cost = dist;

    temp1->adj.push_back(newEdge);
}

bool graph::containsVertex(const string &vertex)
{
    return (vertices->contains(vertex));
}

bool graph::dijkstra(const string &startingV)
{
    vertex *start = (vertex *)vertices->getPointer(startingV);
    start->dist = 0;
    start->path.push_back(startingV);

    heap distHeap(capacity);
    distHeap.insert(startingV, start->dist, start);
    for (list<vertex *>::const_iterator it = vertexList.begin(), end = vertexList.end(); it != end; ++it)
    {
        if ((*it)->name != startingV)
        {
            distHeap.insert((*it)->name, (*it)->dist, *it);
        }
    }

    vertex *temp;

    for (int i = 0; i < capacity; ++i)
    {
        distHeap.deleteMin(nullptr, nullptr, &temp);
        for (list<edge>::const_iterator it = temp->adj.begin(), end = temp->adj.end(); it != end && temp->dist != INT_MAX; ++it)
        {
            if (!it->dest->known && it->dest->dist > (it->cost + temp->dist))
            {
                it->dest->path.clear();
                it->dest->path.insert(it->dest->path.begin(), temp->path.begin(), temp->path.end());
                it->dest->path.push_back(it->dest->name);

                it->dest->dist = (it->cost + temp->dist);
                distHeap.setKey(it->dest->name, (it->cost + temp->dist));
            }
        }
        temp->known = true;
    }

    return true;
}

void graph::printPaths(std::ofstream &out)
{
    for (list<vertex *>::const_iterator it = vertexList.begin(), end = vertexList.end(); it != end; ++it)
    {
        out << (*it)->name << ": ";

        if ((*it)->dist == INT_MAX)
        {
            out << "NO PATH" << std::endl;
        }
        else
        {
            out << (*it)->dist << " [";
            for (list<string>::const_iterator it2 = (*it)->path.begin(), end2 = (*it)->path.end(); it2 != end2; ++it2)
            {
                out << *it2;
                if (next(it2, 1) != end2)
                    out << ", ";
            }
            out << "]" << endl;
        }
    }
}
