#include "../includes/course.h"
#include "../includes/student.h"

#include <stdio.h>
#include <stdlib.h>

int addStudent (int rollNumber, char* name, float CGPA, int numberOfSubjects) {
    StudentNode* newStudent = searchStudent(rollNumber);
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

int modifyStudent (int rollNumber, float CGPA) {
    StudentNode* modifyStudent = searchStudent(rollNumber);
    if (modifyStudent == NULL) {
        printf("Modify: Student %d does not exist.\n", rollNumber); // change to file logs later
        return 0;
    } else {
        modifyStudent->student.CGPA = CGPA;

        printf("Success: %d modified.\n", rollNumber); // change to file logs later
        return 1;
    }
}

int deleteStudent (int rollNumber) {
    StudentNode* deleteStudent = searchStudent(rollNumber);
    if (deleteStudent == NULL) {
        printf("Delete: Student %d does not exist.\n", rollNumber); // change to file logs later
        return 0;
    } else {
        if (deleteStudent->previousStudent == NULL) {
            if (deleteStudent->nextStudent == NULL) {
                free(deleteStudent);
                free(studentHead);
                studentHead = NULL;
            } else {
                studentHead = deleteStudent->nextStudent;
                studentHead->previousStudent = NULL;
                free(deleteStudent);
            }
        } else if (deleteStudent->nextStudent == NULL) {
            deleteStudent->previousStudent->nextStudent = NULL;
            free(deleteStudent);
        } else {
            deleteStudent->previousStudent->nextStudent = deleteStudent->nextStudent;
            deleteStudent->nextStudent->previousStudent = deleteStudent->previousStudent;
            free(deleteStudent);
        }

        printf("Success: %d deleted.\n", rollNumber); // change to file logs later
        return 1;
    }
}

StudentNode* searchStudent (int rollNumber) {
    StudentNode* temporaryStudent = studentHead;
    while (temporaryStudent != NULL) {
        if (temporaryStudent->student.rollNumber == rollNumber) {
            return temporaryStudent;
        }
        temporaryStudent = temporaryStudent->nextStudent;
    }
    return NULL;
}