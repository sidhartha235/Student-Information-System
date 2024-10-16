#include "course.h"
#include "student.h"
#include "writer.h"

#include <stdio.h>
#include <stdlib.h>

CourseNode *searchStudentCourse(CourseNode *courseHead, int courseCode);
extern char logMessage[200];

int addStudentCourse(int rollNumber, int courseCode, int marks)
{
    StudentNode *studentNode = searchStudent(rollNumber);
    int error_num;

    if (studentNode == NULL)
    {
        fprintf(stderr, "Error in AddCourse: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        sprintf(logMessage, "Error in AddCourse: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        // if ((filePointer = fopen(fileName, "a")) == NULL) {
        //     fprintf(stderr, "Failed to open the file: %s\n", fileName);
        //     exit(1);
        // }
        // appendToFile(logMessage, "logs.txt", 1);
        return 0;
    }
    else
    {
        CourseNode *newCourse = searchStudentCourse(studentNode->student.courseHead, courseCode);
        if (newCourse != NULL)
        {
            fprintf(stderr, "Error in AddCourse: Course (%d) already exists for Roll Number (%d)\n", courseCode, rollNumber);
            sprintf(logMessage, "Error in AddCourse: Course (%d) already exists for Roll Number (%d)\n", courseCode, rollNumber);
            // appendToFile(logMessage, "logs.txt", 1);
            return 0;
        }
        else
        {
            newCourse = (CourseNode *)malloc(sizeof(CourseNode));
            if (newCourse == NULL)
            {
                fprintf(stderr, "Failed to allocate memory while adding new course!\n");
                exit(1);
            }

            newCourse->course.courseCode = courseCode;
            newCourse->course.marks = marks;

            newCourse->nextCourse = NULL;
            newCourse->previousCourse = NULL;
            
            // acquire mutex lock
            if ((error_num = pthread_mutex_lock(&mutex)) != 0) {
                perror("pthread_mutex_lock");
                exit(3);
            }

            studentNode->student.numberOfSubjects++;

            if (studentNode->student.courseHead != NULL)
            {
                newCourse->nextCourse = studentNode->student.courseHead;
                studentNode->student.courseHead->previousCourse = newCourse;
            }
            studentNode->student.courseHead = newCourse;
            
            // release mutex lock
            if ((error_num = pthread_mutex_unlock(&mutex)) != 0) {
                perror("pthread_mutex_unlock");
                exit(3);
            }

            sprintf(logMessage, "Success: Course Added -> Roll Number - %d -- Course Code - %d\n", rollNumber, courseCode);
            // appendToFile(logMessage, "logs.txt", 1);
            return 1;
        }
    }
}

int modifyStudentCourse(int rollNumber, int courseCode, int marks)
{
    StudentNode *studentNode = searchStudent(rollNumber);
    int error_num;

    if (studentNode == NULL)
    {
        fprintf(stderr, "Error in ModifyCourse: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        sprintf(logMessage, "Error in ModifyCourse: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        // appendToFile(logMessage, "logs.txt", 1);
        return 0;
    }
    else
    {
        CourseNode *modifyCourse = searchStudentCourse(studentNode->student.courseHead, courseCode);
        if (modifyCourse == NULL)
        {
            fprintf(stderr, "Error in ModifyCourse: Course (%d) does NOT exist for Roll Number (%d)\n", courseCode, rollNumber);
            sprintf(logMessage, "Error in ModifyCourse: Course (%d) does NOT exist for Roll Number (%d)\n", courseCode, rollNumber);
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

            modifyCourse->course.marks = marks;

            // release mutex lock
            if ((error_num = pthread_mutex_unlock(&mutex)) != 0) {
                perror("pthread_mutex_unlock");
                exit(3);
            }

            sprintf(logMessage, "Success: Course Modified -> Roll Number - %d -- Course Code - %d\n", rollNumber, courseCode);
            // appendToFile(logMessage, "logs.txt", 1);
            return 1;
        }
    }
}

int deleteStudentCourse(int rollNumber, int courseCode)
{
    StudentNode *studentNode = searchStudent(rollNumber);
    int error_num;
    
    if (studentNode == NULL)
    {
        fprintf(stderr, "Error in DeleteCourse: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        sprintf(logMessage, "Error in DeleteCourse: Student does NOT exist with Roll Number (%d)\n", rollNumber);
        // appendToFile(logMessage, "logs.txt", 1);
        return 0;
    }
    else
    {
        CourseNode *deleteCourse = searchStudentCourse(studentNode->student.courseHead, courseCode);
        if (deleteCourse == NULL)
        {
            fprintf(stderr, "Error in DeleteCourse: Course (%d) does NOT exist for Roll Number (%d)\n", courseCode, rollNumber);
            sprintf(logMessage, "Error in DeleteCourse: Course (%d) does NOT exist for Roll Number (%d)\n", courseCode, rollNumber);
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

            if (deleteCourse->previousCourse == NULL)
            {
                studentNode->student.courseHead = deleteCourse->nextCourse;
                if (studentNode->student.courseHead != NULL)
                {
                    studentNode->student.courseHead->previousCourse = NULL;
                }
            }
            else
            {
                deleteCourse->previousCourse->nextCourse = deleteCourse->nextCourse;
            }

            if (deleteCourse->nextCourse != NULL)
            {
                deleteCourse->nextCourse->previousCourse = deleteCourse->previousCourse;
            }

            studentNode->student.numberOfSubjects--;

            // release mutex lock
            if ((error_num = pthread_mutex_unlock(&mutex)) != 0) {
                perror("pthread_mutex_unlock");
                exit(3);
            }

            free(deleteCourse);
            sprintf(logMessage, "Success: Course Deleted -> Roll Number - %d -- Course Code - %d\n", rollNumber, courseCode);
            // appendToFile(logMessage, "logs.txt", 1);
            return 1;
        }
    }
}

CourseNode *searchStudentCourse(CourseNode *courseHead, int courseCode)
{
    CourseNode *temporaryCourse = courseHead;
    while (temporaryCourse != NULL)
    {
        if (temporaryCourse->course.courseCode == courseCode)
        {
            return temporaryCourse;
        }
        temporaryCourse = temporaryCourse->nextCourse;
    }
    return NULL;
}