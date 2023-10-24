#include <random>
#include "RandomGenerator.h"

Graph *RandomGenerator::generate_random(int city_number) {
    random_device randomDevice;
    mt19937 generator(randomDevice());
    uniform_int_distribution<int> random_path_cost_distribution(1, 100);
    auto *graph = new Graph(city_number);

    for (int i = 0; i < city_number; ++i) {
        for (int j = 0; j < city_number; ++j) {
            if (i == j) {
                graph->add_new_connection(i, j, -1);
                continue;
            }
            graph->add_new_connection(i, j, random_path_cost_distribution(generator));
        }
    }

    return graph;
}
