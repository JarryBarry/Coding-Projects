#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <vector>
#include <string>

const int MAX_ID = 99999;
const int MIN_ID = 1;
// Representation for a single student record.
struct Student {
    int id = 0;
    std::string firstName;
    std::string surname;
    int age = 0;
    std::vector<std::string> subjects{};
    std::vector<double> marks{};
};

#endif
