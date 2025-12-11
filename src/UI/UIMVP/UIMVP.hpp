#include <iostream>
#include <string>
#include <limits>


class UIMVP : public UIInterface {
public:
    // Outputs the given sentence to the standard output.
    void print(const std::string& sentence) override;

    // Prompts the user with the given sentence and returns the input as a string.
    std::string getStringFromUser() override;

    // Prompts the user with a message containing the 'num' value and returns a user-input integer.
    int getNumFromUser() override;
};
