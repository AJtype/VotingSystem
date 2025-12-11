#include "UI.hpp"

void UI::print(const std::string& sentence) {
    std::cout << sentence << std::endl;
}

std::string UI::getStringFromUser() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int UI::getNumFromUser() {
    int input;
    std::cin >> input;
    // To consume the trailing newline for future std::getline calls:
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}