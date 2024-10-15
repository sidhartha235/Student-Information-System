#ifndef COURSES
#define COURSES

typedef struct Course {
    int courseCode;
    int marks;
} Course;

typedef struct CourseNode {
    Course course;
    struct CourseNode* nextCourse;
    struct CourseNode* previousCourse;
} CourseNode;

int addStudentCourse(int rollNumber, int courseCode, int marks);

int modifyStudentCourse(int rollNumber, int courseCode, int marks);

int deleteStudentCourse(int rollNumber, int courseCode);

#endif