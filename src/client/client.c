#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "enum.h"
#include "fifo.h"
#include "struct.h"

#define MAX_RETRIES 3
#define RETRY_DELAY 5

volatile sig_atomic_t flag = 0;

void sigpipe_handler(int signo){
    flag = 1;
}

int fd;

int openFifo(){
    fd = open(FIFO, O_WRONLY|O_NONBLOCK);
    if (fd == -1)
    {
        if (errno == ENOENT || errno == ENXIO)
        {
            fprintf(stderr, "Server is not running. Please start server first.\n");
        }
        else
        {
            perror("open");
        }
        return 1;
    }
    return 0;
}

void closeFifo(){
    close(fd);
}

int writeToFifo(void *data, size_t size)
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

    return 0;
}

int addStudent(int rollNumber, char *name, float CGPA, int numberOfSubjects){
    AddStudentData data;
    data.rollNumber = rollNumber;
    strcpy(data.name, name);
    data.CGPA = CGPA;
    data.numberOfSubjects = numberOfSubjects;
    Operation op = ADD_STUDNET;
    if (writeToFifo(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToFifo(&data, sizeof(AddStudentData)) != 0)
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

    if (writeToFifo(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToFifo(&data, sizeof(ModifyStudentData)) != 0)
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

    if (writeToFifo(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToFifo(&data, sizeof(DeleteStudentData)) != 0)
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

    if (writeToFifo(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToFifo(&data, sizeof(StudentCourseData)) != 0)
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

    if (writeToFifo(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToFifo(&data, sizeof(StudentCourseData)) != 0)
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

    if (writeToFifo(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    if (writeToFifo(&data, sizeof(StudentCourseData)) != 0)
    {
        return -1;
    }

    return 0;
}

int endConnection() {
    Operation op = END_CONNECTION;

    if (writeToFifo(&op, sizeof(Operation)) != 0)
    {
        return -1;
    }

    return 0;
}