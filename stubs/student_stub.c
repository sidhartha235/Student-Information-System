#include <string.h>
#include <stdio.h>

int addStudent(int rollNumber, char *name, float CGPA, int numberOfSubjects){
    printf("API : %d %s %f %d\n", rollNumber, name, CGPA, numberOfSubjects);
}

int modifyStudent(int rollNumber, float CGPA){
    printf("API: %d %f\n", rollNumber, CGPA);
}

int deleteStudent(int rollNumber){
    printf("API: %d\n", rollNumber);
}

int addCourse(int rollNumber, int courseCode, int marks){
    printf("API: %d %d %d\n", rollNumber, courseCode, marks);
}

int modifyCourse(int rollNumber, int courseCode, int marks){
    printf("API: %d %d %d\n", rollNumber, courseCode, marks);
}

int deleteCourse(int rollNumber, int courseCode){
    printf("API: %d %d\n", rollNumber, courseCode);
}