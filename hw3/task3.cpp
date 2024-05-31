#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <random>

class MatrixGraph {
public:
    MatrixGraph( int vertexCount );
    ~MatrixGraph() = default;
    MatrixGraph& operator=(const MatrixGraph&) = delete;

    void AddEdge( int from, int to, int w );
    std::vector<int> Dijkstra( int start );

    int VerticesCount() const;
    std::vector<int> GetNextVertices( int vertex ) const;
private:
    int** matrix;
    std::vector<int> shortestDist;
};

struct Comparator{
    bool operator() ( const std::pair<int, int>& v1, const std::pair<int, int>& v2 ) const {
        return v1.second < v2.second;
    }
};

MatrixGraph::MatrixGraph(int vertexCount) {
    //matrix.resize(vertexCount + 1);
    matrix = new int*[vertexCount + 1];
    shortestDist.resize( vertexCount + 1, TMP_MAX );
    for (int i = 0; i < vertexCount + 1; ++i) {
        matrix[i] = new int[vertexCount + 1];
        for (int j = 0; j < vertexCount + 1; ++j) {
            matrix[i][j] = 0;
        }
    }
}

/*MatrixGraph::~MatrixGraph() {

}*/

void MatrixGraph::AddEdge(int from, int to, int w) {
    if ( matrix[from][to] == 0 || matrix[from][to] > w ) {
        matrix[from][to] = w;
        matrix[to][from] = w;
    }
}

int MatrixGraph::VerticesCount() const {
    return shortestDist.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    int n = VerticesCount();
    for (int i = 0; i < n; ++i) {
        if ( matrix[vertex][i] != 0 )
            res.push_back( i );
    }
    return res;
}

std::vector<int> MatrixGraph::Dijkstra(int start) {
    shortestDist[start] = 0;
    std::pair<int, int> vertWithDist( shortestDist[start], start );
    std::set< std::pair<int, int> > queue;
    queue.insert( vertWithDist );
    while ( !queue.empty() ) {
        int vert = queue.begin()->second;
        queue.erase(queue.begin());
        std::vector<int> adj = GetNextVertices(vert);
        for (int & i : adj) {
            if ( shortestDist[i] == TMP_MAX ) {
                auto w = matrix[vert][i];
                shortestDist[i] = shortestDist[vert] + matrix[vert][i];
                if ( shortestDist[i] < 0 ) {
                    std::cout<<"";
                }
                auto sd = shortestDist[i];
                auto elem = std::pair<int, int>(shortestDist[i], i) ;
                queue.insert( elem );
            } else if ( shortestDist[i] > shortestDist[vert] + matrix[vert][i] ) {
                auto w = matrix[vert][i];
                auto elem = std::pair<int, int>(i, shortestDist[i]) ;
                //auto pelem = queue.find( elem );
                queue.erase( elem );
                shortestDist[i] = shortestDist[vert] + matrix[vert][i];
                if ( shortestDist[i] < 0 ) {
                    std::cout<<"";
                }
                queue.insert( std::pair<int, int>( shortestDist[i], i) );
            }
        }
    }

    return shortestDist;
}

int main() {
    int cities, roads;
    std::cin >> cities >> roads;
    auto* graph = new MatrixGraph(cities);

    for (int i = 0; i < roads; ++i) {
        int from, to, v;
        std::cin >> from >> to >> v;
        graph->AddEdge(from, to, v);
    }

    int s, e;
    std::cin >> s >> e;
    std::vector<int> shortestDist(cities);
    shortestDist = graph->Dijkstra(s);
    std::cout << shortestDist[e];
    delete graph;
}