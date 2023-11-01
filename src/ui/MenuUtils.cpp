#include <iostream>
#include "MenuUtils.h"

std::string MenuUtils::get_time_label(std::string time_label) {
    return time_label == "seconds" ? "time [s]" : "time [micro s]";
}

void MenuUtils::print_separator(int size) {
    std::cout << " ";
    for (int i = 0; i < size; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

int MenuUtils::calculate_path_characters_size(const std::vector<int> &path) {
    int characters_size = 0;
    for (auto city_number : path) {
        characters_size += (city_number > 9) ? 2 : 1;
    }
    return characters_size + path.size();
}
