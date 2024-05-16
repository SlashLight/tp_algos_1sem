#include "SetGraph.h"

SetGraph::SetGraph(const IGraph &graph) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> adjList = graph.GetNextVertices( i );
        std::vector<int> prevAdjList = graph.GetPrevVertices( i );
        adjMap[i] = adjList;
        prevAdjMap[i] = prevAdjList;
    }
}

void SetGraph::AddEdge(int from, int to) {
    adjMap[from].push_back(to);
    prevAdjMap[to].push_back( from );
}

int SetGraph::VerticesCount() const {
    return adjMap.size();
}

std::vector<int> SetGraph::GetNextVertices( int const vertex ) const {
    return adjMap.at( vertex );
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    return prevAdjMap.at( vertex );
}
