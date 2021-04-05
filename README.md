# Intro to OS Project 1 - CPU Scheduling
by Parker Brandt (ID: 113521131)</br>

<b><u>Running the Program</u></b></br>
To run the program, simply type "make all" in the command line and it will compile to an executable file named "project1".</br>
From there, the user can just type "./project1 [filename]" to run the program. [filename] should be replaced with the name of the file with the instructions for the program.</br></br>


<b><u>Functions</b></u></br>
<i>char* readline(int fd)</i></br>
This function takes in a file descriptor, and then uses that file descriptor to read the file. The function reads the file until a newline character appears, and once it does, it returns the string before the newline character.</br>

<i>char** split(char* string, char split)</i></br>
This function takes in a string as the "char* string" parameter splits the string into an array of strings according to the "char split" parameter. The function then returns the array of strings.</br>

<i>int countContextSwitches(Process* processes, int numInstructions)</i></br>
This function counts the number of voluntary context switches in the list of processes provided as the first parameter. The other parameter, is the number of instructions provided in the input file. The function returns the integer number of voluntary contextswitches.
(NOTE: A voluntary context switch is when a process completes and does not complete later)</br>

<i>int countNonvolSwitches(Process* processes, int numInstructions)</i></br>
This function counts the number of nonvoluntary context switches in a list of processes provided in the first parameter.
(NOTE: A nonvoluntary context switch is when a process finishes its burst but has not yet completed)</br>

<i>double calcCPUUtilization(Process* processes, int numInstructions)</i></br>
This function calculates the CPU utilization percentage. In this programming project, the CPU will be utilized 100% of the time, so it should always return 100.00</br>

<i>double calcThroughput(Process* processes, int numThreads, int numInstructions)</i></br>
This function calculates the average throughput of all of the processes given in the first parameter. The second parameter "int numThreads" is the number of individual threads in the processes list while "int numInstructions" is the number of total instructions and a singular thread can have multiple instructions.
(NOTE: Throughput is the number of executions completed per unit time, and no specific time unit was given in this assignment)</br>

<i>double calcTurnaroundTime(Process* processes, int numThreads, int numInstructions)</i></br>
Calculates the average turnaround time of all of the processes in the processes list. Turnaround time is the time from submission until completion, so in this assignment the average turnaround time will be the time for each process to complete divided by the number of threads.</br>

<i>double calcWaitingTime(Process* processes, int numThreads, int numInstructions)</i></br>
This function calculates the average waiting time for each process in "Process* processes" list. The waiting time is the number of time units from submission until the process begins executing.</br>

<i>double calcResponseTime(Process* processes, int numThreads, int numInstructions)</i></br>
This function calculates the average response time for each process in the processes list. The response time is similar to the wait time, but does not include when the process executes again later.
