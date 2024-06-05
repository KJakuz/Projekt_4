#include "GraphOperations.h"
#include <iostream>
#include <algorithm>

using namespace std;

void GraphOperations::printGraph(const Graph& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        cout << i << ": ";
        for (int neighbor : graph[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}


vector<int> GraphOperations::findHamiltonianCycle(const Graph& graph) {
    vector<int> path;
    vector<bool> visited(graph.size(), false);
    
function<bool(int, int)> dfs = [&](int v, int depth) {
    visited[v] = true;
    path.push_back(v);
    if (depth == graph.size()) {
        // Sprawdź, czy ostatni wierzchołek w cyklu jest sąsiadem początkowego wierzchołka
        for (int neighbor : graph[path.back()]) {
            if (neighbor == path[0]) {
                return true;
            }
        }
        return false;
    }
    for (int neighbor : graph[v]) {
        if (!visited[neighbor] && dfs(neighbor, depth + 1)) {
            return true;
        }
    }
    visited[v] = false;
    path.pop_back();
    return false;
    };

    for (int i = 0; i < graph.size(); ++i) {
        path.clear(); // Wyczyść ścieżkę przed każdym nowym przeszukiwaniem
        if (dfs(i, 1)) {
            path.push_back(i);
            return path;
        }
    }

    return path; // Zwróć pustą ścieżkę, jeśli nie znaleziono cyklu Hamiltona
}



void GraphOperations::dfsEuler(int v, Graph& graph, vector<int>& cycle) {
    while (!graph[v].empty()) {
        int neighbor = graph[v].back();
        graph[v].pop_back();
        for (int i = 0; i < graph[neighbor].size(); ++i) {
            if (graph[neighbor][i] == v) {
                graph[neighbor].erase(graph[neighbor].begin() + i);
                break;
            }
        }
        dfsEuler(neighbor, graph, cycle);
    }
    cycle.push_back(v);
}

bool GraphOperations::allVerticesEvenDegree(const Graph& graph) {
    unordered_map<int, int> degreeCount; // Mapa stopni wierzchołków
    for (const auto& edgeList : graph) {
        for (int vertex : edgeList) {
            degreeCount[vertex]++;
        }
    }
    
    for (const auto& pair : degreeCount) {
        if (pair.second % 2 != 0) {
            return false; // Zwróć false, jeśli stopień wierzchołka jest nieparzysty
        }
    }
    
    return true;
}

vector<int> GraphOperations::findEulerianCycle(const Graph& graph) {
    if (!allVerticesEvenDegree(graph)) {
        return {}; // Zwróć pusty cykl, jeśli graf nie ma wszystkich wierzchołków o parzystych stopniach
    }
    
    vector<int> cycle;
    Graph copy = graph; // Skopiuj graf, aby uniknąć zmiany oryginalnego grafu
    dfsEuler(0, copy, cycle); // Rozpocznij przeszukiwanie od wierzchołka 0
    reverse(cycle.begin(), cycle.end()); // Odwróć kolejność wierzchołków, aby uzyskać cykl Eulera
    return cycle;
}