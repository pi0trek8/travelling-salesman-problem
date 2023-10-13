//
// Created by Zosia on 11.10.2023.
//

#include "Graph.h"

Graph::Graph() {
    this->city_number = 0;
    this->graph = new List<Edge>[0];
}

Graph::Graph(int city_number) {
    this->city_number = city_number;
    this->graph = new List<Edge>[city_number];
}

void Graph::add_new_connection(int source_city, int destination_city, int cost) {
    if (source_city >= city_number || destination_city >= city_number) {
        return;
    }
    Edge city(cost, destination_city);
    this->graph[source_city].push_back(city);
}

List<Edge> Graph::get_adjacent_cities(int city) {
    return graph[city];
}

void Graph::print() {
    std::cout << "digraph G {" << std::endl;

    for (int i = 0; i < city_number; i++) {
        auto current = graph[i];
        for (auto edge: current) {
            std::cout << "  "
                      << i
                      << " -> "
                      << edge.destination_city
                      << " [label=\""
                      << edge.cost
                      << "\"];"
                      << std::endl;
        }
    }
    std::cout << "}" << std::endl;
}

int Graph::get_city_number() const {
    return city_number;
}

bool Graph::find_adjacent_city(int city, int searched_city) {
    auto adjacent_cities = graph[city];
    for (int j = 0; j < adjacent_cities.get_size(); ++j) {
        if (adjacent_cities[j].destination_city == searched_city) {
            return true;
        }
    }
    return false;
}

int Graph::get_edge_cost_if_exists(int from_city, int to_city) {
    auto adjacent_cities = graph[from_city];
    for (int j = 0; j < adjacent_cities.get_size(); ++j) {
        if (adjacent_cities[j].destination_city == to_city) {
            return adjacent_cities[j].cost;
        }
    }
    return INT_MAX;
}


