#include <queue>
#include "FIFOBranchBound.h"
#include "Matrix.h"

AlgorithmResultTO *FIFOBranchBound::process(Graph *graph) {
    int city_number = graph->get_city_number();
    auto matrix = mapToVector(graph);

    List<Matrix *> queue;
    auto parent_node = new Matrix(nullptr, 0, vector<bool>(city_number, false), matrix);
    parent_node->perform_first_reduction();
    queue.push_back(parent_node);

    Matrix *lower_node = nullptr;

    int upper_bound = INT_MAX;
    bool is_completed;

    while (!queue.get_size()) {
        parent_node = queue[0];
        queue.pop_front();
        auto visited_cities = parent_node->get_visited_cities();
        visited_cities[parent_node->get_city()] = true;

        if (upper_bound < parent_node->getCost()) {
            delete parent_node;
            continue;
        }

        is_completed = true;
        for (int city = 0; city < city_number; ++city) {
            if (visited_cities[city]) {
                continue;
            }
            is_completed = false;
            auto new_node = new Matrix(parent_node, city, visited_cities, parent_node->get_matrix());
            new_node->reduce_matrix(parent_node->get_city(), city, parent_node->getCost());
            queue.push_front(new_node);
        }

        if (is_completed && upper_bound > parent_node->getCost()) {
            lower_node = parent_node;
            upper_bound = parent_node->getCost();
        }
    }

    vector<int> result_path(city_number + 1, 0);
    for (int i = city_number - 1; i > 0; --i) {
        if (lower_node != nullptr) {
            result_path[i] = lower_node->get_city();
            lower_node = lower_node->get_parent();
        }
    }

    return new AlgorithmResultTO(upper_bound, result_path);
}

vector<vector<int>> FIFOBranchBound::mapToVector(Graph *graph) {
    vector<vector<int>> matrix(graph->get_city_number(), vector<int>(graph->get_city_number()));
    for (int i = 0; i < graph->get_city_number(); ++i) {
        for (int j = 0; j < graph->get_city_number(); ++j) {
            matrix[i][j] = graph->get_adjacent_cities(i)[j];
        }
    }
    return matrix;
}
