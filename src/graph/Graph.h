#ifndef TRAVELLING_SALESMAN_PROBLEM_GRAPH_H
#define TRAVELLING_SALESMAN_PROBLEM_GRAPH_H


#include "../list/List.h"
#include "../array/Array.h"


class Graph {
private:
    int city_number = 0;
    Array<int> *graph = nullptr;

public:

    Graph();

    explicit Graph(int city_number);

    void add_new_connection(int from, int to, int cost);

    Array<int> &get_adjacent_cities(int city);

    bool find_adjacent_city(int from_city, int to_city);

    void print();

    int get_edge_cost_if_exists(int from_city, int to_city);

    int get_city_number() const;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_GRAPH_H
