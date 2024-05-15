//
// Created by slashlight on 15.05.2024.
//
#include <vector>
#ifndef ALGOS_IGRAPH_H
#define ALGOS_IGRAPH_H

struct IGraph {
    virtual ~IGraph() = default;

    virtual void AddEdge( int from, int to ) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices( int vertex ) const = 0;
    virtual std::vector<int> GetPrevVertices( int vertex ) const = 0;
};

#endif //ALGOS_IGRAPH_H
