#include "SetGraph.h"

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
