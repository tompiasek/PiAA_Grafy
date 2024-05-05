#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>

#include "graphs/graph.hpp"

class AdjacencyMatrixGraph : public Graph
{

  public:
    // TODO: implement

    static std::unique_ptr<Graph> createGraph(std::istream& is); // TO-DO

    int addVertex(int id) override { return 0; }; // TO_DO
    void updateVertex(int id, int v) {}; // TO_DO
    void removeVertex(int id) override {}; // TO_DO

    void addEdge(int idStart, int idEnd, int w) override {}; // TO_DO
    void updateEdge(int idStart, int idEnd, int w) {}; // TO_DO
    void removeEdge(int idStart, int idEnd) override {}; // TO_DO

    std::vector<Vertex*> getNeighbours(int id) override { return std::vector<Vertex*>(); }; // TO_DO
    void checkNeighbour(int id, int n) {}; // TO_DO

    int findVertexPos(int v_id) { return 0; }; // TO_DO
    Edge* findEdge(int idStart, int idEnd) { return nullptr; }; // TO_DO
    void print() {}; // TO_DO
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
