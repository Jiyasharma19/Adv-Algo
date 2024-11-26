#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Function to implement the Bellman-Ford algorithm
void bellmanFordAlgorithm(int vertices, const vector<Edge> &edges, int start) {
    vector<int> distance(vertices, INT_MAX);
    distance[start] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= vertices - 1; ++i) {
        for (const auto &edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (const auto &edge : edges) {
        int u = edge.source;
        int v = edge.destination;
        int weight = edge.weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative-weight cycle\n";
            return;
        }
    }

    // Print the shortest distances from the source
    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < vertices; ++i) {
        if (distance[i] == INT_MAX) {
            cout << i << "\t\tINF\n";
        } else {
            cout << i << "\t\t" << distance[i] << "\n";
        }
    }
}

int main() {
    int vertices = 5;
    vector<Edge> edges = {
        {0, 1, 1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, 3}
    };

    int startVertex = 0;
    bellmanFordAlgorithm(vertices, edges, startVertex);

    return 0;
}
