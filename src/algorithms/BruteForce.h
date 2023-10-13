//
// Created by Zosia on 12.10.2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H
#define TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H


#include "../list/List.h"
#include "../graph/Graph.h"
#include "../array/Array.h"

class BruteForce {
private:
    Array<Array<int>> possible_paths;
    void create_permutations(Graph* graph, Array<int> permutation, int first_city, int last_city);

public:
    void process(Graph* graph);

    int calculate_best_option(Graph *graph);

    static int calculate_total_path_cost(Graph *graph, Array<int> array);
};





#endif //TRAVELLING_SALESMAN_PROBLEM_BRUTEFORCE_H
