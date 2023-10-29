#ifndef TRAVELLING_SALESMAN_PROBLEM_DYNAMICPROGRAMMING_H
#define TRAVELLING_SALESMAN_PROBLEM_DYNAMICPROGRAMMING_H


#include "Algorithm.h"

class DynamicProgramming : public Algorithm {
private:
    vector<vector<int>> cache;

    int execute(int city, int mask);

public:
    AlgorithmResultTO *process(Graph *graph) override;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_DYNAMICPROGRAMMING_H
