// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
// Найдите количество различных кратчайших путей между заданными вершинами.

#include <iostream>
#include <vector>
#include <queue>

struct IGraph {
    virtual ~IGraph() = default;

    virtual void AddEdge( int from, int to ) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetRelVertices( int vertex ) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph( int vertexCount );

    virtual void AddEdge( int from, int to ) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetRelVertices( int vertex ) const override;
private:
    std::vector<std::vector<int>> adjList;
};

ListGraph::ListGraph(int vertexCount) {
    adjList.resize( vertexCount );
}

void ListGraph::AddEdge(int from, int to) {
    adjList[from].push_back( to );
    adjList[to].push_back( from );
}

int ListGraph::VerticesCount() const {
    return adjList.size();
}

std::vector<int> ListGraph::GetRelVertices(int vertex) const {
    return adjList[vertex];
}

int BFS (const IGraph& graph, int vertex, int to) {
    std::vector<bool> visited( graph.VerticesCount(), false );
    std::queue<int> bfsQ;
    std::vector<int> dist( graph.VerticesCount(), 0 );
    std::vector<int> numOfShortestPaths( graph.VerticesCount(), 0 );
    int wave = 1;
    numOfShortestPaths[vertex] = 1;
    bfsQ.push( vertex );
    bfsQ.push( -1 );
    visited[vertex] = true;
    while ( !bfsQ.empty() ) {
        int current = bfsQ.front();
        bfsQ.pop();
        if (current == -1) {
            ++wave;
            if (!bfsQ.empty())
                bfsQ.push(-1);
        } else {
            std::vector<int> adjList = graph.GetRelVertices( current );
            for (int i = 0; i < adjList.size(); ++i) {
                if (!visited[adjList[i]]) {
                    bfsQ.push(adjList[i]);
                    dist[adjList[i]] = wave;
                    visited[adjList[i]] = true;
                    numOfShortestPaths[adjList[i]] += numOfShortestPaths[ current ];
                } else if (dist[adjList[i]] == wave) {
                    numOfShortestPaths[adjList[i]] += numOfShortestPaths[ current ];
                }
            }
        }
    }

    return numOfShortestPaths[to];
}

int main() {
    int vertex, arcs;
    std::cin >> vertex >> arcs;
    IGraph* graph = new ListGraph(vertex);
    int from, to;
    for (int i = 0; i < arcs; ++i) {
        std::cin >> from >> to;
        graph->AddEdge(from, to);
    }
    std::cin >> from >> to;

    std::cout << BFS( *graph, from, to );
    return 0;
}
