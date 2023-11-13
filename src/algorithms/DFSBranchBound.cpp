#include <queue>
#include <stack>
#include "DFSBranchBound.h"
#include "Matrix.h"

DFSBranchBound::DFSBranchBound(Graph *graph) : graph(graph) {}

AlgorithmResultTO *DFSBranchBound::process() {
    int city_number = graph->get_city_number();
    auto matrix = graph->get_graph_as_vector();

    std::stack<Matrix> stack;
    auto parent_node = Matrix(0, matrix, vector<int>(), 0);
    parent_node.perform_first_reduction();

    stack.push(parent_node);

    Matrix lower_node;

    int upper_bound = findNearestNeighborCost(matrix) + 1;
    cout << upper_bound;

    while (!stack.empty()) {
        parent_node = stack.top();
        stack.pop();

        if (parent_node.is_single_candidate()) {
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
                    stack.push(new_node);
                }
            }
        }
    }

    auto result_path = lower_node.parents;
    result_path.push_back(lower_node.get_city());
    result_path.push_back(0);

    return new AlgorithmResultTO(upper_bound, result_path);
}

int DFSBranchBound::nearestNeighborCost(const vector<vector<int>> &graph, vector<bool> &visited, int current) {
    int minDistance = INT_MAX;
    int numNodes = graph.size();

    for (int i = 0; i < numNodes; ++i) {
        if (graph[current][i] < minDistance && !visited[i]) {
            minDistance = graph[current][i];
        }
    }
    return minDistance;
}

int DFSBranchBound::findNearestNeighborCost(const vector<vector<int>> &graph) {
    int numNodes = graph.size();

    vector<bool> visited(numNodes, false);

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

    totalDistance += graph[current][0];

    return totalDistance;
}

DFSBranchBound::~DFSBranchBound() = default;
