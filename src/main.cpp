#include <iostream>
#include "list/List.h"
#include "graph/Graph.h"
#include "algorithms/BruteForce.h"

using namespace std;

int main(int argc, char *argv[]) {
    auto *tsp = new Graph(4);
    tsp->add_new_connection(0, 1, 1);
    tsp->add_new_connection(0, 2, 1);
    tsp->add_new_connection(0, 3, 1);
    tsp->add_new_connection(1, 0, 1);
    tsp->add_new_connection(1, 2, 1);
    tsp->add_new_connection(1, 3, 1);
    tsp->add_new_connection(2, 0, 1);
    tsp->add_new_connection(2, 1, 1);
    tsp->add_new_connection(2, 3, 1);
    tsp->add_new_connection(3, 0, 1);
    tsp->add_new_connection(3, 1, 1);
    tsp->add_new_connection(3, 2, 1);

//    tsp.print();
    BruteForce bruteForce;
    bruteForce.process(tsp);

//    cout << endl << endl << "Sansiedzi:  ";
//    tsp.get_adjacent_cities(2).print();

    return 0;
}