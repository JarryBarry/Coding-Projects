#include "file_storage.hpp"

#include <fstream>
#include <string>
#include <vector>

void loadStudents(std::vector<Student>& students, const std::string& filename) {
    // TODO: read records from the file; a missing or empty file is not an error
}

bool saveStudents(const std::vector<Student>& students, const std::string& filename) {
    // TODO: write every record to the file; return false if it can't be opened
    return false;
}
