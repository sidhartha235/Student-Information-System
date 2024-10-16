#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "enum.h"
#include "struct.h"

#define MAX_RETRIES 3
#define RETRY_DELAY 5

volatile sig_atomic_t flag = 0;

void sigpipe_handler(int signo){
    flag = 1;
}

int fd;

void openConnection(char *serv_addr, int serv_port)
{
    struct sockaddr_in servaddr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serv_port);
    int rv = inet_pton(AF_INET, serv_addr, &servaddr.sin_addr.s_addr);
    if (rv == 0)
    {
        fprintf(stderr, "Invalid Server address\n");
        exit(1);
    }else if (rv < 0 ){
        perror("inet_pton");
        exit(1);
    }
    if (connect(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
}

void closeConnection()
{
    close(fd);
}

void printResponse(Response res)
{
    switch (res)
    {
    case ADD_STUDENT_SUCCESS:
        printf("Student added successfully\n");
        break;
    case ADD_STUDENT_FAILURE:
        printf("Failed to add student\n");
        break;
    case MODIFY_STUDENT_SUCCESS:
        printf("Student modified successfully\n");
        break;
    case MODIFY_STUDENT_FAILURE:
        printf("Failed to modify student\n");
        break;
    case DELETE_STUDENT_SUCCESS:
        printf("Student deleted successfully\n");
        break;
    case DELETE_STUDENT_FAILURE:
        printf("Failed to delete student\n");
        break;
    case ADD_STUDENT_COURSE_SUCCESS:
        printf("Student course added successfully\n");
        break;
    case ADD_STUDENT_COURSE_FAILURE:
        printf("Failed to add student course\n");
        break;
    case MODIFY_STUDENT_COURSE_SUCCESS:
        printf("Student course modified successfully\n");
        break;
    case MODIFY_STUDENT_COURSE_FAILURE:
        printf("Failed to modify student course\n");
        break;
    case DELETE_STUDENT_COURSE_SUCCESS:
        printf("Student course deleted successfully\n");
        break;
    case DELETE_STUDENT_COURSE_FAILURE:
        printf("Failed to delete student course\n");
        break;
    default:
        printf("Invalid response\n");
        break;
    }
}

void readFromSocket(){
    ssize_t read_bytes;
    Response res;
    read_bytes = recv(fd, &res, sizeof(Response), MSG_WAITALL);
    if (read_bytes < 0)
    {
        perror("recv");
        exit(1);
    }else if(read_bytes == 0){
        fprintf(stderr, "Server closed the connection\n");
        exit(1);
    }
    printResponse(res);
}

int writeToSocket(void *data, size_t size)
{
    ssize_t write_bytes;
    int retries = 0;

    if(signal(SIGPIPE, sigpipe_handler) == SIG_ERR){
        perror("signal");
        return -1;
    }

    while (1){
        flag = 0;
        write_bytes = write(fd, data, size);
        if (write_bytes < 0)
        {
            if(errno == EPIPE || flag){
                if(retries < MAX_RETRIES){
                    fprintf(stderr, "SIGPIPE Received.Retrying in %d seconds, Attempt %d/%d.\n", RETRY_DELAY, retries,MAX_RETRIES);
                    retries++;
                    sleep(RETRY_DELAY);
                    continue;
                }else{
                    fprintf(stderr, "Max retries reached. Server either not running or closed the pipe.\n");
                    exit(1);
                }
            }else{
                perror("write");
                exit(1);
            }
        }
        break;
    }
    // readFromSocket();
    return 0;
}

int addStudent(int rollNumber, char *name, float CGPA, int numberOfSubjects){
    AddStudentData data;
    data.rollNumber = rollNumber;
    strcpy(data.name, name);
    data.CGPA = CGPA;
    data.numberOfSubjects = numberOfSubjects;
    Operation op = ADD_STUDNET;
    if (writeToSocket(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToSocket(&data, sizeof(AddStudentData)) != 0)
    {
        return -1;
    }

    return 0;
}

int modifyStudent(int rollNumber, float CGPA)
{
    ModifyStudentData data;
    data.rollNumber = rollNumber;
    data.CGPA = CGPA;

    Operation op = MODIFY_STUDENT;

    if (writeToSocket(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToSocket(&data, sizeof(ModifyStudentData)) != 0)
    {
        return -1;
    }

    return 0;
}

int deleteStudent(int rollNumber)
{
    DeleteStudentData data;
    data.rollNumber = rollNumber;

    Operation op = DELETE_STUDENT;

    if (writeToSocket(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToSocket(&data, sizeof(DeleteStudentData)) != 0)
    {
        return -1;
    }

    return 0;
}

int addStudentCourse(int rollNumber, int courseCode, int marks)
{
    StudentCourseData data;
    data.rollNumber = rollNumber;
    data.courseCode = courseCode;
    data.marks = marks;

    Operation op = ADD_STUDENT_COURSE;

    if (writeToSocket(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToSocket(&data, sizeof(StudentCourseData)) != 0)
    {
        return -1;
    }

    return 0;
}

int modifyStudentCourse(int rollNumber, int courseCode, int marks)
{
    StudentCourseData data;
    data.rollNumber = rollNumber;
    data.courseCode = courseCode;
    data.marks = marks;

    Operation op = MODIFY_STUDENT_COURSE;

    if (writeToSocket(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToSocket(&data, sizeof(StudentCourseData)) != 0)
    {
        return -1;
    }

    return 0;
}

int deleteStudentCourse(int rollNumber, int courseCode)
{
    StudentCourseData data;
    data.rollNumber = rollNumber;
    data.courseCode = courseCode;

    Operation op = DELETE_STUDENT_COURSE;

    if (writeToSocket(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToSocket(&data, sizeof(StudentCourseData)) != 0)
    {
        return -1;
    }

    return 0;
}