//
// Created by Zosia on 01.11.2023.
//

#ifndef TRAVELLING_SALESMAN_PROBLEM_MENUUTILS_H
#define TRAVELLING_SALESMAN_PROBLEM_MENUUTILS_H


#include <string>
#include <vector>

namespace MenuUtils {
    std::string get_time_label(std::string time_label);

    void print_separator(int size);

    int calculate_path_characters_size(const std::vector<int> &path);

}
#endif //TRAVELLING_SALESMAN_PROBLEM_MENUUTILS_H
