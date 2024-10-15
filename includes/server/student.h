#ifndef STUDENT_INFO
#define STUDENT_INFO

#include "course.h"

typedef struct Student
{
    int rollNumber;
    char *name;
    float CGPA;
    int numberOfSubjects;
    CourseNode *courseHead;
} Student;

typedef struct StudentNode
{
    Student student;
    struct StudentNode *nextStudent;
    struct StudentNode *previousStudent;
} StudentNode;

extern StudentNode *studentHead;
extern char logMessage[200];

int addStudent(int rollNumber, char *name, float CGPA, int numberOfSubjects);

int modifyStudent(int rollNumber, float CGPA);

int deleteStudent(int rollNumber);

StudentNode *searchStudent(int rollNumber);

#endif