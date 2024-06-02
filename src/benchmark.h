#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "GraphOperations.h"
#include <chrono>

class Benchmark {
public:
    static void runBenchmarks();
private:
    static void benchmarkHamiltonianCycle();
    static void benchmarkEulerianCycle();
};

#endif
