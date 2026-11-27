#include "input_utils.hpp"

#include <iostream>
#include <cctype>
#include <string>

void handleClosedInput() {
    // TODO (milestone 2): exit() skips anything main() would do on the way out,
    // such as saving. Either save after every change, or throw an exception here
    // and catch it in main.
    std::cout << "\nInput closed. Exiting.\n";
    std::exit(0);
}

//TODO: handle end of input (CTRL + D)
std::string readLine(const std::string& prompt) {
    //read a full line of text and reject empty input
    std::string input;
    std::cout << prompt << "\n";
    while (std::getline(std::cin, input) && input.find_first_not_of(" \t") == std::string::npos) {
        std::cout << "You cannot enter no value\n";
        std::cout << prompt << "\n";
    }
    if (std::cin.fail()) {
        handleClosedInput();
    }
    input.erase(0, input.find_first_not_of(" \t"));
    input.erase(input.find_last_not_of(" \t") + 1);
    return input;
}

bool readYesNo(const std::string& prompt) {
    // accept y/Y or n/N and return true for yes
    std::string input;
    std::cout << prompt << "\n";
    while (std::getline(std::cin, input)) {
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        if (input.length() == 1) {
            char c = std::tolower(static_cast<unsigned char>(input[0]));
            if (c == 'y') return true;
            if (c == 'n') return false;
        }

        std::cout << "Please enter y or n\n";
        std::cout << prompt << "\n";
    }
    if (std::cin.fail()) {
        handleClosedInput();
    }
    return false;
}
