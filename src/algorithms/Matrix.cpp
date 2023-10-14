#include <climits>
#include "Matrix.h"

int Matrix::find_minimum_cost(vector<int> & cities_costs) {
    int minimum_cost = INT_MAX;
    for (auto city_cost: cities_costs) {
        if (minimum_cost > city_cost) {
            minimum_cost = city_cost;
        }
    }
    return minimum_cost;
}

int Matrix::reduce_matrix(int from, int to, int parent_cost) {
    int matrixSize = matrix.size();
    int total_cost = matrix[from][to];;

    for (int i = 0; i < matrixSize; ++i) {
        matrix[from][i] = -1;
        matrix[i][to] = -1;
    }
    matrix[to][from] = -1;

    total_cost = reduce_rows_if_possible(to, matrixSize, total_cost);
    total_cost = reduce_columns_if_possible(to, matrixSize, total_cost);

    return total_cost;
}

int Matrix::reduce_rows_if_possible(int to, int matrixSize, int total_cost) {
    for (int i = 0; i < matrixSize; ++i) {
        // Skip if the row is already reduced
        if (matrix[i][to] == -1) continue;

        int minimum_cost_in_row = find_minimum_cost(matrix[i]);
        if (minimum_cost_in_row != INT_MAX) {
            for (int j = 0; j < matrixSize; ++j) {
                if (matrix[i][j] != -1) {
                    matrix[i][j] -= minimum_cost_in_row;
                }
            }
            total_cost += minimum_cost_in_row;
        }
    }
    return total_cost;
}

int Matrix::reduce_columns_if_possible(int to, int matrixSize, int total_cost) {
    for (int i = 0; i < matrixSize; ++i) {
        // Skip if the column is already reduced
        if (matrix[to][i] == -1) continue;

        int minimum_cost_in_column = INT_MAX;
        for (int j = 0; j < matrixSize; ++j) {
            if (matrix[j][i] != -1) {
                minimum_cost_in_column = std::min(minimum_cost_in_column, matrix[j][i]);
            }
        }
        if (minimum_cost_in_column != INT_MAX) {
            for (int j = 0; j < matrixSize; ++j) {
                if (matrix[j][i] != -1) {
                    matrix[j][i] -= minimum_cost_in_column;
                }
            }
            total_cost += minimum_cost_in_column;
        }
    }
    return total_cost;
}

int Matrix::perform_first_reduction() {
    int total_cost = 0;
    int matrix_size = matrix.size();
    total_cost = reduce_columns_if_possible(matrix_size, total_cost);
    total_cost = reduce_rows_if_possible(matrix_size, total_cost);
    return total_cost;
}

int Matrix::reduce_columns_if_possible(int matrixSize, int total_cost) {
    for (int i = 0; i < matrixSize; ++i) {
        int minimum_cost_in_column = INT_MAX;
        for (int j = 0; j < matrixSize; ++j) {
            if (matrix[j][i] != -1) {
                minimum_cost_in_column = std::min(minimum_cost_in_column, matrix[j][i]);
            }
        }
        if (minimum_cost_in_column != INT_MAX) {
            for (int j = 0; j < matrixSize; ++j) {
                if (matrix[j][i] != -1) {
                    matrix[j][i] -= minimum_cost_in_column;
                }
            }
            total_cost += minimum_cost_in_column;
        }
    }
    return total_cost;
}

int Matrix::reduce_rows_if_possible(int matrixSize, int total_cost) {
    for (int i = 0; i < matrixSize; ++i) {
        int minimum_cost_in_row = find_minimum_cost(matrix[i]);
        if (minimum_cost_in_row != INT_MAX) {
            for (int j = 0; j < matrixSize; ++j) {
                if (matrix[i][j] != -1) {
                    matrix[i][j] -= minimum_cost_in_row;
                }
            }
            total_cost += minimum_cost_in_row;
        }
    }
    return total_cost;
}
