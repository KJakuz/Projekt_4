#include <iostream>
#include <cstdlib>
#include "GraphGenerator.h"
#include "GraphOperations.h"
#include "Benchmark.h"

void printUsage() {
    std::cout << "Usage:\n"
              << "./program --hamilton\n"
              << "./program --non-hamilton\n";
}

void printCycle(const std::vector<int>& cycle) {
    if (cycle.empty()) {
        std::cout << "No cycle found." << std::endl;
    } else {
        for (int v : cycle) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
        return 1;
    }

    std::string mode = argv[1];
    int nodes;
    double saturation;

    if (mode == "--hamilton") {
        std::cout << "nodes> ";
        std::cin >> nodes;
        std::cout << "saturation> ";
        std::cin >> saturation;
        
        auto graph = GraphGenerator::generateHamiltonianGraph(nodes, saturation);
        GraphOperations::printGraph(graph);
        auto hamiltonianCycle = GraphOperations::findHamiltonianCycle(graph);
        std::cout << "Hamiltonian Cycle: ";
        printCycle(hamiltonianCycle);
        auto eulerianCycle = GraphOperations::findEulerianCycle(graph);
        std::cout << "Eulerian Cycle: ";
        printCycle(eulerianCycle);
    } else if (mode == "--non-hamilton") {
        std::cout << "nodes> ";
        std::cin >> nodes;

        auto graph = GraphGenerator::generateNonHamiltonianGraph(nodes);
        GraphOperations::printGraph(graph);
        auto hamiltonianCycle = GraphOperations::findHamiltonianCycle(graph);
                std::cout << "Hamiltonian Cycle: ";
        printCycle(hamiltonianCycle);
        auto eulerianCycle = GraphOperations::findEulerianCycle(graph);
        std::cout << "Eulerian Cycle: ";
        printCycle(eulerianCycle);
    } else {
        printUsage();
        return 1;
    }

    return 0;
}
