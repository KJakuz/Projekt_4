#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <vector>

using Graph = std::vector<std::vector<int>>;

class GraphGenerator {
public:
    static Graph generateHamiltonianGraph(int nodes, double saturation);
    static Graph generateNonHamiltonianGraph(int nodes);
private:
    static void ensureEvenDegree(Graph &graph);
};

#endif
