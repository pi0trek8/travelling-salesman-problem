#include "DynamicProgramming.h"

AlgorithmResultTO *DynamicProgramming::process(Graph *graph) {
    int city_number = graph->get_city_number();
    int static ALL_CITIES_VISITED_MARKER ;
    ALL_CITIES_VISITED_MARKER = (1 << city_number) - 1;
    int visited_cities_tracker = 1;
    int minimum_hamiltonian_cycle_cost = INT_MAX;

    vector<vector<int>> parent(city_number, vector<int>(1 << city_number, -1));




    vector<int> hamiltonian_cycle(city_number + 1, 0);
//    for (int i = city_number - 1; i > 0; --i) {
//        hamiltonian_cycle[i] = last_city;
//        all_cities_visited_marker ^= (1 << last_city);
//        last_city = parent[i][all_cities_visited_marker];
//    }

    return new AlgorithmResultTO(minimum_hamiltonian_cycle_cost, hamiltonian_cycle);
}

int DynamicProgramming::execute(int city, int mask) {

//    if(mask == ALL_CITIES_VISITED_MARKER) {
//        return 0;
//    }
    return 0;
}





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