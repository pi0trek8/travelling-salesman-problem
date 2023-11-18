#include "DynamicProgramming.h"

DynamicProgramming::DynamicProgramming(Graph *graph) : graph(graph) {
    this->city_number = graph->get_city_number();
    ALL_VISITED_CITIES_MASK = (1 << city_number) - 1;
    allocate_memory();
}

AlgorithmResultTO *DynamicProgramming::process() {
    // Vector to store the least cost Hamiltonian cycle
    vector<int> least_cost_hamiltonian_cycle;

    // Execute the Dynamic Programming algorithm starting from city 0
    execute(0, (1 << 0));

    // Reconstruct the least cost Hamiltonian cycle from the computed paths
    int city = 0;
    least_cost_hamiltonian_cycle.push_back(city);
    for (int m = 1 << 0; m < (1 << city_number) - 1; m = m | (1 << city)) {
        city = least_cost_paths[city][m];
        least_cost_hamiltonian_cycle.push_back(city);
    }
    least_cost_hamiltonian_cycle.push_back(0);

    // Create and return the result object
    return new AlgorithmResultTO(cache[0][1 << 0], least_cost_hamiltonian_cycle);
}

// Recursive function to execute the Dynamic Programming algorithm
int DynamicProgramming::execute(int city, int mask) {
    int minimum_path_cost = INT_MAX;
    int last_visited_city = -1;

    // Base case: if all cities are visited, return the cost to return to city 0
    if (mask == ALL_VISITED_CITIES_MASK) {
        return this->graph->get_edge_cost_if_exists(city, 0);
    }

    // Check if the result for the current city and mask is already cached
    if (this->cache[city][mask] != -1) {
        return this->cache[city][mask];
    }

    // Iterate through all possible next cities
    for (int second_city = 0; second_city < city_number; ++second_city) {
        // Skip if the second city is already visited or is the current city
        if ((mask & (1 << second_city)) != 0 || second_city == city) {
            continue;
        }

        // Compute the cost to the second city and the cost of the remaining path
        int cost_to_second_city = graph->get_edge_cost_if_exists(city, second_city);
        int path_cost = cost_to_second_city + execute(second_city, (mask | (1 << second_city)));

        // Update the minimum cost and the last visited city
        if (path_cost < minimum_path_cost) {
            minimum_path_cost = path_cost;
            last_visited_city = second_city;
        }
    }

    // Cache the result and the last visited city
    this->cache[city][mask] = minimum_path_cost;
    this->least_cost_paths[city][mask] = last_visited_city;

    return minimum_path_cost;
}

// Helper function to allocate memory for the cache and least_cost_paths arrays
void DynamicProgramming::allocate_memory() {
    cache = new int *[city_number];
    least_cost_paths = new int *[city_number];

    for (int i = 0; i < city_number; ++i) {
        cache[i] = new int[1 << city_number];
        least_cost_paths[i] = new int[1 << city_number];
    }

    // Initialize the arrays with -1
    for (int i = 0; i < this->city_number; i++) {
        for (int j = 0; j < 1 << this->city_number; j++) {
            this->cache[i][j] = -1;
            this->least_cost_paths[i][j] = -1;
        }
    }
}

DynamicProgramming::~DynamicProgramming() {
    // Deallocate memory for cache and least_cost_paths arrays
    for (int i = 0; i < city_number; ++i) {
        delete[] cache[i];
        delete[] least_cost_paths[i];
    }
    delete[] cache;
    delete[] least_cost_paths;
}
