//
// Created by Piotr Szczypior on 29/10/2023.
//

#include "BruteForce2.h"

BruteForce2::BruteForce2(Graph *graph) : graph(graph) {
    minimal_cost = INT_MAX;
    this->city_number = graph->get_city_number();
}

AlgorithmResultTO *BruteForce2::process() {
    for (int i = 0; i < city_number; ++i) {
        permutation.push_back(i);
    }
    minimal_cost = calculate_total_path_cost();
    create_permutations(city_number - 1);

    vector<int> path_to_return(city_number + 1, 0);
    for (int i = 0; i < city_number; ++i) {
        path_to_return[i] = best_path[i];
    }

    return new AlgorithmResultTO(minimal_cost, path_to_return);
}

void BruteForce2::create_permutations(int last_city) {
    if (last_city == 0) {
        auto cost = calculate_total_path_cost();
        if (minimal_cost > cost) {
            minimal_cost = cost;
            best_path = permutation;
        }
        return;
    }

    for (int i = 1; i <= last_city; ++i) {
        permutation.swap(i, last_city);
        create_permutations(last_city - 1);
        permutation.swap(i, last_city);
    }
}

int BruteForce2::calculate_total_path_cost() {
    int cost = 0;
    for (int i = 0; i < city_number - 1; ++i) {
        cost += graph->get_edge_cost_if_exists(permutation[i], permutation[i + 1]);
    }
    cost += graph->get_edge_cost_if_exists(permutation[city_number - 1], 0);
    return cost;
}

BruteForce2::~BruteForce2() = default;
