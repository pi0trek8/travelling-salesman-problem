//
// Created by Zosia on 14.10.2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_BNBNODE_H
#define TRAVELLING_SALESMAN_PROBLEM_BNBNODE_H

#include <vector>
#include "Matrix.h"

using  namespace std;

class BnBNode {
private:
    int nodeId;
    int city;
    int lowerBound;
    int parentNodeId;
    bool visited;
    Matrix matrix;

public:
    explicit BnBNode(const Matrix &matrix) : matrix(matrix) {}

    const Matrix &getMatrix() const {
        return matrix;
    }



};


#endif //TRAVELLING_SALESMAN_PROBLEM_BNBNODE_H
