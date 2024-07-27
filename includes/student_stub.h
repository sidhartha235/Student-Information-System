#ifndef STUDENT_STUB_H
#define STUDENT_STUB_H

int addStudent(int rollNumber, char *name, float CGPA, int numberOfSubjects);

int modifyStudent(int rollNumber, float CGPA);

int deleteStudent(int rollNumber);

int addCourse(int rollNumber, int courseCode, int marks);

int modifyCourse(int rollNumber, int courseCode, int marks);

int deleteCourse(int rollNumber, int courseCode);

#endif