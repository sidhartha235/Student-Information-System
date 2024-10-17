#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

#include "enum.h"
#include "struct.h"

#include "server.h"
#include "student.h"
#include "course.h"
#include "writer.h"

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

static void *handleClient(void *connfd);

int initializeServer(uint16_t serv_port) {
    int listenfd;
    struct sockaddr_in servaddr;
    socklen_t servlen = sizeof(servaddr);
    int optval = 1;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("listenfd");
        exit(2);
    }

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("setsockopt");
        exit(2);
    }

    memset(&servaddr, 0, servlen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(serv_port);

    if (bind(listenfd, (struct sockaddr *) &servaddr, servlen) == -1) {
        perror("bind");
        exit(2);
    }

    if (listen(listenfd, 5) == -1) {
        perror("listen");
        exit(2);
    }

    return listenfd;
}

void stopServer(int listenfd) {
    if (close(listenfd) == -1) {
        perror("close");
        exit(1);
    }
    printf("Server is stopped!\n");
    exit(0);
}

void runServer(int listenfd) {
    int *connfd_ptr;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    
    pthread_t tid;
    int error_num;

    char strptr[INET_ADDRSTRLEN];

    for ( ; ; ) {
        if ((connfd_ptr = malloc(sizeof(int))) == NULL) {
            perror("malloc");
            exit(1);
        }

        if ((*connfd_ptr = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) == -1) {
            perror("accept");
            exit(2);
        }

        printf("\nConnection from client %s:%d\n", \
                inet_ntop(AF_INET, &cliaddr.sin_addr, strptr, INET_ADDRSTRLEN), \
                ntohs(cliaddr.sin_port));

        if ((error_num = pthread_create(&tid, NULL, &handleClient, connfd_ptr)) != 0) {
            fprintf(stderr, "Error in pthread_create\n");
            printf("Error Message: %s\n", strerror(error_num));
            exit(3);
        }
    }
}

static void *handleClient(void *arg) {
    int connfd, error_num;
    char *outputFile;

    connfd = *((int *) arg);
    free(arg);

    if ((error_num = pthread_detach(pthread_self())) != 0) {
        fprintf(stderr, "Error in pthread_detach\n");
        printf("Error Message: %s\n", strerror(error_num));
        exit(3);
    }

    printf("My Thread ID = %ld\n", pthread_self());
    printf("Connection fd = %d\n", connfd);
    updateDB(connfd);

    outputFile = "2108_2119.out";
    initWrite(outputFile);

    if (close(connfd) == -1) { 
        perror("connfd");
        exit(1);
    }

    pthread_exit(NULL);
}

void updateDB(int connfd) {
    Operation operation;
    void *data;
    ssize_t read_bytes, write_bytes;
    Response response;

    while ((read_bytes = recv(connfd, &operation, sizeof(Operation), MSG_WAITALL)) != 0) {
        if (read_bytes == -1) {
            if (errno == EINTR) {
                read_bytes = 0;
                continue;
            }
            perror("recv");
            exit(4);
        }

        response = -1;

        switch (operation) {
            case ADD_STUDNET:
                data = (AddStudentData *) malloc(sizeof(AddStudentData));
                if (data == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }
                if ((read_bytes = recv(connfd, data, sizeof(AddStudentData), MSG_WAITALL)) == -1) {
                    perror("recv");
                    exit(4);
                }
                response = performOperationAndGetResponse(operation, data);
                break;

            case MODIFY_STUDENT:
                data = (ModifyStudentData *) malloc(sizeof(ModifyStudentData));
                if (data == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }
                if ((read_bytes = recv(connfd, data, sizeof(ModifyStudentData), MSG_WAITALL)) == -1) {
                    perror("recv");
                    exit(4);
                }
                response = performOperationAndGetResponse(operation, data);
                break;

            case DELETE_STUDENT:
                data = (DeleteStudentData *) malloc(sizeof(DeleteStudentData));
                if (data == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }
                if ((read_bytes = recv(connfd, data, sizeof(DeleteStudentData), MSG_WAITALL)) == -1) {
                    perror("recv");
                    exit(4);
                }
                response = performOperationAndGetResponse(operation, data);
                break;

            case ADD_STUDENT_COURSE:

            case MODIFY_STUDENT_COURSE:

            case DELETE_STUDENT_COURSE:
                data = (StudentCourseData *) malloc(sizeof(StudentCourseData));
                if (data == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }
                if ((read_bytes = recv(connfd, data, sizeof(StudentCourseData), MSG_WAITALL)) == -1) {
                    perror("recv");
                    exit(4);
                }
                response = performOperationAndGetResponse(operation, data);
                break;

            default:
                fprintf(stderr, "Unknown operation!\n");
                break;
        }


        if ((write_bytes = send(connfd, &response, sizeof(Response), 0)) == -1) {
            perror("send");
            exit(4);
        }
        free(data);
    }
}

Response performOperationAndGetResponse(Operation operation, void *data) {
    AddStudentData *addStudentData;
    ModifyStudentData *modifyStudentData;
    DeleteStudentData *deleteStudentData;
    StudentCourseData *courseData;
    Response response = -1;

    switch (operation) {
        case ADD_STUDNET:
            addStudentData = (AddStudentData *) data;
            // printf("%s\n", addStudentData->name);
            response = addStudent(addStudentData->rollNumber,
                                  addStudentData->name,
                                  addStudentData->CGPA,
                                  addStudentData->numberOfSubjects);
            break;

        case MODIFY_STUDENT:
            modifyStudentData = (ModifyStudentData *) data;
            response = modifyStudent(modifyStudentData->rollNumber,
                                     modifyStudentData->CGPA);
            break;

        case DELETE_STUDENT:
            deleteStudentData = (DeleteStudentData *) data;
            response = deleteStudent(deleteStudentData->rollNumber);
            break;

        case ADD_STUDENT_COURSE:
            courseData = (StudentCourseData *) data;
            response = addStudentCourse(courseData->rollNumber,
                                        courseData->courseCode,
                                        courseData->marks);
            break;

        case MODIFY_STUDENT_COURSE:
            courseData = (StudentCourseData *) data;
            response = modifyStudentCourse(courseData->rollNumber,
                                           courseData->courseCode,
                                           courseData->marks);
            break;

        case DELETE_STUDENT_COURSE:
            courseData = (StudentCourseData *) data;
            response = deleteStudentCourse(courseData->rollNumber,
                                           courseData->courseCode);
            break;

        default:
            fprintf(stderr, "Unknown operation!\n");
            break;
    }

    return response;
}