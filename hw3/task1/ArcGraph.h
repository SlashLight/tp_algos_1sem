//
// Created by slashlight on 15.05.2024.
//
#include <vector>
#include "IGraph.h"
#ifndef ALGOS_ARCGRAPH_H
#define ALGOS_ARCGRAPH_H


class ArcGraph : public IGraph {
public:
    ArcGraph( int _vertexCount );

    void AddEdge( int from, int to );

    int VerticesCount() const;

    std::vector<int> GetNextVertices( int vertex ) const;
    std::vector<int> GetPrevVertices( int vertex ) const;
private:
    std::vector<std::pair<int, int>> arcList;
    int vertexCount;
};


#endif //ALGOS_ARCGRAPH_H
