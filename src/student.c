#include "../includes/course.h"
#include "../includes/student.h"

#include <stdio.h>
#include <stdlib.h>

int AddStudent (int rollNumber, char* name, float CGPA, int numberOfSubjects) {
    StudentNode* newStudent = SearchStudent(rollNumber);
    if (newStudent != NULL) {
        printf("Add: Student %d already exists.\n", rollNumber); // change to file logs later
        return 0;
    } else {
        newStudent = (StudentNode*) malloc(sizeof(StudentNode));
        if (newStudent == NULL) {
            printf("Failed to allocate memory while adding new student!\n");
            exit(1);
        }

        newStudent->student.rollNumber = rollNumber;
        newStudent->student.name = name;
        newStudent->student.CGPA = CGPA;
        newStudent->student.numberOfSubjects = numberOfSubjects;
        newStudent->student.courseHead = NULL;
        
        newStudent->nextStudent = NULL;
        newStudent->previousStudent = NULL;
        
        if (studentHead != NULL) {
            newStudent->nextStudent = studentHead;
            studentHead->previousStudent = newStudent;
            studentHead = newStudent;
        } else {
            studentHead = newStudent;
        }

        printf("Success: %d added.\n", rollNumber); // change to file logs later
        return 1;
    }
}

int ModifyStudent (int rollNumber, float CGPA) {
    StudentNode* modifyStudent = SearchStudent(rollNumber);
    if (modifyStudent == NULL) {
        printf("Modify: Student %d does not exist.\n", rollNumber); // change to file logs later
        return 0;
    } else {
        modifyStudent->student.CGPA = CGPA;

        printf("Success: %d modified.\n", rollNumber); // change to file logs later
        return 1;
    }
}

int DeleteStudent (int rollNumber) {

}

StudentNode* SearchStudent (int rollNumber) {
    StudentNode* temporaryStudent = studentHead;
    while (temporaryStudent != NULL) {
        if (temporaryStudent->student.rollNumber == rollNumber) {
            return temporaryStudent;
        }
        temporaryStudent = temporaryStudent->nextStudent;
    }
    return NULL;
}