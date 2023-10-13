#include "Edge.h"

Edge::Edge(int cost, int destinationCity) : cost(cost), destination_city(destinationCity) {
    this->cost = cost;
    this->destination_city = destinationCity;
}

Edge::Edge() = default;

Edge::~Edge() = default;