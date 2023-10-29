#include <vector>
#include "BruteForce.h"

BruteForce::BruteForce() {
    this->minimal_cost = INT_MAX;
}

AlgorithmResultTO *BruteForce::process(Graph *graph) {
    vector<int> possible_path;

    possible_path.reserve(graph->get_city_number());
    for (int i = 0; i < graph->get_city_number(); i++) {
        possible_path.push_back(i);
    }

    create_permutations(graph, possible_path, 1, graph->get_city_number() - 1);
    return new AlgorithmResultTO(minimal_cost, best_path);
}

//http://algorytmika.wikidot.com/exponential-permut?fbclid=IwAR00oDEd6EZWTG5_8eIX6-ZDDGp5sd1oOl2mCQKEu8JxW26WW9ggN9WNbX0
void BruteForce::create_permutations(Graph *graph, vector<int> permutation, int first_city, int last_city) {
    if (first_city == last_city) {
        permutation.push_back(0);

        auto permutation_cost = calculate_total_path_cost(graph, permutation);
        if (permutation_cost < minimal_cost) {
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
