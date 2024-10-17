#ifndef STUDENT_INFO
#define STUDENT_INFO

#include "course.h"

#include <pthread.h>

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

extern pthread_mutex_t mutex;

Response addStudent(int rollNumber, char *name, float CGPA, int numberOfSubjects);
Response modifyStudent(int rollNumber, float CGPA);
Response deleteStudent(int rollNumber);
StudentNode *searchStudent(int rollNumber);

#endif