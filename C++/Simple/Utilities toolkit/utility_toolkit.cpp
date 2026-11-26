#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "utilities.hpp"

int main() {
    int selection = 0;
    std::vector<std::string> storageWeightConverter;
    std::vector<std::string> storageDistanceConverter;
    std::vector<std::string> storageTemperatureCalculator;
    std::vector<std::string> storageCalculator;

    while (selection != 5) {
        std::cout << "Type in the number you want to use for the utility\n"
                  << "1. WeightConverter, 2. DistanceConverter, 3. TemperatureCalculations, 4. Calculator, 5. Quit\n";

        if (!(std::cin >> selection) || selection < 1 || selection > 5) {
            // Reset stream error flags and discard invalid input up to the newline
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid selection, of 1 - 5\n";
            continue;
        }

        switch (selection) {
            case 1: {
                int tempSelection = 0;
                double weight = 0.0;
                bool validPlanet = false;
                bool validWeight = false;

                while (!validPlanet) {
                    std::cout << "Select a planet (1. Mercury, 2. Venus, 3. Mars, 4. Jupiter, "
                              << "5. Saturn, 6. Uranus, 7. Neptune, 8. Earth): ";
                    if (std::cin >> tempSelection && tempSelection >= 1 && tempSelection <= 8) {
                        validPlanet = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter a valid selection, of 1 - 8\n";
                    }
                }

                while (!validWeight) {
                    std::cout << "Enter your weight in kg: ";
                    if (std::cin >> weight && weight >= 0.0) {
                        validWeight = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter a positive number for weight.\n";
                    }
                }

                WeightConverter(weight, tempSelection, storageWeightConverter);
                break;
            }
            case 2: {
                double distance = 0.0;
                int directionChoice = 0;
                bool validDistance = false;
                bool validDirection = false;

                while (!validDistance) {
                    std::cout << "Enter distance: ";
                    if (std::cin >> distance && distance >= 0.0) {
                        validDistance = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter a non-negative number for distance.\n";
                    }
                }

                while (!validDirection) {
                    std::cout << "Conversion direction (1 = Miles to Kilometers, 2 = Kilometers to Miles): ";
                    if (std::cin >> directionChoice && (directionChoice == 1 || directionChoice == 2)) {
                        validDirection = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter 1 or 2.\n";
                    }
                }

                DistanceConverter(distance, storageDistanceConverter, directionChoice == 1);
                break;
            }
            case 3: {
                int selection1 = 0;
                int selection2 = 0;
                double temperature = 0.0;
                bool validFrom = false;
                bool validTo = false;
                bool validTemp = false;

                while (!validFrom) {
                    std::cout << "Select starting unit (1 = Celsius, 2 = Fahrenheit, 3 = Kelvin): ";
                    if (std::cin >> selection1 && selection1 >= 1 && selection1 <= 3) {
                        validFrom = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter a valid unit (1 - 3).\n";
                    }
                }

                while (!validTo) {
                    std::cout << "Select target unit (1 = Celsius, 2 = Fahrenheit, 3 = Kelvin): ";
                    if (std::cin >> selection2 && selection2 >= 1 && selection2 <= 3) {
                        validTo = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter a valid unit (1 - 3).\n";
                    }
                }

                while (!validTemp) {
                    std::cout << "Enter temperature value: ";
                    if (std::cin >> temperature) {
                        validTemp = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter a valid number for temperature.\n";
                    }
                }

                TemperatureCalculations(selection1, selection2, temperature, storageTemperatureCalculator);
                break;
            }
            case 4: {
                double num1 = 0.0;
                double num2 = 0.0;
                char op = ' ';
                bool validNum1 = false;
                bool validOp = false;
                bool validNum2 = false;

                while (!validNum1) {
                    std::cout << "Enter first number: ";
                    if (std::cin >> num1) {
                        validNum1 = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter a valid number.\n";
                    }
                }

                while (!validOp) {
                    std::cout << "Enter operator (+, -, *, /): ";
                    if (std::cin >> op && (op == '+' || op == '-' || op == '*' || op == '/')) {
                        validOp = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter one of +, -, *, or /.\n";
                    }
                }

                while (!validNum2) {
                    std::cout << "Enter second number: ";
                    if (std::cin >> num2) {
                        validNum2 = true;
                    } else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Please enter a valid number.\n";
                    }
                }

                calculator(num1, num2, op, storageCalculator);
                break;
            }
            case 5:
                std::cout << "Thank you for participating hope you enjoyed :)\n";
                break;
        }
    }

    // Display all stored results before exiting
    std::cout << "\n--- Session History ---\n";
    for (std::size_t i = 0; i < storageWeightConverter.size(); ++i) {
        std::cout << storageWeightConverter[i];
    }
    for (std::size_t i = 0; i < storageDistanceConverter.size(); ++i) {
        std::cout << storageDistanceConverter[i];
    }
    for (std::size_t i = 0; i < storageTemperatureCalculator.size(); ++i) {
        std::cout << storageTemperatureCalculator[i];
    }
    for (std::size_t i = 0; i < storageCalculator.size(); ++i) {
        std::cout << storageCalculator[i];
    }

    return 0;
}