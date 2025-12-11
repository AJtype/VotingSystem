#include <iostream>
#include <string>
#include <limits>


class UI {
public:
    // Outputs the given sentence to the standard output.
    void print(const std::string& sentence);

    // Prompts the user with the given sentence and returns the input as a string.
    std::string getStringFromUser();

    // Prompts the user with a message containing the 'num' value and returns a user-input integer.
    int getNumFromUser();
};
