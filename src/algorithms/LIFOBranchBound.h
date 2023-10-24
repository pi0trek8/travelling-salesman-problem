//
// Created by Piotr Szczypior on 23/10/2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_LIFOBRANCHBOUND_H
#define TRAVELLING_SALESMAN_PROBLEM_LIFOBRANCHBOUND_H


#include "Algorithm.h"

class LIFOBranchBound : public Algorithm {
private:
    vector<vector<int>> mapToVector(Graph *graph);

public:
    AlgorithmResultTO *process(Graph *graph) override;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_LIFOBRANCHBOUND_H
