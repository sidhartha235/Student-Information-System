#include "../includes/course.h"
#include "../includes/student.h"

#include <stdio.h>
#include <stdlib.h>

int addStudentCourse (int rollNumber, int courseCode, int marks) {

}

int modifyStudentCourse (int rollNumber, int courseCode, int marks) {

}

int deleteStudentCourse (int rollNumber, int courseCode) {

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