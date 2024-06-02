#include "GraphOperations.h"
#include <iostream>
#include <algorithm>

void GraphOperations::printGraph(const Graph& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        std::cout << i << ": ";
        for (int neighbor : graph[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}


std::vector<int> GraphOperations::findHamiltonianCycle(const Graph& graph) {
    std::vector<int> path;
    std::vector<bool> visited(graph.size(), false);
    
    std::function<bool(int, int)> dfs = [&](int v, int depth) {
        if (depth == graph.size()) {
            return std::find(graph[v].begin(), graph[v].end(), path[0]) != graph[v].end();
        }
        visited[v] = true;
        path.push_back(v);
        for (int neighbor : graph[v]) {
            if (!visited[neighbor] && dfs(neighbor, depth + 1)) {
                return true;
            }
        }
        visited[v] = false;
        path.pop_back();
        return false;
    };
    
    if (dfs(0, 1)) {
        path.push_back(path[0]);
    } else {
        path.clear();
    }
    return path;
}

std::vector<int> GraphOperations::findEulerianCycle(const Graph& graph) {
    // Implementation of Eulerian cycle finding algorithm
    // Ensure all vertices with non-zero degree are even
    std::vector<int> cycle;
    return cycle;
}
