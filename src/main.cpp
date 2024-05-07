#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "utilities.hpp"

// Pomiar czasu
#include <ctime>
#include <chrono>

#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    // std::cout<< "Tu wykonujemy testy efektywności algorytmów"<<std::endl;

    ifstream file("C:\\Users\\tompi\\source\\repos\\PiAAGrafy\\sp_data\\graph\\graphV200D1.txt");

    if (!file.is_open()) {
		std::cerr << "Error: file not opened" << std::endl;
        cout << "Error: file not opened" << endl;
		return 1;
	}

    string path = "C:\\Users\\tompi\\source\\repos\\PiAAGrafy\\sp_data\\sp_result\\";
    string file_name = "spV200D1.txt";
    vector<SP_Node*> results = readSPResults(path + file_name);


    std::unique_ptr<Graph> graph = AdjacencyListGraph::createGraph(file);
    file.clear();
    file.seekg(0, ios::beg);
    std::unique_ptr<Graph> graphM = AdjacencyMatrixGraph::createGraph(file);

    std::chrono::steady_clock::time_point start, end;
    start = std::chrono::high_resolution_clock::now();
    std::vector<SP_Node*> paths = graph->spDijkstra(graph->getSPVertexId());
    end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "AdjacencyListGraph time: " << time << " microseconds" << endl;

    start = std::chrono::high_resolution_clock::now();
    std::vector<SP_Node*> pathsM = graphM->spDijkstra(graphM->getSPVertexId());
    end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "AdjacencyMatrixGraph time: " << time << " microseconds" << endl;

    if (checkDijkstra(paths, results)) cout << "AdjacencyListGraph results are the same!" << endl;
	else cout << "AdjacencyListGraph results are different!" << endl;

    if (checkDijkstra(pathsM, results)) cout << "Dijkstra results are the same!" << endl;
    else cout << "Dijkstra results are different!" << endl;


    return 0;
}
