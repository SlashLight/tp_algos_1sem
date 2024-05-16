//
// Created by slashlight on 15.05.2024.
//
#include <vector>
#include <map>
#include "IGraph.h"
#ifndef ALGOS_SETGRAPH_H
#define ALGOS_SETGRAPH_H


class SetGraph : public IGraph {
public:
    SetGraph( int vertexCount ) {};

    void AddEdge( int from, int to ) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices( int vertex ) const override;
    std::vector<int> GetPrevVertices( int vertex ) const override;
private:
    std::map< int, std::vector<int> > adjMap;
    std::map< int, std::vector<int> > prevAdjMap;
};


#endif //ALGOS_SETGRAPH_H
