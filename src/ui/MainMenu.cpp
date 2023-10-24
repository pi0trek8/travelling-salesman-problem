#include <iomanip>
#include "MainMenu.h"
#include "ConsoleHelper.h"
#include "../graph/Graph.h"
#include "../file/FileReader.h"
#include "../timer/Timer.h"
#include "../algorithms/BruteForce.h"
#include "../algorithms/BranchAndBound.h"
#include "../algorithms/LIFOBranchBound.h"
#include "RandomGenerator.h"

void MainMenu::create_menu() {
    int choice;
    string buffer;
    Timer timer;
    Algorithm *algorithm;

    auto randomGenerator = new RandomGenerator();
    Graph *graph = nullptr;
    FileReader fileReader;

    while (true) {
        ConsoleHelper::clear_console();
        print_options();
        choice = ConsoleHelper::get_input();
        ConsoleHelper::clear_console();
        switch (choice) {
            case 1: {
                cout << "Enter file path: ";
                cin >> buffer;

                graph = fileReader.read_problem_from_file<Graph>(buffer);

                if (graph == nullptr) {
                    cout << "Reading from file was unsuccessful. Please try again..." << endl;
                    ConsoleHelper::press_key_to_continue();
                }
                break;
            }
            case 2: {
                cout << "Enter how many cities should problem contain: ";
                cin >> buffer;
                //TODO: muss noch ergaenzen werden
                graph = randomGenerator->generate_random(stoi(buffer));
                if (graph == nullptr) {
                    cout << "Problem was created unsuccessful. Please try again..." << endl;
                    ConsoleHelper::press_key_to_continue();
                }
                break;
            }
            case 3: {
                if (graph == nullptr) {
                    cout << "Operation unsuccessful. Generate or read problem from file first." << endl;
                    ConsoleHelper::press_key_to_continue();
                    break;
                }
                cout << "Problem visualisation as a adjacency matrix implementation of a finite graph" << endl << endl;
                graph->print();
                ConsoleHelper::press_key_to_continue();
                break;
            }
            case 4: {
                if (graph == nullptr) {
                    cout << "Operation unsuccessful. Generate or read problem from file first." << endl;
                    ConsoleHelper::press_key_to_continue();
                    break;
                }
                delete algorithm;
                algorithm = new BruteForce();
                cout << "Algorithm Brute force" << endl;
                timer.time_start();
                auto result = algorithm->process(graph);
                timer.time_stop();

                cout << "Algorithm results: " << endl;
                generate_result_table(result->getPathCost(), result->getPath(), timer.elapsed_time());

                ConsoleHelper::press_key_to_continue();
                delete result;
                break;
            }
            case 5: {
                if (graph == nullptr) {
                    cout << "Operation unsuccessful. Generate or read problem from file first." << endl;
                    ConsoleHelper::press_key_to_continue();
                    break;
                }
                delete algorithm;
                cout << "Algorithm LC Branch & Bound" << endl;
                algorithm = new BranchAndBound();

                timer.time_start();
                auto result = algorithm->process(graph);
                timer.time_stop();

                cout << "Algorithm results: " << endl;
                generate_result_table(result->getPathCost(), result->getPath(), timer.elapsed_time());

                ConsoleHelper::press_key_to_continue();
                break;
            }
            case 6: {
                if (graph == nullptr) {
                    cout << "Operation unsuccessful. Generate or read problem from file first." << endl;
                    ConsoleHelper::press_key_to_continue();
                    break;
                }

                delete algorithm;
                cout << "Algorithm FIFO Branch & Bound" << endl;
                algorithm = new LIFOBranchBound();

                timer.time_start();
                auto result = algorithm->process(graph);
                timer.time_stop();

                cout << "Algorithm results: " << endl;
                generate_result_table(result->getPathCost(), result->getPath(), timer.elapsed_time());

                ConsoleHelper::press_key_to_continue();
                break;
            }
            case 7: {

                break;
            }
            default: {
                break;
            }
        }
    }

}


void MainMenu::print_options() {
    cout << endl;
    cout << "Travelling Salesman Problem Menu: " << std::endl;
    cout << "1. Read from file" << std::endl;
    cout << "2. Generate random problem" << std::endl;
    cout << "3. Display problem as adjacency matrix graph representation" << std::endl;
    cout << "4. Algorithm - Brute Force" << std::endl;
    cout << "5. Algorithm - LC Branch & Bound" << std::endl;
    cout << "6. Algorithm - FIFO Branch & Bound" << std::endl;
    cout << "7. Algorithm - Dynamic Programming" << std::endl;
    cout << "8. Go back" << std::endl;
    cout << "Choose: ";
}


void MainMenu::generate_result_table(int cost, vector<int> path, pair<string, long long> elapsed_time) {
    int characters_size = 0;
    for (auto city_number: path) {
        if (city_number > 9) {
            characters_size += 2;
        } else {
            characters_size += 1;
        }
    }
    characters_size += path.size();
    string time_label = "";
    if (elapsed_time.first == "seconds") {
        time_label = "time [s]";
    } else {
        time_label = "time [micro s]";
    }

    std::cout << "| " << std::setw(8) << "cost" << " | "
              << std::setw(characters_size) << "path " << "| "
              << std::setw(time_label.size()) << time_label << " |" << std::endl;
    int separator_size = 16 + characters_size + time_label.size();

    for (int i = 0; i < separator_size; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;

    std::cout << "| " << std::setw(8) << cost << " | ";

    for (int city: path) {
        if (city > 9) {
            std::cout << std::setw(2) << city << " ";
        } else {
            std::cout << std::setw(1) << city << " ";
        }
    }

    std::cout << "| " << std::setw(time_label.size()) << elapsed_time.second << " |" << std::endl;

}