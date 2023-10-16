//
// Created by Zosia on 11.10.2023.
//

#include "Graph.h"

Graph::Graph() {
    this->city_number = 0;
    this->graph = new Array<int>[0];
}

Graph::Graph(int city_number) {
    this->city_number = city_number;
    this->graph = new Array<int>[city_number];

    // TODO: not so elegant
    for (int i = 0; i < city_number; ++i) {
        for (int j = 0; j < city_number; ++j) {
            graph[i].push_back(0);
        }
    }
}

void Graph::add_new_connection(int source_city, int destination_city, int cost) {
    // TODO: maybe change push back to index access
    if (source_city >= city_number || destination_city >= city_number) {
        return;
    }
    this->graph[source_city][destination_city] = cost;
}

Array<int> Graph::get_adjacent_cities(int city) {
    return graph[city];
}

//void Graph::print() {
//    std::cout << "digraph G {" << std::endl;
//
//    for (int i = 0; i < city_number; i++) {
//        auto current = graph[i];
//        for (auto edge: current) {
//            std::cout << "  "
//                      << i
//                      << " -> "
//                      << edge.destination_city
//                      << " [label=\""
//                      << edge.cost
//                      << "\"];"
//                      << std::endl;
//        }
//    }
//    std::cout << "}" << std::endl;
//}

int Graph::get_city_number() const {
    return city_number;
}

bool Graph::find_adjacent_city(int from_city, int to_city) {
    auto adjacent_cities = graph[from_city];
    return adjacent_cities[to_city] != -1;
}

int Graph::get_edge_cost_if_exists(int from_city, int to_city) {
    auto adjacent_cities = graph[from_city];

    if(adjacent_cities[to_city] == -1) {
        return INT_MAX;
    }
    return adjacent_cities[to_city];
}


