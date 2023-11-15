#include <queue>
#include <iomanip>
#include "LCBranchAndBound.h"
#include "Matrix.h"

LCBranchAndBound::LCBranchAndBound(Graph *graph) : graph(graph) {}

AlgorithmResultTO *LCBranchAndBound::process() {
    int city_number = graph->get_city_number();

    auto &matrix = graph->get_graph_as_vector();

    std::priority_queue<Matrix, vector<Matrix>, CompareMatrices> queue;
    auto parent_node = Matrix(0, matrix, vector<int>(), 0);
    parent_node.perform_first_reduction();
    queue.push(parent_node);

    auto nearest_neighbor_result = find_nearest_neighbor_result(matrix);

    int upper_bound = nearest_neighbor_result.first;
    vector<int> best_path = nearest_neighbor_result.second;

    while (!queue.empty()) {
        parent_node = queue.top();
        queue.pop();

        if (parent_node.get_tree_level() == city_number - 1) {
            if (upper_bound > parent_node.getCost()) {
                best_path = parent_node.parents;
                best_path.push_back(parent_node.get_city());
                upper_bound = parent_node.getCost();
            }
            continue;
        }

        if (parent_node.getCost() < upper_bound) {
            for (int city = 0; city < city_number; ++city) {
                if (city == parent_node.get_city() || parent_node.has_city_been_visited(city)) {
                    continue;
                }
                auto new_node = Matrix(city, parent_node.get_matrix(),
                                           parent_node.parents, parent_node.get_tree_level() + 1);
                new_node.reduce_matrix(parent_node.get_city(), city, parent_node.getCost());
                new_node.parents.push_back(parent_node.get_city());
                if (new_node.getCost() <= upper_bound) {
                    queue.push(new_node);
                }
            }
        }
    }
    best_path.push_back(0);

    return new AlgorithmResultTO(upper_bound, best_path);
}


pair<int, std::vector<int>> LCBranchAndBound::nearest_neighbor_cost(const vector<vector<int>> &graph, vector<bool> &visited, int current) {
    int minimum_cost = INT_MAX;
    int city_number = graph.size();
    int nearest_neighbor = -1;

    for (int i = 0; i < city_number; ++i) {
        if (graph[current][i] < minimum_cost && !visited[i]) {
            minimum_cost = graph[current][i];
            nearest_neighbor = i;
        }
    }

    return std::make_pair(minimum_cost, vector<int>{current, nearest_neighbor});

}

pair<int, vector<int>> LCBranchAndBound::find_nearest_neighbor_result(const vector<vector<int>> &graph) {
    int city_number = graph.size();

    vector<bool> visited(city_number, false);
    int current = 0;
    visited[current] = true;

    int total_cost = 0;
    vector<int> best_path;

    for (int i = 0; i < city_number - 1; ++i) {
        pair<int, vector<int>> best_neighbor = nearest_neighbor_cost(graph, visited, current);
        total_cost += best_neighbor.first;

        int nearest = best_neighbor.second.back();

        visited[nearest] = true;
        current = nearest;
        best_path.insert(best_path.end(), best_neighbor.second.begin(), best_neighbor.second.end() - 1);
    }

    total_cost += graph[current][0];
    best_path.push_back(0);

    return make_pair(total_cost, best_path);
}

LCBranchAndBound::~LCBranchAndBound() = default;
