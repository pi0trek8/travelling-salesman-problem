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
#include "file/FileReader.h"

using namespace std;

void automated_tests(const vector<string> &arguments);

int main(int argc, char *argv[]) {

//    MainMenu::create_menu();

    vector<string> arguments;
    for (int i = 0; i < argc; ++i) {
        arguments.emplace_back(argv[i]);
    }
    automated_tests(arguments);
    return 0;
}

void automated_tests(const vector<string> &arguments) {
    Algorithm *algorithm;
    Timer timer;
    auto randomGenerator = new RandomGenerator();
    FileReader fileReader;

    float whole_time = 0.0;
    if (arguments[2].ends_with(".txt")) {
        auto graph = fileReader.read_problem_from_file<Graph>(arguments[2]);

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
    } else {
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
        auto result = algorithm->process();
        timer.time_stop();
        whole_time += timer.elapsed_time_in_seconds();
        delete graph;
    }

    cout << whole_time;
    delete randomGenerator;
    delete algorithm;
}
