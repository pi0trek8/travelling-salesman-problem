#include "DynamicProgramming.h"

DynamicProgramming::DynamicProgramming(Graph *graph) : graph(graph) {
    this->city_number = graph->get_city_number();
    ALL_CITIES_VISITED_MARKER = (1 << city_number) - 1;
    allocate_memory();
}

AlgorithmResultTO *DynamicProgramming::process() {


    int visited_cities_tracker = 1;
    int minimum_hamiltonian_cycle_cost = INT_MAX;

    vector<vector<int>> parent(city_number, vector<int>(1 << city_number, -1));


    vector<int> hamiltonian_cycle;
//    for (int i = city_number - 1; i > 0; --i) {
//        hamiltonian_cycle[i] = last_city;
//        all_cities_visited_marker ^= (1 << last_city);
//        last_city = parent[i][all_cities_visited_marker];
//    }
    execute(0, (1 << 0));

    int city = 0;

    // and calculate it's binary mask
    int mask = 1 << city;

    for(int i = 0; i < city_number; i++) {
        // add the city to the path vector
        hamiltonian_cycle.push_back(city);

        // select the next city
        city = last_cities[city][mask];

        // if the last city was already found - stop collecting cities
        if (city == -1)
            break;

        // set the mask to the next city
        mask = mask | (1 << city);
    }

    return new AlgorithmResultTO(0, hamiltonian_cycle);
}

int DynamicProgramming::execute(int city, int mask) {
    int minimum_path_cost = INT_MAX;
    int last_visited_city = -1;

    if (mask == ALL_CITIES_VISITED_MARKER) {
        return this->graph->get_edge_cost_if_exists(city, 0);
    }

    if (this->cache[city][mask] != -1) {
        return this->cache[city][mask];
    }

    for (int second_city = 0; second_city < city_number; ++second_city) {
        if ((mask & (1 << city)) == 1) {
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
    this->last_cities[city][mask] = last_visited_city;

    return minimum_path_cost;
}

void DynamicProgramming::allocate_memory() {
    cache = new int *[city_number];
    last_cities = new int *[city_number];
    for (int i = 0; i < city_number; ++i) {
        cache[i] = new int[1 << city_number];
        last_cities[i] = new int[1 << city_number];
    }

    for (int i = 0; i < this->city_number; i++) {
        for (int j = 0; j < 1 << this->city_number; j++) {
            this->cache[i][j] = -1;
            this->last_cities[i][j] = -1;
        }
    }
}

DynamicProgramming::~DynamicProgramming() {
    for (int i = 0; i < city_number; ++i) {
        delete[] cache[i];
        delete[] last_cities[i];
    }
    delete[] cache;
    delete[] last_cities;
};






//for (int i = 0; i < city_number; ++i) {
//d_cache[i][1 << i] = graph->get_edge_cost_if_exists(0, i);
//parent[i][1 << i] = 0;
//}
//
//for (int mask = 0; mask < all_cities_visited_marker; ++mask) {
//for (int from_city = 0; from_city < city_number; ++from_city) {
//if (!(mask & (1 << from_city))) {
//continue;
//}
//for (int to_city = 0; to_city < city_number; ++to_city) {
//if (!(mask & (1 << to_city))) {
//d_cache[mask | (1 << to_city)][to_city]
//= std::min(d_cache[mask][from_city] + graph->get_edge_cost_if_exists(from_city, to_city),
//d_cache[mask | (1 << to_city)][to_city]);
//}
//}
//}
//}
//for (int city = 1; city < city_number; ++city) {
//auto cost = d_cache[city][all_cities_visited_marker] + graph->get_edge_cost_if_exists(city, 0);
//if (cost < minimum_hamiltonian_cycle_cost) {
//minimum_hamiltonian_cycle_cost = cost;
//}
//}


//oid DynamicProgramming::collectPaths() {
//    // set city as firstCity
//    int city = 0;
//
//    // and calculate it's binary mask
//    int mask = 1 << city;
//
//    for(int i = 0; i < numberOfCities; i++) {
//        // add the city to the path vector
//        this->path.push_back(city);
//
//        // select the next city
//        city = lastCities[city][mask];
//
//        // if the last city was already found - stop collecting cities
//        if (city == -1)
//            break;
//
//        // set the mask to the next city
//        mask = calcNextMask(city, mask);
//    }
//}