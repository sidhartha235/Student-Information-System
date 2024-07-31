#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "writer.h"
#include "student.h"
#include "course.h"

char buffer[200];

void writeStudent(StudentNode *studentNode, char *fileName);
void writeCourse(CourseNode *courseNode, char *fileName);

int appendToFile(char *line, char *fileName)
{
    char path[100];
    char *directory = "";
    time_t currentTime;
    struct tm *localTime;
    char dateTime[100];

    strcpy(path, directory);
    strcat(path, fileName);

    FILE *filePointer;
    static int firstWrite = 0;
    if (strcmp(fileName, "2108_2119.out") == 0 && firstWrite == 0)
    {
        filePointer = fopen(path, "w");
        firstWrite = 1;
    }
    else
    {
        filePointer = fopen(path, "a");
        if (strcmp(fileName, "logs.txt") == 0)
        {
            currentTime = time(NULL);
            localTime = localtime(&currentTime);
            sprintf(dateTime, "[%02d-%02d-%d %02d:%02d:%02d]\t", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
            strcat(dateTime, line);
            strcpy(line, dateTime);
        }
    }

    if (filePointer == NULL)
    {
        fprintf(stderr, "Failed to open the file: %s\n", path);
        exit(1);
    }

    if (fprintf(filePointer, "%s\n", line) < 0)
    {
        fprintf(stderr, "Failed to write to the file: %s\n", path);
        fclose(filePointer);
        exit(1);
    }

    fclose(filePointer);
    return 1;
}

void initWrite(char *fileName)
{
    StudentNode *studentNode = studentHead;
    while (studentNode->nextStudent != NULL)
    {
        studentNode = studentNode->nextStudent;
    }
    // Now traverse back to start
    while (studentNode != NULL)
    {
        writeStudent(studentNode, fileName);
        studentNode = studentNode->previousStudent;
    }

    printf("Successfully written to the file: output/%s\n", fileName);
}

void writeStudent(StudentNode *studentNode, char *fileName)
{
    int numSubjects = studentNode->student.numberOfSubjects;
    sprintf(buffer, "%d, %s, %.2f, %d", studentNode->student.rollNumber, studentNode->student.name, studentNode->student.CGPA, studentNode->student.numberOfSubjects);
    appendToFile(buffer, fileName);
    CourseNode *courseNode = studentNode->student.courseHead;
    if (courseNode != NULL)
    {
        while (courseNode->nextCourse != NULL)
        {
            courseNode = courseNode->nextCourse;
        }
    }
    while (courseNode != NULL)
    {
        writeCourse(courseNode, fileName);
        courseNode = courseNode->previousCourse;
    }
}

void writeCourse(CourseNode *courseNode, char *fileName)
{
    sprintf(buffer, "%d, %d", courseNode->course.courseCode, courseNode->course.marks);
    appendToFile(buffer, fileName);
}