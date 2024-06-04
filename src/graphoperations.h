#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H

#include <vector>

class GraphOperations {
public:
    using Graph = std::vector<std::vector<int>>;

    static void printGraph(const Graph& graph);

    static std::vector<int> findHamiltonianCycle(const Graph& graph);

    static std::vector<int> findEulerianCycle(const Graph& graph);

private:
    static void dfsEuler(int v, Graph& graph, std::vector<int>& cycle);
};

#endif // GRAPH_OPERATIONS_H
