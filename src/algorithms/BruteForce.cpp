#include <vector>
#include "BruteForce.h"

AlgorithmResultTO *BruteForce::process(Graph *graph) {
    vector<int> possible_path;

    for (int i = 0; i < graph->get_city_number(); i++) {
        possible_path.push_back(i);
    }

    create_permutations(graph, possible_path, 1, graph->get_city_number() - 1);
    auto algorithmResult = new AlgorithmResultTO(minimal_cost, best_path);

    return algorithmResult;
}

void BruteForce::create_permutations(Graph *graph, vector<int> permutation, int first_city, int last_city) {
    if (first_city == last_city) {

        // check if permutation is in the problem's graph
        for (int i = 0; i < permutation.size() - 1; ++i) {
            if (!graph->find_adjacent_city(permutation[i], permutation[i + 1])) {
                return;
            }
        }

        // find if there is a connection zwischen last city and first city
        if (!graph->find_adjacent_city(permutation[permutation.size() - 1], permutation[0])) {
            return;
        }
        permutation.push_back(0);

        auto permutation_cost = calculate_total_path_cost(graph, permutation);
        if(permutation_cost < minimal_cost) {
            minimal_cost = permutation_cost;
            best_path = permutation;
        }

        return;
    }

    for (int i = first_city; i < permutation.size(); ++i) {
        std::swap(permutation[first_city], permutation[i]);
        create_permutations(graph, permutation, first_city + 1, last_city);
        std::swap(permutation[first_city], permutation[i]);
    }
}

int BruteForce::calculate_total_path_cost(Graph *graph, vector<int> path) {
    int cost = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        cost += graph->get_edge_cost_if_exists(path[i], path[i + 1]);
    }
    return cost;
}

BruteForce::BruteForce() {
    this->minimal_cost = INT_MAX;
}