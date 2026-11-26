#include <iostream>
#include <string>
#include <vector>

void WeightConverter(double weight, int planet_choice, std::vector<std::string>& storageWeightConverter) {
    std::string message;

    switch (planet_choice) {
        case 1:
            message = "Your weight of " + std::to_string(weight) +
                      "kg on planet Mercury: " + std::to_string(weight * 0.378) + "\n";
            break;
        case 2:
            message = "Your weight of " + std::to_string(weight) +
                      "kg on planet Venus: " + std::to_string(weight * 0.907) + "\n";
            break;
        case 3:
            message = "Your weight of " + std::to_string(weight) +
                      "kg on planet Mars: " + std::to_string(weight * 0.377) + "\n";
            break;
        case 4:
            message = "Your weight of " + std::to_string(weight) +
                      "kg on planet Jupiter: " + std::to_string(weight * 2.36) + "\n";
            break;
        case 5:
            message = "Your weight of " + std::to_string(weight) +
                      "kg on planet Saturn: " + std::to_string(weight * 0.916) + "\n";
            break;
        case 6:
            message = "Your weight of " + std::to_string(weight) +
                      "kg on planet Uranus: " + std::to_string(weight * 0.889) + "\n";
            break;
        case 7:
            message = "Your weight of " + std::to_string(weight) +
                      "kg on planet Neptune: " + std::to_string(weight * 1.12) + "\n";
            break;
        default:
            message = "Your weight of " + std::to_string(weight) +
                      "kg on planet Earth: " + std::to_string(weight) + "\n";
            break;
    }

    storageWeightConverter.push_back(message);
    std::cout << storageWeightConverter.back();
}

void DistanceConverter(double distance, std::vector<std::string>& storageDistanceConverter, bool toKilometers) {
    std::string message;

    if (toKilometers) {
        message = std::to_string(distance) + " Miles is " +
                  std::to_string(distance * 1.609344) + " kilometers\n";
    } else {
        message = std::to_string(distance) + " Kilometers is " +
                  std::to_string(distance * 0.621371) + " miles\n";
    }

    storageDistanceConverter.push_back(message);
    std::cout << storageDistanceConverter.back();
}

void TemperatureCalculations(int selection1, int selection2, double temperature, std::vector<std::string>& storageTemperatureCalculator) {
    std::string message;

    if (selection1 == 1 && selection2 == 2) {
        message = std::to_string(temperature) + " Celsius is " +
                  std::to_string((temperature * 1.8) + 32.0) + " Fahrenheit\n";
    } else if (selection1 == 1 && selection2 == 3) {
        message = std::to_string(temperature) + " Celsius is " +
                  std::to_string(temperature + 273.15) + " Kelvin\n";
    } else if (selection1 == 2 && selection2 == 1) {
        message = std::to_string(temperature) + " Fahrenheit is " +
                  std::to_string((temperature - 32.0) / 1.8) + " Celsius\n";
    } else if (selection1 == 2 && selection2 == 3) {
        message = std::to_string(temperature) + " Fahrenheit is " +
                  std::to_string(((temperature - 32.0) / 1.8) + 273.15) + " Kelvin\n";
    } else if (selection1 == 3 && selection2 == 1) {
        message = std::to_string(temperature) + " Kelvin is " +
                  std::to_string(temperature - 273.15) + " Celsius\n";
    } else if (selection1 == 3 && selection2 == 2) {
        message = std::to_string(temperature) + " Kelvin is " +
                  std::to_string(((temperature - 273.15) * 1.8) + 32.0) + " Fahrenheit\n";
    } else if (selection1 == 1 && selection2 == 1) {
        message = std::to_string(temperature) + " Celsius is " +
                  std::to_string(temperature) + " Celsius\n";
    } else if (selection1 == 2 && selection2 == 2) {
        message = std::to_string(temperature) + " Fahrenheit is " +
                  std::to_string(temperature) + " Fahrenheit\n";
    } else if (selection1 == 3 && selection2 == 3) {
        message = std::to_string(temperature) + " Kelvin is " +
                  std::to_string(temperature) + " Kelvin\n";
    } else {
        message = "Invalid unit selection\n";
    }

    storageTemperatureCalculator.push_back(message);
    std::cout << storageTemperatureCalculator.back();
}

void calculator(double num1, double num2, char op, std::vector<std::string>& storageCalculator) {
    std::string message;

    switch (op) {
        case '+':
            message = std::to_string(num1) + " + " + std::to_string(num2) +
                      " = " + std::to_string(num1 + num2) + "\n";
            break;
        case '-':
            message = std::to_string(num1) + " - " + std::to_string(num2) +
                      " = " + std::to_string(num1 - num2) + "\n";
            break;
        case '*':
            message = std::to_string(num1) + " * " + std::to_string(num2) +
                      " = " + std::to_string(num1 * num2) + "\n";
            break;
        case '/':
            // Check denominator first so dividing by zero writes a message instead of dividing
            if (num2 == 0.0) {
                message = "Cannot divide by zero\n";
            } else {
                message = std::to_string(num1) + " / " + std::to_string(num2) +
                          " = " + std::to_string(num1 / num2) + "\n";
            }
            break;
        default:
            message = "Invalid operator\n";
            break;
    }

    storageCalculator.push_back(message);
    std::cout << storageCalculator.back();
}