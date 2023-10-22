#ifndef TRAVELLING_SALESMAN_PROBLEM_ALGORITHMRESULTTO_H
#define TRAVELLING_SALESMAN_PROBLEM_ALGORITHMRESULTTO_H
#include <vector>

using namespace std;

class AlgorithmResultTO {
private:
    int path_cost;
    vector<int> path;
public:

    AlgorithmResultTO(int pathCost, const vector<int> &path);

    int getPathCost() const;

    void setPathCost(int pathCost);

    const vector<int> &getPath() const;

    void setPath(const vector<int> &path);

};


#endif //TRAVELLING_SALESMAN_PROBLEM_ALGORITHMRESULTTO_H
