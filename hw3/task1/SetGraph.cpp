#include "SetGraph.h"

SetGraph::SetGraph(int vertexCount) : adjSet( vertexCount ), prevAdjSet( vertexCount ) {}

SetGraph::SetGraph(const IGraph &graph) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> adjacent = graph.GetNextVertices(i);
        for ( int &adj : adjacent ) {
            adjSet[i].insert(adj);
        }
        adjacent = graph.GetPrevVertices(i);
        for ( int &adj : adjacent ) {
            adjSet[i].insert(adj);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    adjSet[from].insert(to);
    prevAdjSet[to].insert( from );
}

int SetGraph::VerticesCount() const {
    return adjSet.size();
}

std::vector<int> SetGraph::GetNextVertices( int const vertex ) const {
    return std::vector<int>(adjSet[vertex].begin(), adjSet[vertex].end());
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    return std::vector<int>(prevAdjSet[vertex].begin(), prevAdjSet[vertex].end());
}
