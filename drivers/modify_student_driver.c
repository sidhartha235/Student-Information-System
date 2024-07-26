#include <stdio.h>
#include <stdlib.h>

#include "../includes/student.h"

StudentNode* studentHead = NULL;

int main () {
    addStudent(1, "Sid", 9.11, 5);
    addStudent(2, "Sri", 9.22, 6);
    addStudent(3, "Sam", 9.33, 4);
    modifyStudent(4, 9.223);
    addStudent(3, "Max", 9.44, 4);
    addStudent(4, "Max", 9.44, 4);

    modifyStudent(2, 9.991);
    modifyStudent(1, 9.012);

    StudentNode* temp = studentHead;
    while (temp != NULL) {
        printf("Name: %s\n", temp->student.name);
        printf("Roll: %d\n", temp->student.rollNumber);
        printf("CGPA: %.2f\n", temp->student.CGPA);
        printf("NofS: %d\n", temp->student.numberOfSubjects);
        printf("Crss: %p\n\n", temp->student.courseHead);
        temp = temp->nextStudent;
    }

    temp = studentHead;
    while (temp != NULL) {
        temp = studentHead;
        studentHead = studentHead->nextStudent;
        free(temp);
    }

    return 0;
}