#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "enum.h"
#include "fifo.h"
#include "struct.h"

#include "server.h"
#include "student.h"
#include "course.h"
#include "writer.h"

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void makeFifo() {
    if ((mkfifo (FIFO, FILE_MODE) < 0) && (errno != EEXIST)) {
        fprintf(stderr, "Cannot create %s\n", FIFO);
        exit(1);
    }
    printf("FIFO created successfully!\n");
}

int openFifo() {
    int readfd;
    if ((readfd = open(FIFO, O_RDONLY, 0)) < 0) {
        fprintf(stderr, "Error opening FIFO %s(%d)\n", FIFO, errno);
        exit(3);
    }
    return readfd;
}

void readFromFifo() {
    ssize_t read_bytes;
    int fd = openFifo();

    while (1) {
        Operation operation;
        void *data = NULL;
        read_bytes = read(fd, &operation, sizeof(operation));

        if (read_bytes < 0) {
            fprintf(stderr, "Error in reading from FIFO!\n");
            close(fd);
            exit(1);
        } else if (read_bytes == 0) {
            continue;
        } else {
            switch (operation) {
                case ADD_STUDNET:
                    data = (AddStudentData *) malloc(sizeof(AddStudentData));
                    if (data == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        exit(1);
                    }
                    if ((read_bytes = read(fd, data, sizeof(AddStudentData))) < 0) {
                        fprintf(stderr, "Error in reading from FIFO!\n");
                        close(fd);
                        exit(1);
                    }
                    extractData(operation, data);
                    break;
                case MODIFY_STUDENT:
                    data = (ModifyStudentData *) malloc(sizeof(ModifyStudentData));
                    if (data == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        exit(1);
                    }
                    if ((read_bytes = read(fd, data, sizeof(ModifyStudentData))) < 0) {
                        fprintf(stderr, "Error in reading from FIFO!\n");
                        close(fd);
                        exit(1);
                    }
                    extractData(operation, data);
                    break;
                case DELETE_STUDENT:
                    data = (DeleteStudentData *) malloc(sizeof(DeleteStudentData));
                    if (data == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        exit(1);
                    }
                    if ((read_bytes = read(fd, data, sizeof(DeleteStudentData))) < 0) {
                        fprintf(stderr, "Error in reading from FIFO!\n");
                        close(fd);
                        exit(1);
                    }
                    extractData(operation, data);
                    break;
                case ADD_STUDENT_COURSE:
                case MODIFY_STUDENT_COURSE:
                case DELETE_STUDENT_COURSE:
                    data = (StudentCourseData *) malloc(sizeof(StudentCourseData));
                    if (data == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        exit(1);
                    }
                    if ((read_bytes = read(fd, data, sizeof(StudentCourseData))) < 0) {
                        fprintf(stderr, "Error in reading from FIFO!\n");
                        close(fd);
                        exit(1);
                    }
                    extractData(operation, data);
                    break;
                case END_CONNECTION:
                    char *outputFile = "2108_2119.out";
                    initWrite(outputFile);
                    break;
                default:
                    fprintf(stderr, "Unknown operation!\n");
                    break;
            }
        }

        free(data);
    }

    close(fd);
}

void extractData(Operation operation, void *data) {
    switch (operation) {
        case ADD_STUDNET:
            AddStudentData *addStudentData = (AddStudentData *) data;
            // printf("%s\n", addStudentData->name);
            addStudent(addStudentData->rollNumber,
                       addStudentData->name,
                       addStudentData->CGPA,
                       addStudentData->numberOfSubjects);
            break;

        case MODIFY_STUDENT:
            ModifyStudentData *modifyStudentData = (ModifyStudentData *) data;
            modifyStudent(modifyStudentData->rollNumber,
                          modifyStudentData->CGPA);
            break;

        case DELETE_STUDENT:
            DeleteStudentData *deleteStudentData = (DeleteStudentData *) data;
            deleteStudent(deleteStudentData->rollNumber);
            break;

        case ADD_STUDENT_COURSE:
            StudentCourseData *addCourseData = (StudentCourseData *) data;
            addStudentCourse(addCourseData->rollNumber,
                             addCourseData->courseCode,
                             addCourseData->marks);
            break;

        case MODIFY_STUDENT_COURSE:
            StudentCourseData *modifyCourseData = (StudentCourseData *) data;
            modifyStudentCourse(modifyCourseData->rollNumber,
                                modifyCourseData->courseCode,
                                modifyCourseData->marks);
            break;

        case DELETE_STUDENT_COURSE:
            StudentCourseData *deleteCourseData = (StudentCourseData *) data;
            deleteStudentCourse(deleteCourseData->rollNumber,
                                deleteCourseData->courseCode);
            break;

        default:
            fprintf(stderr, "Unknown operation!\n");
            break;
    }
}