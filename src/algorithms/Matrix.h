//
// Created by Zosia on 14.10.2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_MATRIX_H
#define TRAVELLING_SALESMAN_PROBLEM_MATRIX_H

#include <vector>

using namespace std;

class Matrix {
private:
    vector<vector<int>> matrix;

    int find_minimum_cost(vector<int> &cities);


    int reduce_columns_if_possible(int to, int matrixSize, int total_cost);

    int reduce_rows_if_possible(int to, int matrixSize, int total_cost);

    int reduce_columns_if_possible(int matrixSize, int total_cost);

    int reduce_rows_if_possible(int matrixSize, int total_cost);

public:

    int reduce_matrix(int from, int to, int parent_cost);

    int perform_first_reduction();
};


#endif //TRAVELLING_SALESMAN_PROBLEM_MATRIX_H
