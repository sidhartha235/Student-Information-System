#ifndef STUDENT_INFO
#define STUDENT_INFO

#include "../includes/course.h"

typedef struct Student {
    int rollNumber;
    char* name;
    float CGPA;
    int numberOfSubjects;
    CourseNode* courseHead;
} Student;

typedef struct StudentNode {
    Student student;
    struct StudentNode* nextStudent;
    struct StudentNode* previousStudent;
} StudentNode;

extern StudentNode* studentHead;

int AddStudent(int rollNumber, char* name, float CGPA, int numberOfSubjects);

int ModifyStudent(int rollNumber, float CGPA);

int DeleteStudent(int rollNumber);

StudentNode* SearchStudent(int rollNumber);

#endif