#ifndef TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUND_H
#define TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUND_H

#include <vector>
#include "../graph/Graph.h"
#include "Algorithm.h"
#include "Matrix.h"

using namespace std;

class BranchAndBound : public Algorithm {
private:
    vector<vector<int>> mapToVector(Graph *graph);

public:
    AlgorithmResultTO *process(Graph *graph) override;


    struct CompareMatrices {
        bool operator()(const Matrix *first_matrix, const Matrix *second_matrix) {
            return first_matrix->getCost() >= second_matrix->getCost();
        }
    };
};


#endif //TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUND_H
