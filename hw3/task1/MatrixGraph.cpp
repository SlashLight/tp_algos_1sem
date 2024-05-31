#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertexCount) {
    matrix.resize(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        matrix[i].resize(vertexCount);
    }
}

MatrixGraph::MatrixGraph(const IGraph &graph) {
    matrix.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        matrix[i].resize(graph.VerticesCount());
        std::vector<int> adj = graph.GetNextVertices(i);
        for (int j : adj) {
            matrix[i][j] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    matrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    int n = this->VerticesCount();
    for (int i = 0; i < n; ++i) {
        if ( matrix[vertex][i] == 1 )
            res.push_back( i );
    }
    return res;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    int n = this->VerticesCount();
    for (int i = 0; i < n; ++i) {
        if ( matrix[i][vertex] == 1 )
            res.push_back( i );
    }
    return res;
}

