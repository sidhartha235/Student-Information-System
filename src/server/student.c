#include "student.h"
#include "writer.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

StudentNode *studentHead = NULL;
char logMessage[200];
pthread_mutex_t mutex;

int addStudent(int rollNumber, char *name, float CGPA, int numberOfSubjects)
{
    StudentNode *newStudent = searchStudent(rollNumber);
    int error_num;

    if (newStudent != NULL)
    {
        fprintf(stderr, "Error in AddStudent: Student already exists with Roll Number (%d)\n", rollNumber);
        sprintf(logMessage, "Error in AddStudent: Student already exists with Roll Number (%d)\n", rollNumber);
        // appendToFile(logMessage, "logs.txt", 1);
        return 0;
    }
    else
    {
        newStudent = (StudentNode *)malloc(sizeof(StudentNode));
        if (newStudent == NULL)
        {
            fprintf(stderr, "Failed to allocate memory while adding new student!\n");
            exit(1);
        }

        newStudent->student.rollNumber = rollNumber;
        newStudent->student.name = (char *)malloc(strlen(name) + 1);
        if (newStudent->student.name == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        strcpy(newStudent->student.name,name);
        newStudent->student.CGPA = CGPA;
        newStudent->student.numberOfSubjects = 0;
        newStudent->student.courseHead = NULL;

        newStudent->nextStudent = NULL;
        newStudent->previousStudent = NULL;

        // acquire mutex lock
        if ((error_num = pthread_mutex_lock(&mutex)) != 0) {
            perror("pthread_mutex_lock");
            exit(3);
        }

        if (studentHead != NULL)
        {
            newStudent->nextStudent = studentHead;
            studentHead->previousStudent = newStudent;
        }
        studentHead = newStudent;
        
        // release mutex lock
        if ((error_num = pthread_mutex_unlock(&mutex)) != 0) {
            perror("pthread_mutex_unlock");
            exit(3);
        }

        sprintf(logMessage, "Success: Student Added -> Roll Number - %d\n", rollNumber);
        // appendToFile(logMessage, "logs.txt", 1);
        return 1;
    }
}

int modifyStudent(int rollNumber, float CGPA)
{
    StudentNode *modifyStudent = searchStudent(rollNumber);
    int error_num;

    if (modifyStudent == NULL)
    {
        fprintf(stderr, "Error in ModifyStudent: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        sprintf(logMessage, "Error in ModifyStudent: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        // appendToFile(logMessage, "logs.txt", 1);
        return 0;
    }
    else
    {
        // acquire mutex lock
        if ((error_num = pthread_mutex_lock(&mutex)) != 0) {
            perror("pthread_mutex_lock");
            exit(3);
        }
        
        modifyStudent->student.CGPA = CGPA;
        
        // release mutex lock
        if ((error_num = pthread_mutex_unlock(&mutex)) != 0) {
            perror("pthread_mutex_unlock");
            exit(3);
        }

        sprintf(logMessage, "Success: Student Modified -> Roll Number - %d\n", rollNumber);
        // appendToFile(logMessage, "logs.txt", 1);
        return 1;
    }
}

int deleteStudent(int rollNumber)
{
    StudentNode *deleteStudent = searchStudent(rollNumber);
    int error_num;

    if (deleteStudent == NULL)
    {
        fprintf(stderr, "Error in DeleteStudent: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        sprintf(logMessage, "Error in DeleteStudent: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        // appendToFile(logMessage, "logs.txt", 1);
        return 0;
    }
    else
    {
        // acquire mutex lock
        if ((error_num = pthread_mutex_lock(&mutex)) != 0) {
            perror("pthread_mutex_lock");
            exit(3);
        }
        
        if (deleteStudent->previousStudent == NULL)
        {
            studentHead = deleteStudent->nextStudent;
            if (studentHead != NULL)
            {
                studentHead->previousStudent = NULL;
            }
        }
        else
        {
            deleteStudent->previousStudent->nextStudent = deleteStudent->nextStudent;
        }

        if (deleteStudent->nextStudent != NULL)
        {
            deleteStudent->nextStudent->previousStudent = deleteStudent->previousStudent;
        }

        // release mutex lock
        if ((error_num = pthread_mutex_unlock(&mutex)) != 0) {
            perror("pthread_mutex_unlock");
            exit(3);
        }

        free(deleteStudent);
        sprintf(logMessage, "Success: Student Deleted -> Roll Number - %d\n", rollNumber);
        // appendToFile(logMessage, "logs.txt", 1);
        return 1;
    }
}

StudentNode *searchStudent(int rollNumber)
{
    StudentNode *temporaryStudent = studentHead;
    while (temporaryStudent != NULL)
    {
        if (temporaryStudent->student.rollNumber == rollNumber)
        {
            return temporaryStudent;
        }
        temporaryStudent = temporaryStudent->nextStudent;
    }
    return NULL;
}