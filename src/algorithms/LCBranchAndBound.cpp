#include <queue>
#include <iomanip>
#include "LCBranchAndBound.h"
#include "Matrix.h"

LCBranchAndBound::LCBranchAndBound(Graph *graph) : graph(graph) {}

AlgorithmResultTO *LCBranchAndBound::process() {
    int city_number = graph->get_city_number();

    const auto &matrix = graph->get_graph_as_vector();

    std::priority_queue<Matrix, vector<Matrix>, CompareMatrices> queue;
    auto parent_node = Matrix(0, matrix, vector<int>());
    parent_node.perform_first_reduction();
    queue.push(parent_node);

    Matrix lower_node;

    // calculate first upper bound using najblizszego sasiada
    int upper_bound = INT_MAX;

    while (!queue.empty()) {
        parent_node = queue.top();
        queue.pop();

        if (parent_node.is_single_candidate()) {
            if (upper_bound > parent_node.getCost() / 2) {
                cout << parent_node.get_city() << " with cost: "<<parent_node.getCost() << endl;
                lower_node = parent_node;
                upper_bound = parent_node.getCost() / 2;
            }
            continue;
        }

        if( parent_node.getCost() + 1> upper_bound) {
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
                queue.push(new_node);
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

    return new AlgorithmResultTO(lower_node.getCost(), result_path);
}

LCBranchAndBound::~LCBranchAndBound() = default;
