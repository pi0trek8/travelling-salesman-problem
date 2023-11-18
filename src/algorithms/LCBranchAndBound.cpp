#include <queue>
#include <iomanip>
#include "LCBranchAndBound.h"
#include "Matrix.h"

LCBranchAndBound::LCBranchAndBound(Graph *graph) : graph(graph) {}

// Process function initiates the Lower Bound Branch and Bound algorithm
AlgorithmResultTO *LCBranchAndBound::process() {
    // Get the number of cities in the graph and the graph represented as a vector
    int city_number = graph->get_city_number();
    auto &matrix = graph->get_graph_as_vector();

    // Initialize a priority queue for Branch and Bound traversal, using a custom matrix comparison
    std::priority_queue<Matrix, vector<Matrix>, CompareMatrices> queue;
    auto parent_node = Matrix(0, matrix, vector<int>(), 0);
    parent_node.perform_first_reduction();
    queue.push(parent_node);

    // Find the nearest neighbor result using a heuristic (in this case, nearest neighbor algorithm)
    auto nearest_neighbor_result = find_nearest_neighbor_result(matrix);

    // Initialize upper_bound and best_path based on the nearest neighbor result
    int upper_bound = nearest_neighbor_result.first;
    vector<int> best_path = nearest_neighbor_result.second;

    // Branch and Bound traversal
    while (!queue.empty()) {
        parent_node = queue.top();
        queue.pop();

        // Check if the current node is a leaf node
        if (parent_node.get_tree_level() == city_number - 1) {
            // Update the best path and upper bound if a better path is found
            if (upper_bound > parent_node.getCost()) {
                best_path = parent_node.parents;
                best_path.push_back(parent_node.get_city());
                upper_bound = parent_node.getCost();
            }
            continue;
        }

        // Check if it is worth exploring the node further
        if (parent_node.getCost() < upper_bound) {
            // Explore child nodes
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

    // Add the starting city (0) to the end of the best path
    best_path.push_back(0);

    // Create and return the result object
    return new AlgorithmResultTO(upper_bound, best_path);
}

// Helper function to find the cost and path of the nearest neighbor for a given city
pair<int, std::vector<int>> LCBranchAndBound::nearest_neighbor_cost(const vector<vector<int>> &graph, vector<bool> &visited, int current) {
    int minimum_cost = INT_MAX;
    int city_number = graph.size();
    int nearest_neighbor = -1;

    // Iterate through all cities to find the nearest neighbor
    for (int i = 0; i < city_number; ++i) {
        if (graph[current][i] < minimum_cost && !visited[i]) {
            minimum_cost = graph[current][i];
            nearest_neighbor = i;
        }
    }

    // Return the cost and path to the nearest neighbor
    return std::make_pair(minimum_cost, vector<int>{current, nearest_neighbor});
}

// Function to find the result of the nearest neighbor heuristic for the entire graph
pair<int, vector<int>> LCBranchAndBound::find_nearest_neighbor_result(const vector<vector<int>> &graph) {
    int city_number = graph.size();

    // Initialize visited array, starting city, total cost, and best path
    vector<bool> visited(city_number, false);
    int current = 0;
    visited[current] = true;

    int total_cost = 0;
    vector<int> best_path;

    // Iterate through cities to build the nearest neighbor path
    for (int i = 0; i < city_number - 1; ++i) {
        pair<int, vector<int>> best_neighbor = nearest_neighbor_cost(graph, visited, current);
        total_cost += best_neighbor.first;

        int nearest = best_neighbor.second.back();

        visited[nearest] = true;
        current = nearest;
        best_path.insert(best_path.end(), best_neighbor.second.begin(), best_neighbor.second.end() - 1);
    }

    // Add the starting city (0) to the end of the path
    total_cost += graph[current][0];
    best_path.push_back(0);

    // Return the total cost and the best path
    return make_pair(total_cost, best_path);
}

LCBranchAndBound::~LCBranchAndBound() = default;
