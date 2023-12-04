#ifndef TRAVELLING_SALESMAN_PROBLEM_ALGORITHM_H
#define TRAVELLING_SALESMAN_PROBLEM_ALGORITHM_H


#include <atomic>
#include "../TO/AlgorithmResultTO.h"
#include "../graph/Graph.h"

class Algorithm {
public:
    virtual AlgorithmResultTO* process() = 0;

    virtual ~Algorithm() = default;
};



#endif //TRAVELLING_SALESMAN_PROBLEM_ALGORITHM_H
