//
// Created by Piotr Szczypior on 24/10/2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_RANDOMGENERATOR_H
#define TRAVELLING_SALESMAN_PROBLEM_RANDOMGENERATOR_H


#include "../graph/Graph.h"

class RandomGenerator {
public:
    Graph *generate_random(int city_number);
};


#endif //TRAVELLING_SALESMAN_PROBLEM_RANDOMGENERATOR_H
