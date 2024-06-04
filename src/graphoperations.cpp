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
    vector<int> path; // Ścieżka cyklu Hamiltona
    vector<bool> visited(graph.size(), false); // Tablica odwiedzonych wierzchołków
    
    function<bool(int, int)> dfs = [&](int v, int depth) {
        // Sprawdzamy, czy odwiedziliśmy wszystkie wierzchołki
        if (depth == graph.size()) {
            // Jeśli tak, sprawdzamy, czy możemy wrócić do wierzchołka początkowego, tworząc cykl Hamiltona
            return find(graph[v].begin(), graph[v].end(), path[0]) != graph[v].end();
        }
        
        // Oznaczamy aktualny wierzchołek jako odwiedzony i dodajemy go do ścieżki
        visited[v] = true;
        path.push_back(v);
        
        // Przechodzimy przez sąsiadów aktualnego wierzchołka
        for (int neighbor : graph[v]) {
            // Jeśli sąsiad nie został odwiedzony, rekurencyjnie odwiedzamy go
            if (!visited[neighbor] && dfs(neighbor, depth + 1)) {
                return true; // Jeśli udało się znaleźć cykl Hamiltona, zwracamy prawdę
            }
        }
        
        // Jeśli nie udało się znaleźć cyklu Hamiltona, oznaczamy aktualny wierzchołek jako nieodwiedzony i usuwamy go ze ścieżki
        visited[v] = false;
        path.pop_back();
        
        return false; // Zwracamy fałsz, ponieważ cykl Hamiltona nie został znaleziony dla tego wierzchołka
    };
    
    // Rozpoczynamy przeszukiwanie DFS od pierwszego wierzchołka
    if (dfs(0, 1)) {
        path.push_back(path[0]); // Jeśli znaleziono cykl Hamiltona, dodajemy wierzchołek początkowy na koniec ścieżki, aby zamknąć cykl
    } else {
        path.clear(); // W przeciwnym razie, czyszczymy ścieżkę
    }
    
    return path; // Zwracamy ścieżkę (cykl Hamiltona) lub pustą listę, jeśli nie udało się znaleźć cyklu
}


vector<int> GraphOperations::findEulerianCycle(const Graph& graph) {
    // Funkcja pomocnicza DFS do znajdowania cyklu Eulera
    vector<int> cycle;
  Graph graphCopy = graph;
    function<void(int)> dfs = [&](int v) {
        while (!graphCopy[v].empty()) {
            int u = graphCopy[v].back(); // Weź ostatniego sąsiada wierzchołka v
            graphCopy[v].pop_back(); // Usuń krawędź v-u
            dfs(u); // Rekurencyjnie odwiedź wierzchołek u
        }
        cycle.push_back(v); // Dodaj wierzchołek do cyklu Eulera
    };


    // Znajdź wierzchołek startowy, który ma niezerowy stopień
    int startVertex = -1;
    for (int i = 0; i < graphCopy.size(); ++i) {
        if (!graphCopy[i].empty()) {
            startVertex = i;
            break;
        }
    }

    // Jeśli nie znaleziono wierzchołka o niezerowym stopniu, zwróć pusty cykl Eulera
    if (startVertex == -1) {
        return cycle;
    }

    // Rozpocznij przeszukiwanie DFS od wierzchołka startowego
    dfs(startVertex);

    // Odwróć cykl, aby uzyskać poprawną kolejność wierzchołków
    reverse(cycle.begin(), cycle.end());

    return cycle;
}
