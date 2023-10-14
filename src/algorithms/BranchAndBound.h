//
// Created by Zosia on 14.10.2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUND_H
#define TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUND_H

#include <vector>
#include "../graph/Graph.h"

using namespace std;

class BranchAndBound {
private:
    Graph *graph;

    

public:
    explicit BranchAndBound(Graph *graph)  {
        this->graph = graph;
    }


    pair<vector<int>, int> process();

};


#endif //TRAVELLING_SALESMAN_PROBLEM_BRANCHANDBOUND_H
