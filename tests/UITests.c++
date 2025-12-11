#include "../src/UI/UIMVP/UIMVP.hpp"
#include "../src/UI/UInterface.hpp"
#include <cassert>
#include <sstream>

void test_print() {
    UIInterface ui = UIMVP();
    std::ostringstream oss;
    // Redirect std::cout to oss
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());

    std::string sentence = "Hello, world!";
    ui.print(sentence);

    // Restore std::cout
    std::cout.rdbuf(old_cout);

    std::string output = oss.str();
    // std::endl adds a newline
    assert(output == "Hello, world!\n");
}

void test_getStringFromUser() {
    UIInterface ui = UIMVP();
    std::istringstream iss("Test string\n");
    std::streambuf* old_cin = std::cin.rdbuf(iss.rdbuf());

    std::string result = ui.getStringFromUser();

    std::cin.rdbuf(old_cin);

    assert(result == "Test string");
}

void test_getNumFromUser() {
    UIInterface ui = UIMVP();
    std::istringstream iss("42\n");
    std::streambuf* old_cin = std::cin.rdbuf(iss.rdbuf());

    int result = ui.getNumFromUser();

    std::cin.rdbuf(old_cin);

    assert(result == 42);
}

int main() {
    test_print();
    test_getStringFromUser();
    test_getNumFromUser();
    std::cout << "All UI tests passed!\n";
    return 0;
}

// g++ -std=c++17 -I../src/UIMVP -o UITests UITests.c++ ../src/UIMVP/UI.c++
