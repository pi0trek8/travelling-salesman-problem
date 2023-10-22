#ifndef TRAVELLING_SALESMAN_PROBLEM_MATRIX_H
#define TRAVELLING_SALESMAN_PROBLEM_MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

class Matrix {
private:
    Matrix *parent;

    int city;

    int cost;

    vector<bool> visited_cities;

    vector<vector<int>> matrix;

    int find_minimum_cost(vector<int> &cities);

    int reduce_columns_if_possible(int matrix_size);

    int reduce_rows_if_possible(int matrix_size);

public:
    int getCost() const;

    const vector<vector<int>> &get_matrix() const;

    Matrix(Matrix *parent, int city, const vector<bool> &visitedCities, const vector<vector<int>> &matrix);

    void print() const;

    void reduce_matrix(int from, int to, int parent_cost);

    int get_city() const;

    void perform_first_reduction();

    const vector<bool> &get_visited_cities() const;

    Matrix *get_parent();
};

#endif //TRAVELLING_SALESMAN_PROBLEM_MATRIX_H