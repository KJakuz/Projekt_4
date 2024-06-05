#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include "GraphGenerator.h"
#include "GraphOperations.h"

using namespace std;

void printUsage() {
    cout << "Usage:\n"
              << "./program --hamilton\n"
              << "./program --non-hamilton\n";
}

void printCycle(const vector<int>& cycle) {
    if (cycle.empty()) {
        cout << "No cycle found." << endl;
    } else {
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage();
        return 1;
    }

    string mode = argv[1];
    int nodes;
    double saturation;

    ofstream outputFile("benchmark_results.txt",ios::app);

    if (mode == "--hamilton") {
        cout << "nodes> ";
        cin >> nodes;
        cout << "saturation> ";
        cin >> saturation;

        auto start = chrono::steady_clock::now();
        auto graph = GraphGenerator::generateHamiltonianGraph(nodes, saturation);
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        outputFile <<mode<<";generation" <<";"<< duration.count() << "milliseconds" <<";"<<nodes<<endl;
        GraphOperations::printGraph(graph);

        start = chrono::steady_clock::now();
        auto hamiltonianCycle = GraphOperations::findHamiltonianCycle(graph);
        end = chrono::steady_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        outputFile <<mode<<";findinghamilton" <<";"<< duration.count() << "milliseconds" <<";"<<nodes<<endl;
        cout<<"Hamilton cycle: ";
        printCycle(hamiltonianCycle);

        start = chrono::steady_clock::now();
        auto eulerianCycle = GraphOperations::findEulerianCycle(graph);
        end = chrono::steady_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        outputFile <<mode<<";findingeuler" <<";"<< duration.count() << "milliseconds" <<";"<<nodes<<endl;
        cout<<"Euler cycle: ";
        printCycle(eulerianCycle);
    } else if (mode == "--non-hamilton") {
        cout << "nodes> ";
        cin >> nodes;

        auto start = chrono::steady_clock::now();
        auto graph = GraphGenerator::generateNonHamiltonianGraph(nodes);
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        outputFile <<mode<<";generation" <<";"<< duration.count() << "milliseconds" <<";"<<nodes<<endl;
        GraphOperations::printGraph(graph);

        start = chrono::steady_clock::now();
        auto hamiltonianCycle = GraphOperations::findHamiltonianCycle(graph);
        end = chrono::steady_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        outputFile <<mode<<";findingeuler" <<";"<< duration.count() << "milliseconds" << ";"<<nodes<<endl;
        cout<<"Hamilton cycle: ";
        printCycle(hamiltonianCycle);
    } else {
        printUsage();
        return 1;
    }

    return 0;
}
