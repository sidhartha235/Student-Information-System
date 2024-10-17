#ifndef COURSES
#define COURSES

#include "enum.h"

typedef struct Course {
    int courseCode;
    int marks;
} Course;

typedef struct CourseNode {
    Course course;
    struct CourseNode* nextCourse;
    struct CourseNode* previousCourse;
} CourseNode;

Response addStudentCourse(int rollNumber, int courseCode, int marks);
Response modifyStudentCourse(int rollNumber, int courseCode, int marks);
Response deleteStudentCourse(int rollNumber, int courseCode);

#endif