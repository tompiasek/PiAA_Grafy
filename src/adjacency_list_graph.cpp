#include "graphs/adjacency_list_graph.hpp"

#include <sstream>

//AdjacencyListGraph::AdjacencyListGraph() : Graph() {};

AdjacencyListGraph::AdjacencyListGraph(int no_vertices, int no_edges) : Graph(no_vertices, no_edges) {};

AdjacencyListGraph::AdjacencyListGraph(int no_vertices, int no_edges, std::vector<Vertex*> vertices, std::vector<std::list<Edge*>> adjacencyList) : Graph(no_vertices, no_edges), vertices(vertices), adjacencyList(adjacencyList) {};

AdjacencyListGraph::AdjacencyListGraph(int no_vertices, int no_edges, std::vector<Vertex*> vertices, std::vector<std::list<Edge*>> adjacencyList, Vertex* v_sp) : Graph(no_vertices, no_edges, v_sp), vertices(vertices), adjacencyList(adjacencyList) {};

std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    // Read number of vertices and edges (1st line)
    int no_vertices = 0, no_edges = 0;
    is >> no_vertices >> no_edges;

    std::string line;
    int v1_val = 0, v2_val = 0, w = 0, v_id = 0, v_sp_val = NULL;
    std::vector<Vertex*> vertices;
    std::vector<std::list<Edge*>> adjacencyList(no_vertices);
    bool found_v1 = false, found_v2 = false;
    Vertex* v1;
    Vertex* v2;
    Vertex* v_sp = nullptr;

    // Read edges
    for(int i = 0; i < no_edges; i++) {
        is >> v1_val >> v2_val >> w;
        
        // Check if vertices with given id already exist (quicker than 2x findVertex)
		for (int i = 0; i < vertices.size(); i++) {
            Vertex* v = vertices[i];
			if (v->id == v1_val) {
				v1 = v;
				found_v1 = true;
                v_id = i;
			}
			if (v->id == v2_val) {
				v2 = v;
				found_v2 = true;
			}
		}

        // If not, create new vertices
        if(!found_v1) {
            v1 = new Vertex(v1_val);
            vertices.push_back(v1);
            v_id = vertices.size() - 1;
        }
        found_v1 = false;

        if (!found_v2) {
			v2 = new Vertex(v2_val);
			vertices.push_back(v2);
		}
	    found_v2 = false;

        // Add edge to adjacency list
        adjacencyList[v_id].push_back(new Edge(v1, v2, w));
    }
    // Check if starting vertex for SP is provided, if so, save its ID
    if (is >> v_sp_val) {
        v_sp = new Vertex(v_sp_val);
    }

    std::cout << "Graph created with " << no_vertices << " vertices and " << no_edges << " edges.\n";

    return std::make_unique<AdjacencyListGraph>(no_vertices, no_edges, vertices, adjacencyList, v_sp);
}

int AdjacencyListGraph::addVertex(int id) {
    // Check if vertex with given id already exists
    int v_pos = findVertexPos(id);

    // If so, return its index
    if (v_pos != -1) {
	    std::cerr << "Vertex with id " << id << " already exists! [addVertex]" << std::endl;
        return v_pos;
    }

    // If not, create new vertex and add it to the list
    vertices.push_back(new Vertex(id));
    return vertices.size() - 1;
}

void AdjacencyListGraph::updateVertex(int id, int v) {
    int v_pos = findVertexPos(id);

    // If vertex with given id does not exist, return
    if (v_pos == -1) {
	    std::cerr << "Vertex with id " << id << " not found! [updateVertex]" << std::endl;
		return;
	}
    if (findVertexPos(v) != -1) {
		std::cerr << "Vertex with id " << v << " already exists! [updateVertex]" << std::endl;
		return;
	}

    // Update vertex value
    vertices[v_pos]->id = v;
}

void AdjacencyListGraph::removeVertex(int id) {
    int v_id = findVertexPos(id);

    // If vertex with given id does not exist, return
    if (v_id == -1) {
	    std::cerr << "Vertex with id " << id << " not found! [removeVertex]" << std::endl;
        return;
    }

    // Remove vertex from vector
    vertices.erase(vertices.begin() + v_id);

    // Remove all edges connected to this vertex
    for (auto& e : adjacencyList) {
        for (auto it = e.begin(); it != e.end(); ) {
            if ((*it)->start->id == id || (*it)->end->id == id) {
				delete *it;
				it = e.erase(it);

                // Update no_edges
                no_edges--;
            }
            else {
				++it;
			}
		}
	}

    adjacencyList.erase(adjacencyList.begin() + v_id);

    // Update no_vertices
	no_vertices--;
}

void AdjacencyListGraph::addEdge(int idStart, int idEnd, int w) {
    if (findEdge(idStart, idEnd) != nullptr) {
		std::cerr << "Edge already exists!" << std::endl;
		return;
	}
    for (Vertex* v : vertices) {
        if(v->id == idStart) {
            for (Vertex* u : vertices) {
                if (u->id == idEnd) {
					adjacencyList[findVertexPos(v->id)].push_back(new Edge(v, u, w));
					no_edges++;
					return;
				}
			}
		
        }
    }
    std::cerr << "Vertices not found! [addEdge]" << std::endl;
}

void AdjacencyListGraph::updateEdge(int idStart, int idEnd, int w) {
    Edge* e = findEdge(idStart, idEnd);
    if(e != nullptr) {
        e->weight = w;
        return;
    } else 
        std::cerr << "Edge (" << idStart << ", " << idEnd << ") not found![updateEdge]" << std::endl;
}

void AdjacencyListGraph::removeEdge(int idStart, int idEnd) {
    int edge_pos = findEdgePos(idStart, idEnd);
    if (edge_pos != -1) {
		int v_pos = findVertexPos(idStart);
		adjacencyList[v_pos].erase(std::next(adjacencyList[v_pos].begin(), edge_pos));
		no_edges--;
	} else 
		std::cerr << "Edge (" << idStart << ", " << idEnd << ") not found![removeEdge]" << std::endl;
}

std::vector<Vertex*> AdjacencyListGraph::getNeighbours(int id) {
    int v_pos = findVertexPos(id);
    Vertex* v_found;
    std::vector<Vertex*> neighbours;
    if (v_pos != -1) {
        for (Edge* e : adjacencyList[v_pos]) {
            neighbours.push_back(e->end);
		}
    } else 
        std::cerr << "Vertex with id " << id << " not found! [getNeighbours]" << std::endl;

	return neighbours;
}

bool AdjacencyListGraph::checkNeighbour(int id, int n) {
    int v_pos = findVertexPos(id);
    if (v_pos != -1) {
        for (Edge* e : adjacencyList[v_pos]) {
            if (e->end->id == n) {
                return true;
            }
        }
    } else 
		std::cerr << "Vertex with id " << id << " not found! [checkNeighbour]" << std::endl;

    return false;
}

Vertex* AdjacencyListGraph::findVertex(int id) {
    for (Vertex* v : vertices) {
        if (v->id == id) {
			return v;
		}
	}
	return nullptr;
}

int AdjacencyListGraph::findVertexPos(int v_id) {
    Vertex* v;
    for (int i = 0; i < vertices.size(); i++) {
        v = vertices[i];
		if (v->id == v_id) {
			return i;
		}
    }
    return -1;
}

Edge* AdjacencyListGraph::findEdge(int idStart, int idEnd) {
    for (Vertex* v : vertices) {
        if (v->id == idStart) {
            for (Edge* e : adjacencyList[findVertexPos(v->id)]) {
                if (e->end->id == idEnd) {
					return e;
				}
			}
		}
	}
	return nullptr;
}

int AdjacencyListGraph::findEdgePos(int idStart, int idEnd) {
    for (Vertex* v : vertices) {
        if (v->id == idStart) {
            int edgePos = 0;
            for (Edge* e : adjacencyList[findVertexPos(v->id)]) {
                if (e->end->id == idEnd) {
					return edgePos;
				}
                edgePos++;
			}
		}
	}
	return -1;
}

void AdjacencyListGraph::print() {
    std::cout << no_vertices << " " << no_edges << std::endl;
    for (std::list<Edge*> e : adjacencyList) {
        for (Edge* edge : e) {
			std::cout << edge->start->id << " " << edge->end->id << " " << edge->weight << std::endl;
		}
	}
    if (sp_vertex != nullptr) 
        std::cout << getSPVertexId() << std::endl;
}
