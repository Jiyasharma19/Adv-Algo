#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge with source, destination, and weight
struct Edge {
    int source, destination, weight;
};

// Function to find the root of an element with path compression
int findRoot(vector<int> &parent, int node) {
    if (parent[node] != node) {
        parent[node] = findRoot(parent, parent[node]);
    }
    return parent[node];
}

// Function to perform union of two subsets based on rank
void performUnion(vector<int> &parent, vector<int> &rank, int root1, int root2) {
    if (rank[root1] < rank[root2]) {
        parent[root1] = root2;
    } else if (rank[root1] > rank[root2]) {
        parent[root2] = root1;
    } else {
        parent[root2] = root1;
        rank[root1]++;
    }
}

// Function to find the Minimum Spanning Tree using Kruskal's Algorithm
void findMST(int vertices, vector<Edge> &edges) {
    vector<int> parent(vertices);
    vector<int> rank(vertices, 0);
    vector<Edge> mstEdges;

    // Initialize disjoint sets for each vertex
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
    }

    // Sort all edges by weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // Iterate through edges and build the MST
    for (const auto &edge : edges) {
        int root1 = findRoot(parent, edge.source);
        int root2 = findRoot(parent, edge.destination);

        if (root1 != root2) {
            mstEdges.push_back(edge);
            performUnion(parent, rank, root1, root2);
            if (mstEdges.size() == vertices - 1) break;
        }
    }

    // Print the edges in the Minimum Spanning Tree
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : mstEdges) {
        cout << edge.source << " -- " << edge.destination << " == " << edge.weight << "\n";
    }
}

int main() {
    int vertices = 4;
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Find and print the Minimum Spanning Tree
    findMST(vertices, edges);

    return 0;
}
