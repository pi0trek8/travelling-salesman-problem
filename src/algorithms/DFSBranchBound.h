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
};


#endif //TRAVELLING_SALESMAN_PROBLEM_DFSBRANCHBOUND_H
