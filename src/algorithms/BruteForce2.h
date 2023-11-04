//
// Created by Piotr Szczypior on 29/10/2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE2_H
#define TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE2_H


#include "Algorithm.h"

class BruteForce2 : public Algorithm {
private:
    Graph *graph;
    int city_number;
    int minimal_cost;
    Array<int> permutation;
    Array<int> best_path;

    void create_permutations(int last_city);

    int calculate_total_path_cost();

public:
    explicit BruteForce2(Graph *graph);

    ~BruteForce2() override;

    AlgorithmResultTO *process() override;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE2_H
