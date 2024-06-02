#include "GraphGenerator.h"
#include <random>
#include <algorithm>

Graph GraphGenerator::generateHamiltonianGraph(int nodes, double saturation) {
    Graph graph(nodes);
    // Generate Hamiltonian cycle
    std::vector<int> hamiltonianCycle(nodes);
    std::iota(hamiltonianCycle.begin(), hamiltonianCycle.end(), 0);
    std::shuffle(hamiltonianCycle.begin(), hamiltonianCycle.end(), std::mt19937{std::random_device{}()});

    for (int i = 0; i < nodes; ++i) {
        int u = hamiltonianCycle[i];
        int v = hamiltonianCycle[(i + 1) % nodes];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Add more edges based on saturation
    int edgesToAdd = (saturation * nodes * (nodes - 1) / 200) - nodes;
    std::mt19937 gen{std::random_device{}()};
    while (edgesToAdd > 0) {
        int u = gen() % nodes;
        int v = gen() % nodes;
        if (u != v && std::find(graph[u].begin(), graph[u].end(), v) == graph[u].end()) {
            graph[u].push_back(v);
            graph[v].push_back(u);
            --edgesToAdd;
        }
    }

    ensureEvenDegree(graph);
    return graph;
}

Graph GraphGenerator::generateNonHamiltonianGraph(int nodes) {
    Graph graph = generateHamiltonianGraph(nodes, 50);
    // Isolate one node
    graph[0].clear();
    for (int i = 1; i < nodes; ++i) {
        graph[i].erase(std::remove(graph[i].begin(), graph[i].end(), 0), graph[i].end());
    }
    return graph;
}

void GraphGenerator::ensureEvenDegree(Graph &graph) {
    for (auto& neighbors : graph) {
        if (neighbors.size() % 2 != 0) {
            // Find a node to connect to
            for (int i = 0; i < graph.size(); ++i) {
                if (std::find(neighbors.begin(), neighbors.end(), i) == neighbors.end()) {
                    neighbors.push_back(i);
                    graph[i].push_back(&neighbors - &graph[0]);
                    break;
                }
            }
        }
    }
}
