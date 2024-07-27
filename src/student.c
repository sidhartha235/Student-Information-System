#include "../includes/student.h"
#include "../includes/writer.h"

#include <stdio.h>
#include <stdlib.h>

char logMessage[200];

int addStudent (int rollNumber, char* name, float CGPA, int numberOfSubjects) {
    StudentNode* newStudent = searchStudent(rollNumber);
    if (newStudent != NULL) {
        sprintf(logMessage, "Error in AddStudent: Student already exists with Roll Number (%d)\n", rollNumber);
        appendToFile(logMessage, "logs.txt");
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
        }
        studentHead = newStudent;

        sprintf(logMessage, "Success: Student Added -> Roll Number - %d\n", rollNumber);
        appendToFile(logMessage, "logs.txt");
        return 1;
    }
}

int modifyStudent (int rollNumber, float CGPA) {
    StudentNode* modifyStudent = searchStudent(rollNumber);
    char logMessage[100];
    if (modifyStudent == NULL) {
        sprintf(logMessage, "Error in ModifyStudent: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        appendToFile(logMessage, "logs.txt");
        return 0;
    } else {
        modifyStudent->student.CGPA = CGPA;

        sprintf(logMessage, "Success: Student Modified -> Roll Number - %d\n", rollNumber);
        appendToFile(logMessage, "logs.txt");
        return 1;
    }
}

int deleteStudent (int rollNumber) {
    StudentNode* deleteStudent = searchStudent(rollNumber);
    char logMessage[100];
    if (deleteStudent == NULL) {
        sprintf(logMessage, "Error in DeleteStudent: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        appendToFile(logMessage, "logs.txt");
        return 0;
    } else {
        if (deleteStudent->previousStudent == NULL) {
            studentHead = deleteStudent->nextStudent;
            if (studentHead != NULL) {
                studentHead->previousStudent = NULL;
            }
        } else {
            deleteStudent->previousStudent->nextStudent = deleteStudent->nextStudent;
        }
        
        if (deleteStudent->nextStudent != NULL) {
            deleteStudent->nextStudent->previousStudent = deleteStudent->previousStudent;
        }

        free(deleteStudent);
        sprintf(logMessage, "Success: Student Deleted -> Roll Number - %d\n", rollNumber);
        appendToFile(logMessage, "logs.txt");
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