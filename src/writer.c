#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "writer.h"
#include "student.h"
#include "course.h"

char buffer[200];

void writeStudent(StudentNode *studentNode, char *fileName);
void writeCourse(CourseNode *courseNode, char *fileName);

int appendToFile(char *line, char *fileName)
{
    char path[100];
    char *directory = "output/";

    strcpy(path, directory);
    strcat(path, fileName);

    FILE *filePointer;
    static int firstWrite = 0;
    if (strcmp(fileName, "08_19.output") == 0 && firstWrite == 0)
    {
        filePointer = fopen(path, "w");
        firstWrite = 1;
    }
    else
    {
        filePointer = fopen(path, "a");
    }

    if (filePointer == NULL)
    {
        printf("Failed to open the file: %s\n", path);
        return 0;
    }

    if (fprintf(filePointer, "%s\n", line) < 0)
    {
        printf("Failed to write to the file: %s\n", path);
        fclose(filePointer);
        return 0;
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