#include "AlgorithmResultTO.h"

int AlgorithmResultTO::getPathCost() const {
    return path_cost;
}

void AlgorithmResultTO::setPathCost(int pathCost) {
    path_cost = pathCost;
}

const vector<int> &AlgorithmResultTO::getPath() const {
    return path;
}

void AlgorithmResultTO::setPath(const vector<int> &path) {
    AlgorithmResultTO::path = path;
}

AlgorithmResultTO::AlgorithmResultTO(int pathCost, const vector<int> &path) : path_cost(pathCost), path(path) {}
