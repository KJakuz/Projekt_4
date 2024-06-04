#include "GraphGenerator.h"
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

Graph GraphGenerator::generateHamiltonianGraph(int nodes, double saturation) {
    Graph graph(nodes);
    // Generate Hamiltonian cycle
    vector<int> hamiltonianCycle(nodes);
    iota(hamiltonianCycle.begin(), hamiltonianCycle.end(), 0);
    shuffle(hamiltonianCycle.begin(), hamiltonianCycle.end(), mt19937{random_device{}()});

    for (int i = 0; i < nodes; ++i) {
        int u = hamiltonianCycle[i];
        int v = hamiltonianCycle[(i + 1) % nodes];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // Add more edges based on saturation
    int edgesToAdd = (saturation * nodes * (nodes - 1) / 200) - nodes;
    mt19937 gen{random_device{}()};
    while (edgesToAdd > 0) {
        int u = gen() % nodes;
        int v = gen() % nodes;
        if (u != v && find(graph[u].begin(), graph[u].end(), v) == graph[u].end()) {
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
        graph[i].erase(remove(graph[i].begin(), graph[i].end(), 0), graph[i].end());
    }
    return graph;
}

void GraphGenerator::ensureEvenDegree(Graph &graph) {
  for (int i = 0; i < graph.size(); ++i) {
    if (graph[i].size() % 2 != 0) {
      // Find any unconnected node (not limited to existing neighbors)
      for (int j = 0; j < graph.size(); ++j) {
        if (i != j && find(graph[i].begin(), graph[i].end(), j) == graph[i].end()) {
          graph[i].push_back(j);
          graph[j].push_back(i);
          break;
        }
      }
    }
  }
}
