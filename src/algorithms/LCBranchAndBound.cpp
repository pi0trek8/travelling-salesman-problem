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

    Matrix lower_node;

    int upper_bound = findNearestNeighborCost(matrix);
    cout << upper_bound;

    while (!queue.empty()) {
        parent_node = queue.top();
        queue.pop();

        if (parent_node.get_tree_level() == city_number - 1) {
            if (upper_bound > parent_node.getCost()) {
                cout << parent_node.get_city() << " with cost: " << parent_node.getCost() << endl;
                lower_node = parent_node;
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
    auto result_path = lower_node.parents;
    result_path.push_back(lower_node.get_city());
    result_path.push_back(0);

    return new AlgorithmResultTO(lower_node.getCost(), result_path);
}


int LCBranchAndBound::nearestNeighborCost(const vector<vector<int>> &graph, vector<bool> &visited, int current) {
    int minDistance = INT_MAX;
    int numNodes = graph.size();

    for (int i = 0; i < numNodes; ++i) {
        if (graph[current][i] < minDistance && !visited[i]) {
            minDistance = graph[current][i];
        }
    }
    return minDistance;
}

// Function to find the shortest path using nearest neighbor algorithm and return the cost
int LCBranchAndBound::findNearestNeighborCost(const vector<vector<int>> &graph) {
    int numNodes = graph.size();

    vector<bool> visited(numNodes, false);

    // Start from node 0
    int current = 0;
    visited[current] = true;

    int totalDistance = 0;

    for (int i = 0; i < numNodes - 1; ++i) {
        int nearestCost = nearestNeighborCost(graph, visited, current);
        totalDistance += nearestCost;

        int nearest = INT_MAX;
        for (int j = 0; j < numNodes; ++j) {
            if (graph[current][j] == nearestCost && !visited[j]) {
                nearest = j;
                break;
            }
        }

        if (nearest == INT_MAX) {
            break;
        }

        visited[nearest] = true;
        current = nearest;
    }

    totalDistance += graph[current][0]; // Return to the starting node

    return totalDistance;
}

LCBranchAndBound::~LCBranchAndBound() = default;
