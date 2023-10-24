#include <queue>
#include "LIFOBranchBound.h"
#include "Matrix.h"

AlgorithmResultTO *LIFOBranchBound::process(Graph *graph) {
    int city_number = graph->get_city_number();
    auto matrix = mapToVector(graph);

    std::queue<Matrix *> queue;
    auto parent_node = new Matrix(nullptr, 0, vector<bool>(city_number, false), matrix);
    parent_node->perform_first_reduction();
    queue.push(parent_node);

    Matrix *lower_node = nullptr;

    int upper_bound = INT_MAX;
    bool is_completed = false;

    while (!queue.empty()) {
        parent_node = queue.front();
        queue.pop();
        auto visited_cities = parent_node->get_visited_cities();
        visited_cities[parent_node->get_city()] = true;

        for (int city = 0; city < city_number; ++city) {
            if (visited_cities[city]) {
                continue;
            }
            auto new_node = new Matrix(parent_node, city, visited_cities, parent_node->get_matrix());
            new_node->reduce_matrix(parent_node->get_city(), city, parent_node->getCost());

            if (upper_bound > new_node->getCost()) {
                upper_bound = new_node->getCost();
                queue.push(new_node);
                lower_node = new_node;
            } else {
                delete new_node;
            }
        }
    }

    int cost = lower_node->getCost();
    vector<int> result_path(city_number + 1, 0);
    for (int i = city_number - 1; i > 0; --i) {
        if (lower_node != nullptr) {
            result_path[i] = lower_node->get_city();
            lower_node = lower_node->get_parent();
        }
    }

    return new AlgorithmResultTO(cost, result_path);
}

vector<vector<int>> LIFOBranchBound::mapToVector(Graph *graph) {
    vector<vector<int>> matrix(graph->get_city_number(), vector<int>(graph->get_city_number()));
    for (int i = 0; i < graph->get_city_number(); ++i) {
        for (int j = 0; j < graph->get_city_number(); ++j) {
            matrix[i][j] = graph->get_adjacent_cities(i)[j];
        }
    }
    return matrix;
}
