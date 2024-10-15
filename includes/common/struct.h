#ifndef STRUCT_H
#define STRUCT_H

#include "enum.h"

#define MAX_NAME 100

typedef struct
{
    int rollNumber;
    char name[MAX_NAME];
    float CGPA;
    int numberOfSubjects;
} AddStudentData;

typedef struct
{
    int rollNumber;
    float CGPA;
} ModifyStudentData;

typedef struct
{
    int rollNumber;
} DeleteStudentData;

typedef struct
{
    int rollNumber;
    int courseCode;
    int marks;
} StudentCourseData;


#endif