#include "UIMVP.hpp"

void UIMVP::print(const std::string& sentence) {
    std::cout << sentence << std::endl;
}

std::string UIMVP::getStringFromUser() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int UIMVP::getNumFromUser() {
    int input;
    std::cin >> input;
    // To consume the trailing newline for future std::getline calls:
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}