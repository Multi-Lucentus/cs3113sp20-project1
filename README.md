# Intro to OS Project 1 - CPU Scheduling
by Parker Brandt (ID: 113521131)</br>

<b><u>Running the Program</u></b></br>
To run the program, simply type "make all" in the command line and it will compile to an executable file named "project1".</br>
From there, the user can just type "./project1 [filename]" to run the program. [filename] should be replaced with the name of the file with the instructions for the program.</br></br>


<b><u>Functions</b></u></br>
<i>char* readline(int fd)</i></br>
This function takes in a file descriptor, and then uses that file descriptor to read the file. The function reads the file until a newline character appears, and once it does, it returns the string before the newline character.</br></br>

<i>char** split(char* string, char split)</i></br>
This function takes in a string as the "char* string" parameter splits the string into an array of strings according to the "char split" parameter. The function then returns the array of strings.</br></br>
