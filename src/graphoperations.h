#ifndef GRAPHOPERATIONS_H
#define GRAPHOPERATIONS_H

#include <vector>

using Graph = std::vector<std::vector<int>>;

class GraphOperations {
public:
    static void printGraph(const Graph& graph);
    static std::vector<int> findHamiltonianCycle(const Graph& graph);
    static std::vector<int> findEulerianCycle(const Graph& graph);
};

#endif
