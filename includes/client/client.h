int addStudent(int rollNumber, char *name, float CGPA, int numberOfSubjects);
int modifyStudent(int rollNumber, float CGPA);
int deleteStudent(int rollNumber);
int addStudentCourse(int rollNumber, int courseCode, int marks);
int modifyStudentCourse(int rollNumber, int courseCode, int marks);
int deleteStudentCourse(int rollNumber, int courseCode);
int openConnection();
void closeConnection();