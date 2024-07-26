#include <stdio.h>
#include <stdlib.h>

#include "../include/student.h"

StudentNode* studentHead = NULL;

int main () {
    studentHead = (StudentNode*) malloc(sizeof(StudentNode));
    if (studentHead == NULL) {
        printf("Failed to allocate memory for student 1!\n");
        exit(1);
    }

    Student student1;
    student1.rollNumber = 1;
    student1.name = "Sid";
    student1.CGPA = 9.11;
    student1.numberOfSubjects = 5;
    student1.courseHead = NULL;
    
    Student student2;
    student2.rollNumber = 2;
    student2.name = "Srikar";
    student2.CGPA = 9.22;
    student2.numberOfSubjects = 6;
    student2.courseHead = NULL;

    Student student3;
    student3.rollNumber = 3;
    student3.name = "Akash";
    student3.CGPA = 9.33;
    student3.numberOfSubjects = 5;
    student3.courseHead = NULL;

    // one
    studentHead->student = student1;
    studentHead->nextStudent = (StudentNode*) malloc(sizeof(StudentNode));
    studentHead->previousStudent = NULL;

    if (studentHead->nextStudent == NULL) {
        printf("Failed to allocate memory for student 2!\n");
        free(studentHead);
        exit(1);
    }
    
    // two
    studentHead->nextStudent->student = student2;
    studentHead->nextStudent->nextStudent = (StudentNode*) malloc(sizeof(StudentNode));
    studentHead->nextStudent->previousStudent = studentHead;

    if (studentHead->nextStudent->nextStudent == NULL) {
        printf("Failed to allocate memory for student 3!\n");
        free(studentHead->nextStudent);
        free(studentHead);
        exit(1);
    }

    // three
    studentHead->nextStudent->nextStudent->student = student3;
    studentHead->nextStudent->nextStudent->nextStudent = NULL;
    studentHead->nextStudent->nextStudent->previousStudent = studentHead->nextStudent;

    // tests
    StudentNode* search = SearchStudent(1);
    if (search == NULL) {
        printf("Student does not exist!\n");
    } else {
        printf("%s\n", search->student.name);
        printf("Student exists!\n");
    }

    printf("\n");

    search = SearchStudent(2);
    if (search == NULL) {
        printf("Student does not exist!\n");
    } else {
        printf("%s\n", search->student.name);
        printf("%d\n", search->student.rollNumber);
        printf("%.2f\n", search->student.CGPA);
        printf("%d\n", search->student.numberOfSubjects);
        printf("Student exists!\n");
    }

    printf("\n");
    
    search = SearchStudent(3);
    if (search == NULL) {
        printf("Student does not exist!\n");
    } else {
        printf("%s\n", search->student.name);
        printf("Student exists!\n");
    }
    
    printf("\n");

    search = SearchStudent(4);
    if (search == NULL) {
        printf("Student does not exist!\n");
    } else {
        printf("%s\n", search->student.name);
        printf("Student exists!\n");
    }

    free(studentHead->nextStudent->nextStudent);
    free(studentHead->nextStudent);
    free(studentHead);

    return 0;
}