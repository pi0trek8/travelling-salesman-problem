#include <climits>
#include <iomanip>
#include <utility>
#include "Matrix.h"

void Matrix::perform_first_reduction() {
    int total_cost = 0;
    int matrix_size = matrix.size();
    total_cost += reduce_rows_if_possible(matrix_size);
    total_cost += reduce_columns_if_possible(matrix_size);
    cost = total_cost;
}

void Matrix::reduce_matrix(int from, int to, int parent_cost) {
    int matrix_size = matrix.size();
    int total_cost = matrix[from][to];

    for (int i = 0; i < matrix_size; ++i) {
        matrix[from][i] = -1;
        matrix[i][to] = -1;
    }
    matrix[to][from] = -1;
    matrix[to][0] = -1;

    total_cost += reduce_rows_if_possible(matrix_size);
    total_cost += reduce_columns_if_possible(matrix_size);

    cost = total_cost + parent_cost;
}

int Matrix::find_minimum_cost(vector<int> &cities_costs) {
    int minimum_cost = INT_MAX;
    for (auto city_cost: cities_costs) {
        if (minimum_cost > city_cost && city_cost != -1) {
            minimum_cost = city_cost;
        }
    }
    return minimum_cost;
}

int Matrix::reduce_columns_if_possible(int matrix_size) {
    int reduction_cost = 0;
    for (int i = 0; i < matrix_size; ++i) {
        int minimum_cost_in_column = INT_MAX;
        for (int j = 0; j < matrix_size; ++j) {
            if (matrix[j][i] != -1) {
                if (std::min(minimum_cost_in_column, matrix[j][i]) != -1) {
                    minimum_cost_in_column = std::min(minimum_cost_in_column, matrix[j][i]);
                }
            }
        }
        if (minimum_cost_in_column != INT_MAX && minimum_cost_in_column > 0) {
            for (int j = 0; j < matrix_size; ++j) {
                if (matrix[j][i] != -1) {
                    matrix[j][i] -= minimum_cost_in_column;
                }
            }
            reduction_cost += minimum_cost_in_column;
        }
    }
    return reduction_cost;
}

int Matrix::reduce_rows_if_possible(int matrix_size) {
    int reduction_cost = 0;
    for (int i = 0; i < matrix_size; ++i) {
        int minimum_cost_in_row = find_minimum_cost(matrix[i]);

        if (minimum_cost_in_row != INT_MAX && minimum_cost_in_row != 0) {
            for (int j = 0; j < matrix_size; ++j) {
                if (matrix[i][j] != -1) {
                    matrix[i][j] -= minimum_cost_in_row;
                }
            }
            reduction_cost += minimum_cost_in_row;
        }
    }
    return reduction_cost;
}

void Matrix::print() const {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int Matrix::getCost() const {
    return cost;
}

const vector<vector<int>> &Matrix::get_matrix() const {
    return matrix;
}

int Matrix::get_city() const {
    return city;
}

const vector<bool> &Matrix::get_visited_cities() const {
    return visited_cities;
}

bool Matrix::is_single_candidate() {
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[city][i] != -1 && city != i) {
            return false;
        }
    }
    return true;
}

Matrix::Matrix() {}

Matrix::Matrix(int city, const vector<vector<int>> &matrix, vector<int> parents, int tree_level) {
    this->city = city;
    this->matrix = matrix;
    this->parents = parents;
    this->tree_level = tree_level;
}

int Matrix::get_tree_level() const {
    return tree_level;
}
