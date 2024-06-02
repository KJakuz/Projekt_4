#include "Benchmark.h"
#include "GraphGenerator.h"
#include <iostream>

void Benchmark::runBenchmarks() {
    benchmarkHamiltonianCycle();
    benchmarkEulerianCycle();
}

void Benchmark::benchmarkHamiltonianCycle() {
    for (int n : {20, 30, 40, 50}) {
        auto graph = GraphGenerator::generateHamiltonianGraph(n, 30);
        auto start = std::chrono::high_resolution_clock::now();
        GraphOperations::findHamiltonianCycle(graph);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Hamiltonian cycle time for n = " << n << ": " << duration.count() << "s\n";
    }
}

void Benchmark::benchmarkEulerianCycle() {
    for (int n : {20, 30, 40, 50}) {
        auto graph = GraphGenerator::generateHamiltonianGraph(n, 30);
        auto start = std::chrono::high_resolution_clock::now();
        GraphOperations::findEulerianCycle(graph);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Eulerian cycle time for n = " << n << ": " << duration.count() << "s\n";
    }
}
