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

int AddStudentCourse(int rollNumber, int courseCode, int marks);

int ModifyStudentCourse(int rollNumber, int courseCode, int marks);

int DeleteStudentCourse(int rollNumber, int courseCode);

#endif