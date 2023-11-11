#include <queue>
#include <stack>
#include "DFSBranchBound.h"
#include "Matrix.h"

DFSBranchBound::DFSBranchBound(Graph *graph) : graph(graph) {}

AlgorithmResultTO *DFSBranchBound::process() {
    int city_number = graph->get_city_number();
    auto matrix = graph->get_graph_as_vector();

    std::stack<Matrix> stack;
    auto parent_node = Matrix(0,  matrix, vector<int>());
    parent_node.perform_first_reduction();

    stack.push(parent_node);

    Matrix lower_node;
    int min = 0;

    int upper_bound = INT_MAX;
    bool is_completed;

    while (!stack.empty()) {
        parent_node = stack.top();
        stack.pop();

        if (parent_node.is_single_candidate()) {
            if (upper_bound > parent_node.getCost() / 2) {
                cout << parent_node.get_city() << " with cost: "<<parent_node.getCost() << endl;
                lower_node = parent_node;
                upper_bound = parent_node.getCost() / 2;
            }
            continue;
        }

        for (int city = 0; city < city_number; ++city) {
            if (city == parent_node.get_city() || parent_node.has_city_been_visited(city)) {
                continue;
            }

            auto new_node = Matrix(city, parent_node.get_matrix(),
                                   parent_node.parents);
            new_node.reduce_matrix(parent_node.get_city(), city, parent_node.getCost());
            new_node.parents.push_back(parent_node.get_city());
            if (new_node.getCost() / 2 <= upper_bound) {
                stack.push(new_node);
            }
        }
//        if (represents_single_candidate && upper_bound > parent_node->getCost()) {
//            lower_node = parent_node;
//            upper_bound = parent_node->getCost();
//        }
    }

    auto result_path = lower_node.parents;
    result_path.push_back(lower_node.get_city());
    result_path.push_back(0);

    return new AlgorithmResultTO(upper_bound, result_path);
}

DFSBranchBound::~DFSBranchBound() = default;
