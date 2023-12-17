include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <new>
using namespace std;
using namespace boost;

// Define a graph type
typedef adjacency_list<vecS, vecS, directedS> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

int main() {
    // Open the file
    ifstream infile("./bilayer_prot/bilayer_prot.gro");
    if (!infile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Initialize variables
    string line;
    vector<pair<string, vector<int>>> leaflets;
    vector<int> current_leaflet;

    // Read the file line by line
    while (getline(infile, line)) {
        istringstream iss(line);
        string token;

        // Check if the line contains leaflet information
        if (line[0] == '[') {
            if (!current_leaflet.empty()) {
                leaflets.push_back(make_pair(token, current_leaflet));
                current_leaflet.clear();
            }
            token = line.substr(1, line.size() - 2);
        } else {
            // Read atom indices from the line
            int index;
            while (iss >> index) {
                current_leaflet.push_back(index);
            }
        }
    }

    // Add the last leaflet
    if (!current_leaflet.empty()) {
        leaflets.push_back(make_pair(token, current_leaflet));
    }

    // Create a graph
    Graph g;

    // Add vertices for each atom
    vector<Vertex> atoms;
    for (auto& leaflet : leaflets) {
        for (int atom : leaflet.second) {
            Vertex v = add_vertex(g);
            atoms.push_back(v);
        }
    }

    // Connect atoms within each leaflet
    for (auto& leaflet : leaflets) {
        for (size_t i = 1; i < leaflet.second.size(); ++i) {
            add_edge(atoms[i - 1], atoms[i], g);
        }
    }

    // Print the graph
    cout << "Graph representation:" << endl;
    graph_traits<Graph>::vertex_iterator vi, vend;
    for (tie(vi, vend) = vertices(g); vi != vend; ++vi) {
        cout << "Atom " << *vi << " is connected to: ";
        graph_traits<Graph>::adjacency_iterator ai, aend;
        for (tie(ai, aend) = adjacent_vertices(*vi, g); ai != aend; ++ai) {
            cout << *ai << " ";
        }
        cout << endl;
    }

    return 0;
}