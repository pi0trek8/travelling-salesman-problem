#include <iostream>
#include "list/List.h"

using namespace std;

int main(int argc, char *argv[]) {
    auto* list = new List<int>;
    list->push_back(10);
    list->push_back(12);

    for(auto node : *list) {
        cout << node << endl;
    }
    list->print();
    cout << "Hello World!" << endl;
    return 0;
}