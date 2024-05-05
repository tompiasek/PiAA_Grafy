#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>

#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // std::cout<< "Tu wykonujemy testy efektywności algorytmów"<<std::endl;

    ifstream file("C:\\Users\\tompi\\source\\repos\\PiAAGrafy\\sp_data\\graph\\graphV10D0.5.txt");

    if (!file.is_open()) {
		std::cerr << "Error: file not opened" << std::endl;
        cout << "Error: file not opened" << endl;
		return 1;
	}

    std::unique_ptr<Graph> graph = AdjacencyListGraph::createGraph(file);
    file.clear();
    file.seekg(0, ios::beg);
    std::unique_ptr<Graph> graphM = AdjacencyMatrixGraph::createGraph(file);

    graphM->print();

    if (auto graphM_child = dynamic_cast<AdjacencyMatrixGraph*>(graphM.get())) {
        graphM_child->printMatrix();
        graphM_child->addVertex(100);
        graphM_child->removeVertex(1);
        graphM_child->updateVertex(5, 2);
        graphM_child->addEdge(2, 6, 32);
        graphM_child->addEdge(100, 3, 1);
        cout << endl << "Added vertex 100, removed vertex 1, updated vertex 5 to 2, added edge 2-7 with weight 32, added edge 100-3 with weight 1" << endl;
        graphM_child->printMatrix();
    }
    else cout << "Error: dynamic cast failed" << endl;

    cout << "\n\n\n";

    graph->print();

    cout << "SP_Vertex ID: " << graph->getSPVertexId() << endl;

    vector<Vertex*> neighbours = graph->getNeighbours(1);

    cout << "Neighbours of vertex 1: ";
    for (Vertex* v : neighbours) {
		cout << v->id << " ";
	}
    cout << endl;

    graph->updateVertex(1, 100);

    graph->removeVertex(100);

    graph->addEdge(2, 4, 10);

    graph->print();


    return 0;
}
