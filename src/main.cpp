#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "utilities.hpp"

#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    // std::cout<< "Tu wykonujemy testy efektywności algorytmów"<<std::endl;

    ifstream file("C:\\Users\\tompi\\source\\repos\\PiAAGrafy\\sp_data\\graph\\graphV100D0.5.txt");

    if (!file.is_open()) {
		std::cerr << "Error: file not opened" << std::endl;
        cout << "Error: file not opened" << endl;
		return 1;
	}

    string path = "C:\\Users\\tompi\\source\\repos\\PiAAGrafy\\sp_data\\sp_result\\";
    string file_name = "spV100D0.5.txt";
    vector<SP_Node*> results = readSPResults(path + file_name);


    std::unique_ptr<Graph> graph = AdjacencyListGraph::createGraph(file);
    file.clear();
    file.seekg(0, ios::beg);
    std::unique_ptr<Graph> graphM = AdjacencyMatrixGraph::createGraph(file);


    std::vector<SP_Node*> paths = graphM->spDijkstra(graphM->getSPVertexId());


    if (checkDijkstra(paths, results)) cout << "Dijkstra results are the same!" << endl;
    else cout << "Dijkstra results are different!" << endl;


    return 0;
}
