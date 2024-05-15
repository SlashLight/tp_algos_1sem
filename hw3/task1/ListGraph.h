//
// Created by slashlight on 15.05.2024.
//
#include <vector>
#include "IGraph.h"
#ifndef ALGOS_LISTGRAPH_H
#define ALGOS_LISTGRAPH_H


class ListGraph : public IGraph{
public:
    ListGraph( int vertexCount );

    void AddEdge( int from, int to ) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices( int vertex ) const override;
    std::vector<int> GetPrevVertices( int vertex ) const override;
private:
    std::vector<std::vector<int>> adjList;
    std::vector<std::vector<int>> prevAdjList;
};


#endif //ALGOS_LISTGRAPH_H
