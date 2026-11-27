# Student Manager

## Build and run

```
g++ -std=c++17 -Wall -Wextra *.cpp -o student_manager
./student_manager
```

## Files

| File | Purpose |
|---|---|
| `student.hpp` | `Student` struct and `NUM_SUBJECTS` |
| `input_utils.hpp/.cpp` | Validated input helpers |
| `student_manager.hpp/.cpp` | Menu and the six student operations |
| `file_storage.hpp/.cpp` | Save/load (milestone 2) |
| `main.cpp` | Load, menu loop, exit |

## Acceptance checklist

- [X] Add multiple students
- [X] Duplicate IDs rejected
- [X] View all students
- [X] Search for a student
- [X] Update marks
- [X] Delete students
- [X] Class statistics correct
- [X] Empty records handled
- [X] Invalid menu input handled
- [X] Program stays running after each operation
- [ ] Data saved to a file
- [ ] Data loaded on startup
- [ ] Updates and deletions persist after restart
- [ ] Program exits cleanly

## Build order

Compile, run and try to break the program after each step before moving on.

- [X] 1. Input helpers: `readNumber`, `readLine`, `readYesNo`
- [X] 2. Menu loop in `main` with `displayMenu` and Exit only
      → test: invalid menu input, clean exit
- [X] 3. `calculateAverage` and `displayStudent`
- [X] 4. `addStudent`
- [X] 5. `viewAllStudents`
      → test: add several students, view them, view with none added
- [X] 6. `findStudentIndex`, then add the duplicate ID check to `addStudent`
      → test: duplicate IDs rejected
- [X] 7. `searchStudent`
- [X] 8. `updateStudentMarks`
- [X] 9. `deleteStudent`
      → test: each one with an existing ID, a missing ID and an empty list
- [X] 10. `showClassStatistics`
      → test: several students, one student, no students
- [ ] 11. `saveStudents` and `loadStudents`
- [ ] 12. Decide in `main` when to load and when to save
      → test: add, update and delete, then restart and check everything persisted