#include "../include/course.h"
#include "../include/student.h"

#include <stdio.h>

int AddStudent (int rollNumber, char* name, float CGPA, int numberOfSubjects) {

}

int ModifyStudent (int rollNumber, float CGPA) {

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