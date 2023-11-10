#include <queue>
#include <stack>
#include "DFSBranchBound.h"
#include "Matrix.h"

DFSBranchBound::DFSBranchBound(Graph *graph) : graph(graph) {}

AlgorithmResultTO *DFSBranchBound::process() {
    int city_number = graph->get_city_number();
    auto matrix = graph->get_graph_as_vector();

    std::stack<Matrix *> stack;
    auto parent_node = new Matrix(nullptr, 0, vector<bool>(city_number, false), matrix, vector<int>());
    parent_node->perform_first_reduction();

    stack.push(parent_node);

    Matrix *lower_node = nullptr;
    int min = 0;

    int upper_bound = INT_MAX;
    bool is_completed;

    while (!stack.empty()) {
        parent_node = stack.top();
        stack.pop();
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
            auto new_node = new Matrix(parent_node, city, visited_cities, parent_node->get_matrix(), parent_node->parents);
            new_node->reduce_matrix(parent_node->get_city(), city, parent_node->getCost());
            new_node->parents.push_back(parent_node->get_city());
            stack.push(new_node);
        }

        if (is_completed && upper_bound > parent_node->getCost()) {
            lower_node = parent_node;
            upper_bound = parent_node->getCost();
            min++;
        }
    }

    auto result_path = lower_node->parents;
    result_path.push_back(lower_node->get_city());
    result_path.push_back(0);

    return new AlgorithmResultTO(upper_bound, result_path);
}

DFSBranchBound::~DFSBranchBound() = default;
