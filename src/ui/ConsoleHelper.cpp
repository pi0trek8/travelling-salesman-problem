#include "ConsoleHelper.h"
#include <limits>

using namespace std;

int ConsoleHelper::get_input() {
    cin.clear();
    string input;
    cin >> input;
    return stoi(input);
}

void ConsoleHelper::press_key_to_continue() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << endl << "Press enter to continue...";
    cin.get();
}

void ConsoleHelper::clear_console() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}