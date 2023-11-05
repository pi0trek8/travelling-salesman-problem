#ifndef TRAVELLING_SALESMAN_PROBLEM_DYNAMICPROGRAMMING_H
#define TRAVELLING_SALESMAN_PROBLEM_DYNAMICPROGRAMMING_H


#include "Algorithm.h"

class DynamicProgramming : public Algorithm {
private:
    int ALL_VISITED_CITIES_MASK;
    Graph *graph;
    int city_number;
    int **cache;
    int **last_cities;

    void allocate_memory();

    int execute(int city, int mask);
public:
    explicit DynamicProgramming(Graph *graph);

    AlgorithmResultTO *process() override;

    ~DynamicProgramming() override;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_DYNAMICPROGRAMMING_H
