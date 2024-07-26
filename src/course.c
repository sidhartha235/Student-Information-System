#include "../includes/course.h"
#include "../includes/student.h"

#include <stdio.h>
#include <stdlib.h>

CourseNode* searchStudentCourse (CourseNode* courseHead, int courseCode) {
    CourseNode* temporaryCourse = courseHead;
    while (temporaryCourse != NULL) {
        if (temporaryCourse->course.courseCode == courseCode) {
            return temporaryCourse;
        }
        temporaryCourse = temporaryCourse->nextCourse;
    }
    return NULL;
}

int addStudentCourse (int rollNumber, int courseCode, int marks) {
    StudentNode* studentNode = searchStudent(rollNumber);
    if (studentNode == NULL) {
        printf("Add Course: Student does not exist.\n", rollNumber); // change to file logs later
        return 0;
    } else {
        CourseNode* newCourse = searchStudentCourse(studentNode->student.courseHead, courseCode);
        if (newCourse != NULL) {
            printf("Add: Course %d already exists!\n", courseCode); //change to file logs later
            return 0;
        } else {
            newCourse = (CourseNode*) malloc(sizeof(CourseNode));
            if (newCourse == NULL) {
                printf("Failed to allocate memory while adding new course!\n");
                exit(1);
            }

            newCourse->course.courseCode = courseCode;
            newCourse->course.marks = marks;

            newCourse->nextCourse = NULL;
            newCourse->previousCourse = NULL;

            if (studentNode->student.courseHead != NULL) {
                newCourse->nextCourse = studentNode->student.courseHead;
                studentNode->student.courseHead->previousCourse = newCourse;
                studentNode->student.courseHead = newCourse;
            } else {
                studentNode->student.courseHead = newCourse;
            }

            printf("Success: %d added for %d.\n", courseCode, rollNumber);
            return 1;
        }
    }
}

int modifyStudentCourse (int rollNumber, int courseCode, int marks) {

}

int deleteStudentCourse (int rollNumber, int courseCode) {

}
