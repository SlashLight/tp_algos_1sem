//
// Created by slashlight on 15.05.2024.
//
#include <vector>
#ifndef ALGOS_MATRIXGRAPH_H
#define ALGOS_MATRIXGRAPH_H


class MatrixGraph {
public:
    MatrixGraph( int vertexCount );

    void AddEdge( int from, int to );
    int VerticesCount() const;
    std::vector<int> GetNextVertices( int vertex ) const;
    std::vector<int> GetPrevVertices( int vertex ) const;
private:
    std::vector<std::vector<int>> matrix;
};


#endif //ALGOS_MATRIXGRAPH_H
