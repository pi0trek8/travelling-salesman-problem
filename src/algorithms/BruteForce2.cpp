#include "BruteForce.h"

BruteForce::BruteForce(Graph *graph) : graph(graph) {
    minimal_cost = INT_MAX;
    this->city_number = graph->get_city_number();
}

AlgorithmResultTO *BruteForce::process() {
    // Initialize the initial permutation
    for (int i = 0; i < city_number; ++i) {
        permutation.push_back(i);
    }

    // Calculate the cost of the initial permutation
    minimal_cost = calculate_total_path_cost();
    best_path = permutation;

    // Generate all permutations and update the minimal cost and best path
    create_permutations(city_number - 1);

    // Create a vector to store the final path
    vector<int> path_to_return(city_number + 1, 0);
    for (int i = 0; i < city_number; ++i) {
        path_to_return[i] = best_path[i];
    }

    // Return the result object
    return new AlgorithmResultTO(minimal_cost, path_to_return);
}

// Recursive function to generate all possible permutations and update the minimal cost and best path
void BruteForce::create_permutations(int last_city) {
    if (last_city == 0) {
        // Calculate the cost of the current permutation and update the minimal cost and best path if needed
        auto cost = calculate_total_path_cost();
        if (minimal_cost > cost) {
            minimal_cost = cost;
            best_path = permutation;
        }
        return;
    }

    // Swap elements in the permutation to generate different permutations
    for (int i = 1; i <= last_city; ++i) {
        permutation.swap(i, last_city);
        create_permutations(last_city - 1);
        permutation.swap(i, last_city);
    }
}

// Calculate the total cost of the current permutation
int BruteForce::calculate_total_path_cost() {
    int cost = 0;
    for (int i = 0; i < city_number - 1; ++i) {
        cost += graph->get_edge_cost_if_exists(permutation[i], permutation[i + 1]);
    }
    cost += graph->get_edge_cost_if_exists(permutation[city_number - 1], 0);
    return cost;
}

BruteForce::~BruteForce() = default;
