//
// Created by slashlight on 15.05.2024.
//
#include <vector>
#include <unordered_set>
#include "IGraph.h"
#ifndef ALGOS_SETGRAPH_H
#define ALGOS_SETGRAPH_H


class SetGraph : public IGraph {
public:
    SetGraph( int vertexCount );
    SetGraph( const IGraph& graph );
    SetGraph& operator=(const SetGraph&) = delete;

    void AddEdge( int from, int to ) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices( int vertex ) const override;
    std::vector<int> GetPrevVertices( int vertex ) const override;
private:
    std::vector< std::unordered_set<int> > adjSet;
    std::vector< std::unordered_set<int> > prevAdjSet;
};


#endif //ALGOS_SETGRAPH_H
