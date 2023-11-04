#ifndef TRAVELLING_SALESMAN_PROBLEM_ALGORITHMRESULTTO_H
#define TRAVELLING_SALESMAN_PROBLEM_ALGORITHMRESULTTO_H

#include <vector>
#include "../array/Array.h"

using namespace std;

class AlgorithmResultTO {
private:
    int path_cost;
    vector<int> path;
public:

    AlgorithmResultTO(int pathCost, const vector<int> &path);

    int getPathCost() const;

    const vector<int> &getPath() const;
};


#endif //TRAVELLING_SALESMAN_PROBLEM_ALGORITHMRESULTTO_H
