#ifndef TRAVELLING_SALESMAN_PROBLEM_MATRIX_H
#define TRAVELLING_SALESMAN_PROBLEM_MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

class Matrix {
private:
    int city;

    int cost;

    int tree_level;

    int visited_cities_mask = (1 << 0);

    vector<bool> visited_cities;

    vector<vector<int>> matrix;

    int find_minimum_cost(vector<int> &cities);

    int reduce_columns_if_possible(int matrix_size);

    int reduce_rows_if_possible(int matrix_size);

public:

    Matrix();

    vector<int> parents;

    bool has_city_been_visited(int to_city) {
        return this->matrix[city][to_city] == -1;
    }

    int getCost() const;

    const vector<vector<int>> &get_matrix() const;

    bool is_single_candidate();

    Matrix(int city, const vector<vector<int>> &matrix, vector<int> parents, int tree_level);

    void print() const;

    void reduce_matrix(int from, int to, int parent_cost);

    int get_city() const;

    void perform_first_reduction();

    const vector<bool> &get_visited_cities() const;

    Matrix *get_parent();

    int get_tree_level() const;
};

#endif //TRAVELLING_SALESMAN_PROBLEM_MATRIX_H