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
#define MAX 4096

static void *handleClient(void *connfd);

int initializeServer(uint16_t serv_port) {
    int listenfd;
    struct sockaddr_in servaddr;
    socklen_t servlen = sizeof(servaddr);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("listenfd");
        exit(2);
    }

    memset(&servaddr, 0, servlen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = serv_port;

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
    if (shutdown(listenfd, SHUT_RDWR) == -1) {
        perror("shutdown");
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

    for ( ; ; ) {
        if ((connfd_ptr = malloc(sizeof(int))) == NULL) {
            perror("malloc");
            exit(1);
        }

        if ((*connfd_ptr = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) == -1) {
            perror("accept");
            exit(2);
        }

        printf("Connection from client %s:%d\n", \
                inet_ntop(AF_INET, &cliaddr.sin_addr, NULL, sizeof(cliaddr.sin_addr)), \
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

    connfd = *((int *) arg);
    free(arg);

    if ((error_num = pthread_detach(pthread_self())) != 0) {
        fprintf(stderr, "Error in pthread_detach\n");
        printf("Error Message: %s\n", strerror(error_num));
        exit(3);
    }

    /* handle client */
    printf("I am handling a client..\n");
    printf("My Thread ID = %ld", pthread_self());
    printf("Connection fd = %d\n", connfd);

    if (close(connfd) == -1) {
        perror("close");
        exit(1);
    }

    pthread_exit(NULL);
}
//     while (1) {
//         Operation operation;
//         void *data = NULL;
//         read_bytes = read(fd, &operation, sizeof(operation));

//         if (read_bytes < 0) {
//             fprintf(stderr, "Error in reading from FIFO!\n");
//             close(fd);
//             exit(1);
//         } else if (read_bytes == 0) {
//             continue;
//         } else {
//             switch (operation) {
//                 case ADD_STUDNET:
//                     data = (AddStudentData *) malloc(sizeof(AddStudentData));
//                     if (data == NULL) {
//                         fprintf(stderr, "Memory allocation failed\n");
//                         exit(1);
//                     }
//                     if ((read_bytes = read(fd, data, sizeof(AddStudentData))) < 0) {
//                         fprintf(stderr, "Error in reading from FIFO!\n");
//                         close(fd);
//                         exit(1);
//                     }
//                     extractData(operation, data);
//                     break;
//                 case MODIFY_STUDENT:
//                     data = (ModifyStudentData *) malloc(sizeof(ModifyStudentData));
//                     if (data == NULL) {
//                         fprintf(stderr, "Memory allocation failed\n");
//                         exit(1);
//                     }
//                     if ((read_bytes = read(fd, data, sizeof(ModifyStudentData))) < 0) {
//                         fprintf(stderr, "Error in reading from FIFO!\n");
//                         close(fd);
//                         exit(1);
//                     }
//                     extractData(operation, data);
//                     break;
//                 case DELETE_STUDENT:
//                     data = (DeleteStudentData *) malloc(sizeof(DeleteStudentData));
//                     if (data == NULL) {
//                         fprintf(stderr, "Memory allocation failed\n");
//                         exit(1);
//                     }
//                     if ((read_bytes = read(fd, data, sizeof(DeleteStudentData))) < 0) {
//                         fprintf(stderr, "Error in reading from FIFO!\n");
//                         close(fd);
//                         exit(1);
//                     }
//                     extractData(operation, data);
//                     break;
//                 case ADD_STUDENT_COURSE:
//                 case MODIFY_STUDENT_COURSE:
//                 case DELETE_STUDENT_COURSE:
//                     data = (StudentCourseData *) malloc(sizeof(StudentCourseData));
//                     if (data == NULL) {
//                         fprintf(stderr, "Memory allocation failed\n");
//                         exit(1);
//                     }
//                     if ((read_bytes = read(fd, data, sizeof(StudentCourseData))) < 0) {
//                         fprintf(stderr, "Error in reading from FIFO!\n");
//                         close(fd);
//                         exit(1);
//                     }
//                     extractData(operation, data);
//                     break;
//                 case END_CONNECTION:
//                     char *outputFile = "2108_2119.out";
//                     initWrite(outputFile);
//                     break;
//                 default:
//                     fprintf(stderr, "Unknown operation!\n");
//                     break;
//             }
//         }

//         free(data);
//     }

//     close(fd);
// }

// void extractData(Operation operation, void *data) {
//     switch (operation) {
//         case ADD_STUDNET:
//             AddStudentData *addStudentData = (AddStudentData *) data;
//             // printf("%s\n", addStudentData->name);
//             addStudent(addStudentData->rollNumber,
//                        addStudentData->name,
//                        addStudentData->CGPA,
//                        addStudentData->numberOfSubjects);
//             break;

//         case MODIFY_STUDENT:
//             ModifyStudentData *modifyStudentData = (ModifyStudentData *) data;
//             modifyStudent(modifyStudentData->rollNumber,
//                           modifyStudentData->CGPA);
//             break;

//         case DELETE_STUDENT:
//             DeleteStudentData *deleteStudentData = (DeleteStudentData *) data;
//             deleteStudent(deleteStudentData->rollNumber);
//             break;

//         case ADD_STUDENT_COURSE:
//             StudentCourseData *addCourseData = (StudentCourseData *) data;
//             addStudentCourse(addCourseData->rollNumber,
//                              addCourseData->courseCode,
//                              addCourseData->marks);
//             break;

//         case MODIFY_STUDENT_COURSE:
//             StudentCourseData *modifyCourseData = (StudentCourseData *) data;
//             modifyStudentCourse(modifyCourseData->rollNumber,
//                                 modifyCourseData->courseCode,
//                                 modifyCourseData->marks);
//             break;

//         case DELETE_STUDENT_COURSE:
//             StudentCourseData *deleteCourseData = (StudentCourseData *) data;
//             deleteStudentCourse(deleteCourseData->rollNumber,
//                                 deleteCourseData->courseCode);
//             break;

//         default:
//             fprintf(stderr, "Unknown operation!\n");
//             break;
//     }
// }