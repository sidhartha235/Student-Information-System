# Student Information System

## Input:
<ul>
    <li>Specify operation to be performed with Student and Course Information.</li>
    <li>For example, refer "input.txt" file.</li>
</ul>

## Output:
<ul>
    <li>Student as well as respective Courses Information into a CSV file <strong>'output/08_19.out'</strong>.</li>
    <li>You can check the end of the file 'output/logs.txt' to check if any errors or inconsistency is present in the Input file.</li>
</ul>

## Execution Steps:
<ol>
    <li>Create a folder named <strong>"output"</strong> in the base directory of this project, if NOT already present.</li>
    <li>Run the shell script file: "<strong>run.sh</strong>"</li>
    <ul>
        <li>Bash: <br><em>./run.sh -input &lt;input_file_name&gt;</em></li>
        <li>Git Bash: <br><em>sh run.sh -input &lt;input_file_name&gt;</em></li>
    </ul>
</ol>


## Modules:

### Parser
<ul>
    <li>Parse the input file.</li>
</ul>

### Student
<ul>
    <li>Data format and operations on Student information.</li>
    <li>Data Format: <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Student: Roll Number, Name, CGPA, Number of Subjects, Courses</li>
    <li>Operations:</li>
    <ol>
        <li>addStudent - Input: Roll Number, Name, CGPA, Number of Subjects</li>
        <li>modifyStudent - Input: Roll Number, CGPA</li>
        <li>deleteStudent - Input: Roll Number</li>
        <li>searchStudent - Input: Roll Number</li>
    </ol>
</ul>

### Course
<ul>
    <li>Data format and operations on Course information.</li>
    <li>Data Format: <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Course: Course Code, Marks</li>
    <li>Operations:</li>
    <ol>
        <li>addStudentCourse - Input: Roll Number, Course Code, Marks</li>
        <li>modifyStudentCourse - Input: Roll Number, Course Code, Marks</li>
        <li>deleteStudentCourse - Input: Roll Number, Course Code</li>
    </ol>
</ul>

### Writer
<ul>
    <li>Write 'Data' and 'Logs' to output files.</li>
</ul>
