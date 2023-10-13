#ifndef TRAVELLING_SALESMAN_PROBLEM_EDGE_H
#define TRAVELLING_SALESMAN_PROBLEM_EDGE_H


class Edge {

public:
    Edge(int cost, int destinationCity);

    Edge();

    virtual ~Edge();

    int destination_city;
    int cost;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_EDGE_H
