#ifndef TRAVELLING_SALESMAN_PROBLEM_MAINMENU_H
#define TRAVELLING_SALESMAN_PROBLEM_MAINMENU_H

using namespace std;
#include <iostream>
#include <vector>

namespace MainMenu {
    void create_menu();

    void print_options();

    void generate_result_table(int cost, vector<int> path, long long elapsed_time);
}

#endif //TRAVELLING_SALESMAN_PROBLEM_MAINMENU_H
