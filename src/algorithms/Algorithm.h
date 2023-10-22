#ifndef TRAVELLING_SALESMAN_PROBLEM_ALGORITHM_H
#define TRAVELLING_SALESMAN_PROBLEM_ALGORITHM_H


#include "../TO/AlgorithmResultTO.h"
#include "../graph/Graph.h"

class Algorithm {
public:
    virtual AlgorithmResultTO* process(Graph *graph) = 0;
};



#endif //TRAVELLING_SALESMAN_PROBLEM_ALGORITHM_H
