//
// Created by Piotr Szczypior on 23/10/2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_FIFOBRANCHBOUND_H
#define TRAVELLING_SALESMAN_PROBLEM_FIFOBRANCHBOUND_H


#include "Algorithm.h"

class FIFOBranchBound : public Algorithm {
private:
    vector<vector<int>> mapToVector(Graph *graph);

public:
    AlgorithmResultTO *process(Graph *graph) override;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_FIFOBRANCHBOUND_H
