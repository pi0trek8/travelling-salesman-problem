#ifndef TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H
#define TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H


#include "Algorithm.h"

class BruteForce : public Algorithm {
private:
    Graph *graph;
    int city_number;
    int minimal_cost;
    Array<int> permutation;
    Array<int> best_path;

    void create_permutations(int last_city);

    int calculate_total_path_cost();

public:
    explicit BruteForce(Graph *graph);

    ~BruteForce() override;

    AlgorithmResultTO *process() override;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H
