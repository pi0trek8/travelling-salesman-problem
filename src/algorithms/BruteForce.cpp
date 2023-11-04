#include "BruteForce.h"

BruteForce::BruteForce(Graph *graph) : graph(graph) {
    this->city_number = graph->get_city_number();
}

AlgorithmResultTO *BruteForce::process() {
    for (int i = 1; i < city_number; ++i) {
        permutation.push_back(i);
    }
    minimal_cost = calculate_total_path_cost();
    create_permutations(city_number - 1);

    vector<int> path_to_return(city_number + 1, 0);
    for (int i = 1; i < city_number - 1; ++i) {
        path_to_return[i] = best_path[i];
    }
    path_to_return[0] = 0;

    return new AlgorithmResultTO(minimal_cost, path_to_return);
}

void BruteForce::create_permutations(int last_city) {
    if (last_city == 1) {
        auto cost = calculate_total_path_cost();
        if (minimal_cost > cost) {
            minimal_cost = cost;
            best_path = permutation;
        }
        return;
    }
    for (int i = 0; i <= last_city; ++i) {
        create_permutations(last_city - 1);
        if(last_city % 2 == 0) {
            permutation.swap(i, last_city - 1);
        } else {
            permutation.swap(0, last_city - 1);
        }
    }
}

int BruteForce::calculate_total_path_cost() {
    int cost = 0;
    for (int i = 0; i < city_number - 2; ++i) {
        cost += graph->get_edge_cost_if_exists(permutation[i], permutation[i + 1]);
    }
    cost += graph->get_edge_cost_if_exists(0, permutation[0]);
    cost += graph->get_edge_cost_if_exists(permutation[city_number - 2], 0);
    return cost;
}

BruteForce::~BruteForce() = default;
