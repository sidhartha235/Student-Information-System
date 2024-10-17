# Student Information System

## Input:

<ul>
    <li>Specify operation to be performed with Student and Course Information.</li>
    <li>For example, refer "input.txt" file.</li>
</ul>

## Output:

<ul>
    <li>Student as well as respective Courses Information into a CSV file <strong>'2108_2119.out'</strong>.</li>
</ul>

## Execution Steps:

Run the makefile using the following command:

```
make
```

Open 2 terminals in the project's directory.

Run the following to start the server process:

```
./server_08_19 <SERV_PORT>
```

Run the following to start the client process:

```
./client_08_19 <SERV_ADDR> <SERV_PORT> input <input_file>
```


## Modules:

### Client

<ul>
    <li>Store data passed by the parser into a structure.</li>
    <li>Write the Operation and Data to a Socket and waits for response.</li>
    <li>Client prints resposne to standard output</li>
</ul>

### Parser

<ul>
    <li>Parse the input file.</li>
    <li>Pass the data to the client.</li>
</ul>

### Server

<ul>
    <li>Read and extract data from the Socket.</li>
    <li>Use the student and course modules to process the Student database information.</li>
    <li>Use the writer module to generate the output file.</li>
    <li>Server writes into output file everytime a client disconnects</li>
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
    <li>Write 'Data' to output files.</li>
</ul>
