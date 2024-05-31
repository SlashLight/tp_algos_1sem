#include <iostream>
#include "IGraph.h"
#include "ListGraph.cpp"
#include "SetGraph.cpp"
#include "MatrixGraph.cpp"
#include "ArcGraph.cpp"

int main() {
    int vertex, arcs;
    std::cin >> vertex >> arcs;
    IGraph* list = new ListGraph(vertex);
    IGraph* set = new SetGraph(vertex);
    IGraph* matrix = new MatrixGraph(vertex);
    IGraph* arc = new ArcGraph(vertex);
    for (int i = 0; i < arcs; ++i) {
        int from, to;
        std::cin >> from >> to;
        list->AddEdge(from, to);
        set->AddEdge(from, to);
        matrix->AddEdge(from, to);
        arc->AddEdge(from, to);
    }

    for (int i = 0; i < vertex; ++i) {
        std::vector<int> vec = list->GetNextVertices(i);
        std::cout << i << ": ";
        for (int j = 0; j < vec.size(); ++j) {
            std::cout << vec[j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < vertex; ++i) {
        std::vector<int> vec = set->GetNextVertices(i);
        std::cout << i << ": ";
        for (int j = 0; j < vec.size(); ++j) {
            std::cout << vec[j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < vertex; ++i) {
        std::vector<int> vec = matrix->GetNextVertices(i);
        std::cout << i << ": ";
        for (int j = 0; j < vec.size(); ++j) {
            std::cout << vec[j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < vertex; ++i) {
        std::vector<int> vec = arc->GetNextVertices(i);
        std::cout << i << ": ";
        for (int j = 0; j < vec.size(); ++j) {
            std::cout << vec[j] << " ";
        }
        std::cout << std::endl;
    }

}
