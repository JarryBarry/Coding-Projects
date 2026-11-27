#include "student_manager.hpp"

#include <iostream>
#include <string>
#include <vector>
#include "input_utils.hpp"

// ---------- Helpers ----------

int findStudentIndex(const std::vector<Student>& students, int id) {
    // return the position of the student with this ID, or -1 if not found
    for(std::size_t i = 0; i < students.size(); i++){
        if(students[i].id == id){
            return i;
        }
    }
    return -1;
}

double calculateAverage(const Student& student) {
    // Average of the student's marks
    double average = 0;
    if(!student.marks.empty()){
        for(std::size_t i = 0; i < student.marks.size(); i++){
            average += student.marks[i];
        } 
        average = average/student.marks.size();  
    }
    return average;
}

void displayStudent(const Student& student) {
    // print ID, names, age, subjects with their mark and the average
    std::cout << "Student ID: " << student.id << "\n";
    std::cout << "Name: " << student.firstName << " " << student.surname << "\n";
    std::cout << "Age: " << student.age << "\n";
    std::cout << "Marks:\n";
    // addStudent always gives a student the same number of subjects and marks,
    // so indexing subjects[i] with a marks index is safe
    for (std::size_t i = 0; i < student.marks.size(); i++) {
        std::cout << "  " << student.subjects[i] << ": " << student.marks[i] << "\n";
    }
    std::cout << "Student Average: " << calculateAverage(student) << "\n";
}

// ---------- Menu operations ----------

void displayMenu() {
    // Only prints. Reading the choice and acting on it is main()'s job.
    std::cout << "\n========== Student Management System ==========\n";
    std::cout << "1. Add Student\n";
    std::cout << "2. View All Students\n";
    std::cout << "3. Search Student\n";
    std::cout << "4. Update Student Marks\n";
    std::cout << "5. Delete Student\n";
    std::cout << "6. Show Class Statistics\n";
    std::cout << "7. Exit\n\n";
}

void addStudent(std::vector<Student>& students) {
    // Build the student in a local variable and only add it to the list once
    // everything has been entered, so a half-finished student never ends up in it
    Student newStudent;

    // Ask for the ID first, so a duplicate is rejected before the user types anything else
    int id = readNumber("Enter the student's ID: ",  MIN_ID, MAX_ID);
    while (findStudentIndex(students, id) != -1) {
        std::cout << "That ID already exists. Please enter a different one.\n";
        id = readNumber("Enter the student's ID: ",  MIN_ID, MAX_ID);
    }
    newStudent.id = id;

    newStudent.firstName = readLine("Enter the student's first name: ");
    newStudent.surname = readLine("Enter the student's surname: ");
    newStudent.age = readNumber("Enter the student's age: ", 7, 21);

    // At least one subject, otherwise the student would have no marks to average
    int subjectAmount = readNumber("How many subjects does the student have? ", 1, 100);
    for (int i = 0; i < subjectAmount; i++) {
        newStudent.subjects.push_back(readLine("Enter the name of subject " + std::to_string(i + 1) + ": "));
    }
    for (int i = 0; i < subjectAmount; i++) {
        newStudent.marks.push_back(readNumber("Enter the mark for " + newStudent.subjects[i] + ": ", 0.0, 100.0));
    }

    students.push_back(newStudent);
    std::cout << "Student added successfully.\n";
}

void viewAllStudents(const std::vector<Student>& students) {
    // list every student, or say there are none
    if (students.size() != 0){
        for(std::size_t i = 0; i < students.size(); i++){
        displayStudent(students[i]);
        std::cout << "\n";
        }
    }
    else{
        std::cout << "There are no students.\n";
    }   
}

void searchStudent(const std::vector<Student>& students) {
    //find by ID and display, or say not found
    int id = readNumber("Enter the student's ID: ", MIN_ID, MAX_ID); 
    int index = findStudentIndex(students,id);
    if(index == -1){
        std::cout << "Student not found.\n";
    }else{
        displayStudent(students[index]);
    }
}

void updateStudentMarks(std::vector<Student>& students) {
    //find by ID, replace marks, show updated record
    int index = findStudentIndex(students, readNumber("Enter the student's ID: ", MIN_ID, MAX_ID));
    if(index != -1){
        for(std::size_t i = 0; i < students[index].subjects.size(); i++){
            std::cout << i+1 << ". " << students[index].subjects[i] << "\n";
        }
        int subjectSelection = readNumber("Select the subject's mark you'd like to edit, number selections 1. Example Subject: ", 
        1, static_cast<int>(students[index].subjects.size()));
        students[index].marks[subjectSelection-1] = readNumber("Enter the new mark: ", 0.0, 100.0);
        std::cout << "Updated Successfully.\n";
        displayStudent(students[index]);
    }else{
        std::cout << "Student not found.\n";
    }
    
    
}

void deleteStudent(std::vector<Student>& students) {
    // find by ID, confirm, remove
    int index = findStudentIndex(students, readNumber("Enter the student's ID: ", MIN_ID, MAX_ID));
    if(index != -1){
        if(readYesNo("Are you sure you want to delete?" + students[index].firstName + " " + students[index].surname + " ID: " +
            std::to_string(students[index].id) + "Y/N, y/n")){
            students.erase(students.begin() + index);
            std::cout << "Student has been removed";
        }else{
            std::cout << "Deletion cancelled";
        }
    }else{
        std::cout << "Student not found.\n";
    }
}

void showClassStatistics(const std::vector<Student>& students) {
    // class average, highest, lowest, total
    double averageMarks = 0.0;
    double highestMark = 0.0;
    int indexHighestStudentMark;
    double lowestMark = 100.0;
    int indexLowestStudentMark;
    int totalStudents = students.size();
    if (totalStudents != 0){
            for(std::size_t i = 0; i < students.size(); i++){
            averageMarks += calculateAverage(students[i]);
        }
        averageMarks = averageMarks/students.size();
        for(std::size_t j = 0; j < students.size(); j++){
            double average =  calculateAverage(students[j]);
            if(average > highestMark){
                highestMark = average;
                indexHighestStudentMark = j;
            }
            if(average < lowestMark){
                lowestMark = average;
                indexLowestStudentMark = j;
            }

        }
        std::cout << "The class average is: " << averageMarks << " \n";
        std::cout << "The highest average: " << highestMark << " belongs to:\n"
            << students[indexHighestStudentMark].firstName << " "
            << students[indexHighestStudentMark].surname << "\n\n";
        std::cout << "The lowest average: " << lowestMark << " belongs to:\n"
            << students[indexLowestStudentMark].firstName << " "
            << students[indexLowestStudentMark].surname << "\n\n";
        std::cout << "The entire class's size is: " << totalStudents << "\n";
    }else{
        std::cout << "There are no students.\n";
    }
}