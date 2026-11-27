#ifndef INPUT_UTILS_HPP
#define INPUT_UTILS_HPP

#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>


[[noreturn]] void handleClosedInput();
// Reusable input helpers. Each one keeps asking until it gets valid input,
// so the menu and student operations don't need their own validation loops.
//TODO: handle end of input (CTRL + D)
template <typename T>
T readNumber(const std::string& prompt, T min, T max) {
    //loop until the user enters a whole number between min and max
        T input = 0;
        std::cout << prompt << "\n";
        while(!(std::cin >> input) || input < min || input > max){
            std::cout << "Please enter a valid number between the minimum and maximum\n" 
            std::cout << "Min: " << min << ", Max: " << max << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << prompt << "\n";
        }
        if (std::cin.fail()) {
            handleClosedInput();
        }   
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
}
std::string readLine(const std::string& prompt);
bool readYesNo(const std::string& prompt);

#endif
