#ifndef TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H
#define TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H


#include "../list/List.h"
#include "../graph/Graph.h"
#include "../array/Array.h"
#include "../TO/AlgorithmResultTO.h"
#include "Algorithm.h"
#include <vector>

class BruteForce : public Algorithm {
private:
    int minimal_cost;
    vector<int> best_path;

    void create_permutations(Graph *graph, vector<int> permutation, int first_city, int last_city);

    static int calculate_total_path_cost(Graph *graph, vector<int> path);

public:

    BruteForce();

    AlgorithmResultTO *process(Graph *graph) override;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H
