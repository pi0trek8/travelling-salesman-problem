#include <thread>
#include "ui/MainMenu.h"
#include "graph/Graph.h"
#include "algorithms/Algorithm.h"
#include "algorithms/BruteForce2.h"
#include "algorithms/LCBranchAndBound.h"
#include "algorithms/DFSBranchBound.h"
#include "algorithms/DynamicProgramming.h"
#include "timer/Timer.h"
#include "ui/RandomGenerator.h"

using namespace std;

void automated_tests(const vector<string> &arguments);

void time_limit_thread();

int main(int argc, char *argv[]) {

    MainMenu::create_menu();

//    thread countdown(time_limit_thread);
//    thread count(print_thread);

//    vector<string> arguments;
//    for (int i = 0; i < argc; ++i) {
//        arguments.emplace_back(argv[i]);
//    }
//    automated_tests(arguments);
    return 0;
}

void automated_tests(const vector<string> &arguments) {
    Algorithm *algorithm;
    Timer timer;
    auto randomGenerator = new RandomGenerator();

    float whole_time = 0.0;

    for (int i = 0; i < 10; ++i) {
        auto graph = randomGenerator->generate_random(stoi(arguments[2]));

        if (arguments[1] == "Brute Force") {
            algorithm = new BruteForce2(graph);
        } else if (arguments[1] == "LC Branch and Bound") {
            algorithm = new LCBranchAndBound(graph);

        } else if (arguments[1] == "DFS Branch and Bound") {
            algorithm = new DFSBranchBound(graph);

        } else if (arguments[1] == "Dynamic Programming") {
            algorithm = new DynamicProgramming(graph);
        }

        timer.time_start();
        algorithm->process();
        timer.time_stop();
        whole_time += timer.elapsed_time_in_seconds();
        delete graph;
    }

    cout << whole_time / 10.0;
    delete randomGenerator;
    delete algorithm;
}