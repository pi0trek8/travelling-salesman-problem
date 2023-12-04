#ifndef TRAVELLING_SALESMAN_PROBLEM_DFSBRANCHBOUND_H
#define TRAVELLING_SALESMAN_PROBLEM_DFSBRANCHBOUND_H


#include "Algorithm.h"

class DFSBranchBound : public Algorithm {
private:
    Graph *graph;

    pair<int, std::vector<int>> nearest_neighbor_cost(const vector<vector<int>> &graph, vector<bool> &visited, int current);

    pair<int, std::vector<int>> find_nearest_neighbor_result(const vector<vector<int>> &graph);
public:
    explicit DFSBranchBound(Graph *graph);

    AlgorithmResultTO *process() override;

    ~DFSBranchBound() override;

};


#endif //TRAVELLING_SALESMAN_PROBLEM_DFSBRANCHBOUND_H
