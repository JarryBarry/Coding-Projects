#ifndef STUDENT_MANAGER_HPP
#define STUDENT_MANAGER_HPP

#include <vector>
#include "student.hpp"

// --- Helpers shared by several operations ---
int findStudentIndex(const std::vector<Student>& students, int id);  // -1 if not found
double calculateAverage(const Student& student);
void displayStudent(const Student& student);

// --- Menu operations ---
void displayMenu();
void addStudent(std::vector<Student>& students);
void viewAllStudents(const std::vector<Student>& students);
void searchStudent(const std::vector<Student>& students);
void updateStudentMarks(std::vector<Student>& students);
void deleteStudent(std::vector<Student>& students);
void showClassStatistics(const std::vector<Student>& students);

#endif
