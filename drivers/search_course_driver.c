#include <stdio.h>
#include <stdlib.h>

#include "../includes/student.h"
#include "../includes/course.h"

// NOTE: to test SearchCourse functionality, add function definition in course.h temporarily

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
    student1.numberOfSubjects = 3;

    CourseNode* course01 = (CourseNode*) malloc(sizeof(CourseNode));
    CourseNode* course02 = (CourseNode*) malloc(sizeof(CourseNode));
    CourseNode* course03 = (CourseNode*) malloc(sizeof(CourseNode));
    course01->course.courseCode = 101;
    course01->course.marks = 89;
    course02->course.courseCode = 102;
    course02->course.marks = 77;
    course03->course.courseCode = 103;
    course03->course.marks = 69;

    course01->previousCourse = NULL;
    course01->nextCourse = course02;
    course02->previousCourse = course01;
    course02->nextCourse = course03;
    course03->previousCourse = course02;
    course03->nextCourse = NULL;
    student1.courseHead = course01;
    
    Student student2;
    student2.rollNumber = 2;
    student2.name = "Sri";
    student2.CGPA = 9.22;
    student2.numberOfSubjects = 3;

    CourseNode* course11 = (CourseNode*) malloc(sizeof(CourseNode));
    CourseNode* course12 = (CourseNode*) malloc(sizeof(CourseNode));
    CourseNode* course13 = (CourseNode*) malloc(sizeof(CourseNode));
    course11->course.courseCode = 151;
    course11->course.marks = 79;
    course12->course.courseCode = 152;
    course12->course.marks = 87;
    course13->course.courseCode = 153;
    course13->course.marks = 59;

    course11->previousCourse = NULL;
    course11->nextCourse = course12;
    course12->previousCourse = course11;
    course12->nextCourse = course13;
    course13->previousCourse = course12;
    course13->nextCourse = NULL;
    student2.courseHead = course11;

    Student student3;
    student3.rollNumber = 3;
    student3.name = "Sam";
    student3.CGPA = 9.33;
    student3.numberOfSubjects = 3;

    CourseNode* course21 = (CourseNode*) malloc(sizeof(CourseNode));
    CourseNode* course22 = (CourseNode*) malloc(sizeof(CourseNode));
    CourseNode* course23 = (CourseNode*) malloc(sizeof(CourseNode));
    course21->course.courseCode = 201;
    course21->course.marks = 69;
    course22->course.courseCode = 202;
    course22->course.marks = 70;
    course23->course.courseCode = 203;
    course23->course.marks = 94;

    course21->previousCourse = NULL;
    course21->nextCourse = course22;
    course22->previousCourse = course21;
    course22->nextCourse = course23;
    course23->previousCourse = course22;
    course23->nextCourse = NULL;
    student3.courseHead = course21;

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
    CourseNode* search = searchStudentCourse(student1.courseHead, 101);
    if (search != NULL) {
        printf("%d\n", search->course.courseCode);
        printf("%d\n", search->course.marks);
    }

    printf("\n");

    search = searchStudentCourse(student2.courseHead, 154);
    if (search != NULL) {
        printf("%d\n", search->course.courseCode);
        printf("%d\n", search->course.marks);
    }

    printf("\n");
    
    search = searchStudentCourse(student3.courseHead, 202);
    if (search != NULL) {
        printf("%d\n", search->course.courseCode);
        printf("%d\n", search->course.marks);
    }
    
    printf("\n");

    search = searchStudentCourse(student2.courseHead, 153);
    if (search != NULL) {
        printf("%d\n", search->course.courseCode);
        printf("%d\n", search->course.marks);
    }

    free(studentHead->nextStudent->nextStudent);
    free(studentHead->nextStudent);
    free(studentHead);

    return 0;
}