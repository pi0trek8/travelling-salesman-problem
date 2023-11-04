#include "AlgorithmResultTO.h"

int AlgorithmResultTO::getPathCost() const {
    return path_cost;
}

const vector<int> &AlgorithmResultTO::getPath() const {
    return path;
}

AlgorithmResultTO::AlgorithmResultTO(int pathCost, const vector<int> &path) : path_cost(pathCost), path(path) {}
