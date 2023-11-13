#ifndef TRAVELLING_SALESMAN_PROBLEM_DFSBRANCHBOUND_H
#define TRAVELLING_SALESMAN_PROBLEM_DFSBRANCHBOUND_H


#include "Algorithm.h"

class DFSBranchBound : public Algorithm {
private:
    Graph *graph;

public:
    explicit DFSBranchBound(Graph *graph);

    AlgorithmResultTO *process() override;

    ~DFSBranchBound() override;

    int nearestNeighborCost(const vector<vector<int>> &graph, vector<bool> &visited, int current);

    int findNearestNeighborCost(const vector<vector<int>> &graph);
};


#endif //TRAVELLING_SALESMAN_PROBLEM_DFSBRANCHBOUND_H
