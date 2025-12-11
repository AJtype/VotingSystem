#pragma once
#include <string>

class UIInterface {
public:
    virtual ~UIMV() = default;

    // Display a string to the user
    virtual void print(const std::string& sentence) = 0;

    // Get a string from user input
    virtual std::string getStringFromUser() = 0;

    // Get a number from user input
    virtual int getNumFromUser() = 0;
};
