#include <stdio.h>
#include <stdlib.h>

#include "../includes/student.h"
#include "../includes/course.h"

StudentNode* studentHead = NULL;

int main () {
    addStudent(1, "Sid", 9.11, 5);
    addStudentCourse(2, 101, 98);
    addStudentCourse(2, 102, 78);
    addStudent(2, "Sri", 9.22, 6);
    addStudentCourse(3, 205, 39);
    addStudent(3, "Sam", 9.33, 4);
    addStudentCourse(3, 205, 39);
    addStudentCourse(2, 101, 98);
    addStudent(3, "Max", 9.44, 4);

    addStudentCourse(1, 101, 88);
    addStudentCourse(1, 102, 81);
    addStudentCourse(2, 101, 98);
    addStudentCourse(2, 102, 78);
    addStudentCourse(1, 103, 68);
    addStudentCourse(3, 103, 66);
    addStudentCourse(3, 105, 96);
    addStudentCourse(1, 201, 98);
    addStudentCourse(1, 203, 89);
    addStudentCourse(2, 202, 18);
    addStudentCourse(3, 153, 99);
    addStudentCourse(3, 205, 39);
    addStudentCourse(2, 302, 58);
    addStudentCourse(2, 352, 78);
    addStudentCourse(2, 152, 98);

    // delete
    deleteStudentCourse(1, 103);
    deleteStudentCourse(5, 103);
    deleteStudentCourse(3, 205);
    deleteStudentCourse(3, 105);
    deleteStudentCourse(1, 109);
    deleteStudentCourse(2, 352);
    deleteStudentCourse(1, 203);

    StudentNode* studentNode = studentHead;
    while (studentNode != NULL) {
        printf("Name: %s\n", studentNode->student.name);
        printf("Roll: %d\n", studentNode->student.rollNumber);
        printf("CGPA: %.2f\n", studentNode->student.CGPA);
        printf("NofS: %d\n", studentNode->student.numberOfSubjects);
        CourseNode* courseNode = studentNode->student.courseHead;
        while (courseNode != NULL) {
            printf("Code: %d\n", courseNode->course.courseCode);
            printf("Mark: %d\n", courseNode->course.marks);
            courseNode = courseNode->nextCourse;
        }
        studentNode = studentNode->nextStudent;
        printf("\n");
    }

    studentNode = studentHead;
    while (studentNode != NULL) {
        studentNode = studentHead;
        studentHead = studentHead->nextStudent;
        CourseNode* courseNode = studentNode->student.courseHead;
        while (courseNode != NULL) {
            courseNode = studentNode->student.courseHead;
            studentNode->student.courseHead = studentNode->student.courseHead->nextCourse;
            free(courseNode);
        }
        free(studentNode);
    }

    return 0;
}