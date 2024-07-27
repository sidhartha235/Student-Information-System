#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "course.h"

#define MAX 100

FILE *openFile(char *filename);
void closeFile(FILE *fp);

void initDBInfo(char *line, FILE *filePointer);
void parseAddStudent(char *line);
void parseAddCourse(char *line);
void parseModifyStudent(char *line);
void parseModifyCourse(char *line);
void parseDeleteStudent(char *line);
void parseDeleteCourse(char *line);

void initParse(char *filename)
{
    FILE *fp = openFile(filename);
    char line[MAX];
    char *callType = NULL;

    while (fgets(line, MAX, fp) != NULL)
    {
        if (sscanf(line, " %*c") != EOF)
        {
            char ch = line[0];
            if (ch == '#')
            {
                if(callType != NULL){
                    free(callType);
                }
                int len = strlen(line);
                callType = (char *)malloc(len);
                if (callType == NULL)
                {
                    fprintf(stderr, "Unable to allocate memory");
                    exit(1);
                }
                strncpy(callType, line + 2, len - 3);
                callType[len] = '\0';
            }
            else
            {
                if (strcasecmp(callType, "initial database") == 0)
                {
                    initDBInfo(line, fp);
                }
                else if (strcasecmp(callType, "add student") == 0)
                {
                    parseAddStudent(line);
                }
                else if (strcasecmp(callType, "add course") == 0)
                {
                    parseAddCourse(line);
                }
                else if (strcasecmp(callType, "modify student") == 0)
                {
                    parseModifyStudent(line);
                }
                else if (strcasecmp(callType, "modify course") == 0)
                {
                    parseModifyCourse(line);
                }
                else if (strcasecmp(callType, "delete student") == 0)
                {
                    parseDeleteStudent(line);
                }
                else if (strcasecmp(callType, "delete course") == 0)
                {
                    parseDeleteCourse(line);
                }
                else
                {
                    fprintf(stderr, "Incorrect Input file");
                    exit(1);
                }
            }
        }
    }

    free(callType);
    closeFile(fp);
}

void initDBInfo(char* line,FILE* filePointer){
    int rollNumber;
    char* name = (char*)malloc(MAX);
    float CGPA;
    int numSubjects;
    int result = sscanf(line, "%d, %[^,], %f, %d", &rollNumber, name, &CGPA, &numSubjects);
    addStudent(rollNumber, name, CGPA, numSubjects);
    int index = 0;
    while (index < numSubjects && (line = fgets(line, MAX, filePointer)))
    {
        if (sscanf(line,"%*c") != EOF){
            int courseCode;
            int marks;
            int result = sscanf(line,"%d, %d", &courseCode, &marks);
            addStudentCourse(rollNumber, courseCode, marks);
            index++;
        }
    }
}

void parseAddStudent(char* line){
    int rollNumber;
    char *name = (char *)malloc(MAX);
    float CGPA;
    int numSubjects;
    int result = sscanf(line, "%d, %[^,], %f, %d", &rollNumber, name, &CGPA, &numSubjects);
    addStudent(rollNumber, name, CGPA, numSubjects);
}

void parseAddCourse(char* line){
    int rollNumber;
    int courseCode;
    int marks;
    int result = sscanf(line, "%d, %d, %d", &rollNumber, &courseCode, &marks);
    addStudentCourse(rollNumber, courseCode, marks);
}

void parseModifyStudent(char* line){
    int rollNumber;
    float CGPA;
    int result = sscanf(line,"%d, %f",&rollNumber, &CGPA);
    modifyStudent(rollNumber, CGPA);
}

void parseModifyCourse(char* line){
    int rollNumber;
    int courseCode;
    int marks;
    int result = sscanf(line,"%d, %d, %d", &rollNumber, &courseCode, &marks);
    modifyStudentCourse(rollNumber, courseCode, marks);
}


void parseDeleteStudent(char* line){
    int rollNumber;
    int result = sscanf(line,"%d", &rollNumber);
    deleteStudent(rollNumber);
}

void parseDeleteCourse(char* line){
    int rollNumber;
    int courseCode;
    int result = sscanf(line,"%d, %d", &rollNumber, &courseCode);
    deleteStudentCourse(rollNumber, courseCode);
}

FILE *openFile(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file");
        exit(1);
    }
    return fp;
}

void closeFile(FILE * fp)
{
    fclose(fp);
}