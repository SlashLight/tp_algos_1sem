#include "ArcGraph.h"

ArcGraph::ArcGraph( int _vertexCount ) {
    vertexCount = _vertexCount;
    arcList.resize( vertexCount );
}

void ArcGraph::AddEdge(int from, int to) {
    std::pair<int, int> elem = {from, to};
    arcList.push_back(elem);
}

int ArcGraph::VerticesCount() const {
    return vertexCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (const auto & i : arcList) {
        if( i.first == vertex ) {
            res.push_back(i.second);
        }
    }

    return res;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (const auto & i : arcList) {
        if( i.second == vertex ) {
            res.push_back(i.first);
        }
    }

    return res;
}
