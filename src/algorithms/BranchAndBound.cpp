//
// Created by Zosia on 14.10.2023.
//

#include "BranchAndBound.h"

pair<vector<int>, int> BranchAndBound::process() {
    vector<int> notVisitedCities;
    vector<vector<int>> _bNbMatrix;
    bool has_finished = false;
    vector<BnBNode> nodes;
    int parent_node_index = 0;

    for (int city = 0; city < graph->get_city_number(); ++city) {
        notVisitedCities.push_back(city);
    }

    while (!has_finished) {

    }




    return nullptr;
}
