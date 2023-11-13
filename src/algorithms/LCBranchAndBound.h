#ifndef TRAVELLING_SALESMAN_PROBLEM_LCBRANCHANDBOUND_H
#define TRAVELLING_SALESMAN_PROBLEM_LCBRANCHANDBOUND_H

#include <vector>
#include "../graph/Graph.h"
#include "Algorithm.h"
#include "Matrix.h"

using namespace std;

class LCBranchAndBound : public Algorithm {
private:
    Graph *graph;

    struct CompareMatrices {
        bool operator()(const Matrix first_matrix, const Matrix second_matrix) {
            return first_matrix.getCost() >= second_matrix.getCost();
        }
    };

public:
    explicit LCBranchAndBound(Graph *graph);

    AlgorithmResultTO *process() override;

    ~LCBranchAndBound() override;

    int nearestNeighborCost(const vector<vector<int>> &graph, vector<bool> &visited, int current);

    int findNearestNeighborCost(const vector<vector<int>> &graph);
};


#endif //TRAVELLING_SALESMAN_PROBLEM_LCBRANCHANDBOUND_H
