//
// Created by Zosia on 14.10.2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_BNBNODE_H
#define TRAVELLING_SALESMAN_PROBLEM_BNBNODE_H

#include <vector>

using  namespace std;

class BnBNode {
    int city;
    int cityId;
    int lowerBound;
    bool visited;
    vector<int> adjacent_cities;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_BNBNODE_H
