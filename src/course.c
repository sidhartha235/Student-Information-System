#include "../includes/course.h"
#include "../includes/student.h"

#include <stdio.h>
#include <stdlib.h>

CourseNode* searchStudentCourse(CourseNode* courseHead, int courseCode);

int addStudentCourse (int rollNumber, int courseCode, int marks) {
    StudentNode* studentNode = searchStudent(rollNumber);
    if (studentNode == NULL) {
        printf("Add Course: Student %d does not exist.\n", rollNumber); // change to file logs later
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
            }
            studentNode->student.courseHead = newCourse;

            printf("Success: %d added for %d.\n", courseCode, rollNumber);
            return 1;
        }
    }
}

int modifyStudentCourse (int rollNumber, int courseCode, int marks) {
    StudentNode* studentNode = searchStudent(rollNumber);
    if (studentNode == NULL) {
        printf("Modify Course: Student %d does not exist.\n", rollNumber); // change to file logs later
        return 0;
    } else {
        CourseNode* modifyCourse = searchStudentCourse(studentNode->student.courseHead, courseCode);
        if (modifyCourse == NULL) {
            printf("Modify: Course %d does not exist!\n", courseCode); //change to file logs later
            return 0;
        } else {
            modifyCourse->course.marks = marks;

            printf("Success: Course %d modified!\n", courseCode);
            return 1;
        }
    }
}

int deleteStudentCourse (int rollNumber, int courseCode) {
    StudentNode* studentNode = searchStudent(rollNumber);
    if (studentNode == NULL) {
        printf("Delete Course: Student %d does not exist.\n", rollNumber); // change to file logs later
        return 0;
    } else {
        CourseNode* deleteCourse = searchStudentCourse(studentNode->student.courseHead, courseCode);
        if (deleteCourse == NULL) {
            printf("Delete: Course %d does not exist!\n", courseCode); // change to file logs later
            return 0;
        } else {
            if (deleteCourse->previousCourse == NULL) {
                studentNode->student.courseHead = deleteCourse->nextCourse;
                if (studentNode->student.courseHead != NULL) {
                    studentNode->student.courseHead->previousCourse = NULL;
                }
            } else {
                deleteCourse->previousCourse->nextCourse = deleteCourse->nextCourse;
            }

            if (deleteCourse->nextCourse != NULL) {
                deleteCourse->nextCourse->previousCourse = deleteCourse->previousCourse;
            }

            free(deleteCourse);
            printf("Success: Course %d deleted.\n", courseCode); // change to file logs later
            return 1;
        }
    }
}

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