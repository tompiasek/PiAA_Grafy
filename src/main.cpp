#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>

#include "graphs/adjacency_list_graph.hpp"

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
