//
// Created by slashlight on 15.05.2024.
//
#include <vector>
#include "IGraph.h"
#ifndef ALGOS_MATRIXGRAPH_H
#define ALGOS_MATRIXGRAPH_H


class MatrixGraph : public IGraph {
public:
    MatrixGraph( int vertexCount );
    MatrixGraph( const IGraph& graph );
    MatrixGraph& operator=(const MatrixGraph&) = delete;

    void AddEdge( int from, int to );
    int VerticesCount() const;
    std::vector<int> GetNextVertices( int vertex ) const;
    std::vector<int> GetPrevVertices( int vertex ) const;
private:
    std::vector<std::vector<int>> matrix;
};


#endif //ALGOS_MATRIXGRAPH_H
