#ifndef FILE_STORAGE_HPP
#define FILE_STORAGE_HPP

#include <string>
#include <vector>
#include "student.hpp"

// Milestone 2: file persistence. Leave these as stubs until the
// in-memory version passes every core acceptance check.

void loadStudents(std::vector<Student>& students, const std::string& filename);
bool saveStudents(const std::vector<Student>& students, const std::string& filename);

#endif
