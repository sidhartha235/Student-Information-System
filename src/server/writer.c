#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "writer.h"
#include "student.h"
#include "course.h"

char buffer[200];

void writeStudent(StudentNode *studentNode, FILE *filePointer);
void writeCourse(CourseNode *courseNode, FILE *filePointer);

int appendToFile(char *line, FILE *filePointer, int is_log)
{
    time_t currentTime;
    struct tm *localTime;
    char dateTime[100];

    if (is_log == 1) {
        currentTime = time(NULL);
        localTime = localtime(&currentTime);
        sprintf(dateTime, "[%02d-%02d-%d %02d:%02d:%02d]\t", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
        strcat(dateTime, line);
        strcpy(line, dateTime);
    }

    if (fprintf(filePointer, "%s\n", line) < 0)
    {
        perror("fprintf");
        exit(1);
    }

    return 1;
}

void initWrite(char *fileName)
{
    // char path[100];
    // char *directory = "";

    // strcpy(path, directory);
    // strcat(path, fileName);
    
    FILE *filePointer;

    if (strcmp(fileName, "2108_2119.out") == 0) {
        filePointer = fopen(fileName, "w");
    } else {
        fprintf(stderr, "Cannot recognize file: %s\n", fileName);
        exit(1);
    }

    if (filePointer == NULL) {
        fprintf(stderr, "Failed to open the file: %s\n", fileName);
        exit(1);
    }

    StudentNode *studentNode = studentHead;
    while (studentNode && studentNode->nextStudent != NULL) {
        studentNode = studentNode->nextStudent;
    }
    // Now traverse back to start
    while (studentNode != NULL) {
        writeStudent(studentNode, filePointer);
        studentNode = studentNode->previousStudent;
    }

    fclose(filePointer);
    printf("Successfully written to the file: %s\n", fileName);
}

void writeStudent(StudentNode *studentNode, FILE *filePointer)
{
    sprintf(buffer, "%d, %s, %.2f, %d", studentNode->student.rollNumber, studentNode->student.name, studentNode->student.CGPA, studentNode->student.numberOfSubjects);
    appendToFile(buffer, filePointer, 0);

    CourseNode *courseNode = studentNode->student.courseHead;
    while (courseNode && courseNode->nextCourse != NULL) {
        courseNode = courseNode->nextCourse;
    }

    while (courseNode != NULL) {
        writeCourse(courseNode, filePointer);
        courseNode = courseNode->previousCourse;
    }
}

void writeCourse(CourseNode *courseNode, FILE *filePointer)
{
    sprintf(buffer, "%d, %d", courseNode->course.courseCode, courseNode->course.marks);
    appendToFile(buffer, filePointer, 0);
}