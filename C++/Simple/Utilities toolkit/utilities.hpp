#include <string>
#include <vector>
void WeightConverter(double weight, int planet_choice, std::vector<std::string>& storageWeightConverter);
void DistanceConverter(double distance, std::vector<std::string>& storageDistanceConverter, bool toKilometers = true);
void TemperatureCalculations(int selection1, int selection2, double temperature, std::vector<std::string>& storageTemperatureCalculator);
void calculator(double num1, double num2, char op, std::vector<std::string>& storageCalculator);