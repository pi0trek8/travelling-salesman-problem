#include "DynamicProgramming.h"

DynamicProgramming::DynamicProgramming(Graph *graph) : graph(graph) {
    this->city_number = graph->get_city_number();
    ALL_VISITED_CITIES_MASK = (1 << city_number) - 1;
    allocate_memory();
}

AlgorithmResultTO *DynamicProgramming::process() {
    vector<int> least_cost_hamiltonian_cycle;
    execute(0, (1 << 0));

    int city = 0;
    least_cost_hamiltonian_cycle.push_back(city);
    for (int m = 1 << 0; m < (1 << city_number) - 1; m = m | (1 << city)) {
        city = least_cost_paths[city][m];
        least_cost_hamiltonian_cycle.push_back(city);
    }
    least_cost_hamiltonian_cycle.push_back(0);

    return new AlgorithmResultTO(cache[0][1 << 0], least_cost_hamiltonian_cycle);
}

int DynamicProgramming::execute(int city, int mask) {
    int minimum_path_cost = INT_MAX;
    int last_visited_city = -1;

    if (mask == ALL_VISITED_CITIES_MASK) {
        return this->graph->get_edge_cost_if_exists(city, 0);
    }

    if (this->cache[city][mask] != -1) {
        return this->cache[city][mask];
    }

    for (int second_city = 0; second_city < city_number; ++second_city) {
        if ((mask & (1 << second_city)) != 0 || second_city == city) {
            continue;
        }
        int cost_to_second_city = graph->get_edge_cost_if_exists(city, second_city);
        int path_cost = cost_to_second_city + execute(second_city, (mask | (1 << second_city)));
        if (path_cost < minimum_path_cost) {
            minimum_path_cost = path_cost;
            last_visited_city = second_city;
        }
    }
    this->cache[city][mask] = minimum_path_cost;
    this->least_cost_paths[city][mask] = last_visited_city;

    return minimum_path_cost;
}

void DynamicProgramming::allocate_memory() {
    cache = new int *[city_number];
    least_cost_paths = new int *[city_number];
    for (int i = 0; i < city_number; ++i) {
        cache[i] = new int[1 << city_number];
        least_cost_paths[i] = new int[1 << city_number];
    }

    for (int i = 0; i < this->city_number; i++) {
        for (int j = 0; j < 1 << this->city_number; j++) {
            this->cache[i][j] = -1;
            this->least_cost_paths[i][j] = -1;
        }
    }
}

DynamicProgramming::~DynamicProgramming() {
    for (int i = 0; i < city_number; ++i) {
        delete[] cache[i];
        delete[] least_cost_paths[i];
    }
    delete[] cache;
    delete[] least_cost_paths;
}
