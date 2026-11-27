#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

#include "file_storage.hpp"
#include "input_utils.hpp"
#include "student.hpp"
#include "student_manager.hpp"

const std::string DATA_FILE = "students.txt";

int main() {
    //To prevent Doubles that turn into strings from displaying 6 decimals. Rather only 2.
    std::cout << std::fixed << std::setprecision(2);
    std::vector<Student> students;

    // menu loop - show the menu, read a choice, call the matching
    //       operation, repeat until the user picks Exit
    int choice = 0;
    while (choice != 7) {
        displayMenu();
        choice = readNumber("Select an option:", 1, 7);

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: viewAllStudents(students); break;
            case 3: searchStudent(students); break;
            case 4: updateStudentMarks(students); break;
            case 5: deleteStudent(students); break;
            case 6: showClassStatistics(students); break;
            case 7: std::cout << "Goodbye!\n"; break;
            default: std::cout << "How did you get here?\n"; break;
        }
    }
    // TODO (milestone 2): load existing records from DATA_FILE



    // TODO (milestone 2): decide when to save (after every change, on exit, or both)

    return 0;
}
