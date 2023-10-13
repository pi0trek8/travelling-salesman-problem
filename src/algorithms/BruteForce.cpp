#include "BruteForce.h"

void BruteForce::process(Graph *graph) {
    Array<int> possible_path;

    for (int i = 0; i < graph->get_city_number(); i++) {
        possible_path.push_back(i);
    }
    create_permutations(graph, possible_path, 1, graph->get_city_number() - 1);

    int minimal_cost = calculate_best_option(graph);


    cout << endl << "Final result: \t" << possible_paths.get_size() << endl;
    for (int i = 0; i < possible_paths.get_size(); ++i) {
        for (int j = 0; j < possible_paths[i].get_size(); ++j) {
            cout << possible_paths[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Total cost: " << minimal_cost << endl;
}

void BruteForce::create_permutations(Graph *graph, Array<int> permutation, int first_city, int last_city) {
    if (first_city == last_city) {
        cout << "Permutation: ";
        permutation.print();
        // check if permutation is in the problem's graph
        for (int i = 0; i < permutation.get_size() - 1; ++i) {
            if (!graph->find_adjacent_city(permutation.get(i), permutation.get(i + 1))) {
                return;
            }
        }

        // find if there is a connection zwischen last city and first city
        if (!graph->find_adjacent_city(permutation.get(permutation.get_size() - 1), permutation.get(0))) {
            return;
        }
        permutation.push_back(0);
        cout << "Permutation: ";
        permutation.print();

        // add permutation
        possible_paths.push_back(permutation);
        return;
    }

    for (int i = first_city; i < permutation.get_size(); ++i) {
        permutation.swap(first_city, i);
        create_permutations(graph, permutation, first_city + 1, last_city);
        permutation.swap(first_city, i);
    }
}

int BruteForce::calculate_best_option(Graph *graph) {
    int minimal_cost = INT_MAX;
    for (int i = 0; i < possible_paths.get_size(); ++i) {
        int cost = calculate_total_path_cost(graph, possible_paths[i]);
        if(minimal_cost > cost) {
            minimal_cost = cost;
        }
    }
    return minimal_cost;
}

int BruteForce::calculate_total_path_cost(Graph *graph, Array<int> array) {
    auto total_cost = 0;
    for (int i = 0; i < array.get_size() - 1; ++i) {
        total_cost += graph->get_edge_cost_if_exists(array[i], array[i + 1]);
    }
    return total_cost;
}
