//
// Created by Zosia on 11.10.2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_GRAPH_H
#define TRAVELLING_SALESMAN_PROBLEM_GRAPH_H


#include "../list/List.h"
#include "edge/Edge.h"

class Graph {
private:
    int city_number = 0;
    List<Edge> *graph = nullptr;

public:

    Graph();

    explicit Graph(int city_number);

    void add_new_connection(int from, int to, int cost);

    List<Edge> get_adjacent_cities(int city);

    bool find_adjacent_city(int city, int searched_city);

    void print();

    int get_edge_cost_if_exists(int from_city, int to_city);

    int get_city_number() const;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_GRAPH_H
