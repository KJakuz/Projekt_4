#include <iostream>
#include <cstdlib>
#include "GraphGenerator.h"
#include "GraphOperations.h"
#include <string>
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


void actions(string action, auto graph){
    if (action == "print"){
        GraphOperations::printGraph(graph);
    }
    else if (action == "hamilton"){
        auto hamiltonianCycle = GraphOperations::findHamiltonianCycle(graph);
        cout << "Hamiltonian Cycle: ";
        printCycle(hamiltonianCycle);
    }
    else if (action == "euler"){
        auto eulerianCycle = GraphOperations::findEulerianCycle(graph);
        cout << "Eulerian Cycle: ";
        printCycle(eulerianCycle);
    }
    else if (action == "exit"){
        exit(0);
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
    string action;

    if (mode == "--hamilton") {
        //cout << "nodes> ";
        cin >> nodes;
        //cout << "saturation> ";
        cin >> saturation;
        
        auto graph = GraphGenerator::generateHamiltonianGraph(nodes, saturation);
        // GraphOperations::printGraph(graph);
        // auto hamiltonianCycle = GraphOperations::findHamiltonianCycle(graph);
        // cout << "Hamiltonian Cycle: ";
        // printCycle(hamiltonianCycle);
        // auto eulerianCycle = GraphOperations::findEulerianCycle(graph);
        // cout << "Eulerian Cycle: ";
        // printCycle(eulerianCycle);
        // action = "print";
        // actions(action,graph);
        cin >> action;
        actions(action,graph);
        cin >> action;
        actions(action,graph);
    } else if (mode == "--non-hamilton") {
        //cout << "nodes> ";
        cin >> nodes;

        auto graph = GraphGenerator::generateNonHamiltonianGraph(nodes);
        // GraphOperations::printGraph(graph);
        // auto hamiltonianCycle = GraphOperations::findHamiltonianCycle(graph);
        //         cout << "Hamiltonian Cycle: ";
        // printCycle(hamiltonianCycle);
        // auto eulerianCycle = GraphOperations::findEulerianCycle(graph);
        // cout << "Eulerian Cycle: ";
        // printCycle(eulerianCycle);
        cin >> action;
        actions(action,graph);
        cin >> action;
        actions(action,graph);
    } else {
        printUsage();
        return 1;
    }

    return 0;
}
