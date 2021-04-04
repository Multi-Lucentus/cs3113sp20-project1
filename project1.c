#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define BUF_SIZE 16


typedef enum bool {false, true} bool;


struct Process
{
	int pid;
	int burst;
	int priority;
};
typedef struct Process Process;


// Prototype Functions
char* readline(int fd);
char** split(char* string, char split);

int countContextSwitches(Process* processes, int numInstructions);
int countNonvolSwitches(Process* processes, int numInstructions);
double calcCPUUtilization(Process* processes, int numInstructions);
double calcThroughput(Process* processes, int numThreads, int numInstructions);
double calcTurnaroundTime(Process* processes, int numThreads, int numInstructions);
double calcWaitTime(Process* processes, int numInstructions);
double calcResponseTime(Process* processes, int numInstructions);


// Main Function
// Start of Program Logic
int main(int argc, char *argv[])
{
	// Variables
	char *filename;
	
	int fd;
	char *buffer;

	int numProcesses;
	int numThreads;
	int numInstructions;

	int numContextSwitches;
	int numNonvolSwitches;
	double cpuUtil;
	double throughput;
	double turnAroundTime;
	double waitTime;
	double responseTime;

	Process *processes;


	// Check the command-line arguments
	// argc = 1: use stdin
	// argc = 2: use argv[1] for filename
	if(argc == 1)
		filename = "STDIN";
	else if(argc == 2)
		filename = argv[1];
	else
	{
		// Print error to STDERR
		dprintf(STDERR, "Illegal number of commmand-line arguments.\n");
		exit(EXIT_FAILURE);
	}

	// Initialize the arrays
	buffer = (char*)malloc(BUF_SIZE * sizeof(char));

	// Open the file
	// If we need to use STDIN, fd will just be 0
	if(strcmp(filename, "STDIN") == 0)
		fd = 0;
	else
		fd = open(filename, O_RDONLY, 0);


	// Read the first two lines to get the initial data
	char* firstLine = (char*)malloc(BUF_SIZE * sizeof(char));
	char* secondLine = (char*)malloc(BUF_SIZE * sizeof(char));

	strcpy(firstLine, readline(fd));
	strcpy(secondLine, readline(fd));

	// TEST OUTPUT
	dprintf(STDERR, "First Line: %s\n", firstLine);
	dprintf(STDERR, "Second Line: %s\n", secondLine);

	// Parse through the two lines to get the data
	numProcesses = atoi(firstLine);
	dprintf(STDERR, "Num Processes: %d\n", numProcesses);
	
	char** strArray = split(secondLine, ' ');

	numThreads = atoi(strArray[0]);
	dprintf(STDERR, "Num Threads: %d\n", numThreads);

	numInstructions = atoi(strArray[1]);
	dprintf(STDERR, "Num Instructions: %d\n", numInstructions);


	// Read through the file and add information to the Process array
	processes = (Process*)malloc(numInstructions * sizeof(Process));
	
	char* line;
	char** data;
	for(int i = 0; i < numInstructions; i++)
	{
		// Get the line
		line = readline(fd);

		// Parse the data
		data = split(line, ' ');

		// Update the data inside the processes array
		processes[i].pid = atoi(data[0]);
		processes[i].burst = atoi(data[1]);
		processes[i].priority = atoi(data[2]);

		// TEST OUTPUT
		dprintf(STDERR, "PID: %d Burst: %d Prio: %d\n", processes[i].pid, processes[i].burst, processes[i].priority);
	}


	// Calculate information about the processes and output
	numContextSwitches = countContextSwitches(processes, numInstructions);
	dprintf(STDOUT, "%d\n", numContextSwitches);
	
	numNonvolSwitches = countNonvolSwitches(processes, numInstructions);
	dprintf(STDOUT, "%d\n", numNonvolSwitches);

	cpuUtil = calcCPUUtilization(processes, numInstructions);
	dprintf(STDOUT, "%.2f\n", cpuUtil);

	throughput = calcThroughput(processes, numThreads, numInstructions);
	dprintf(STDOUT, "%.2f\n", throughput);

	turnAroundTime = calcTurnaroundTime(processes, numThreads, numInstructions);
	dprintf(STDOUT, "%.2f\n", turnAroundTime);

	exit(EXIT_SUCCESS);
}


// Function Declarations

/**
  * Reads a line from the file pointed to by the file descriptor
  * Returns the string obtained from that file
  */
char* readline(int fd)
{
	char *buffer = (char*)malloc(BUF_SIZE * sizeof(char));
	int bufCount = 0;

	char c;
	while(read(fd, &c, 1) > 0)
	{
		// Check if the character is newline
		if(c != '\n')
		{
			buffer[bufCount] = c;
			bufCount++;
		}
		else
		{
			buffer[bufCount] = '\0';
			break;
		}
	}

	return buffer;
}


/**
  * Splits a string according to the split parameter
  * Returns an array of strings
  */
char** split(char* string, char split)
{
	// Count number of occurrences of the split character
	int splitCount = 0;
	for(int i = 0; i < strlen(string); i++)
		if(string[i] == split)
			splitCount++;

	char** stringArray = (char**)malloc((splitCount + 1) * sizeof(char*));
	for(int i = 0; i < (splitCount + 1); i++)
		stringArray[i] = (char*)malloc(BUF_SIZE * sizeof(char));

	int arrayCount = 1;

	stringArray[0] = strtok(string, &split);
	
	while(stringArray[arrayCount] != NULL)
	{
		stringArray[arrayCount] = strtok(NULL, &split);
		arrayCount++;
	}

	return stringArray;
}


/**
  * Counts the number of voluntary context switches in the processes list
  * A voluntary context switch is the completion of a process
  */
int countContextSwitches(Process* processes, int numInstructions)
{
	int count = 0;
	int testPID;
	bool isVoluntary = true;

	for(int i = 0; i < numInstructions; i++)
	{
		// The last instruction will always be a voluntary context switch
		if(i == numInstructions - 1)
			count++;
		else
		{
			testPID = processes[i].pid;

			for(int j = i + 1; j < numInstructions; j++)
				if(processes[j].pid == testPID)
					isVoluntary = false;

			if(isVoluntary == true)
				count++;
		}
	}

	return count;
}

/**
  * Counts the number of nonvoluntary context switches in the processes list
  * A nonvoluntary context switch is a context switch if the process has not fully completed and completes later
  */
int countNonvolSwitches(Process* processes, int numInstructions)
{
	int count = 0;
	int testPID;
	bool isNonVoluntary = false;

	for(int i = 0; i < numInstructions; i++)
	{
		testPID = processes[i].pid;

		for(int j = j + 2; j < numInstructions; j++)
			if(processes[j].pid == testPID)
				isNonVoluntary = true;
		
		if(isNonVoluntary == true)
			count++;
	}

	return count;
}

/**
  * Calculates the CPU Utilization Percentage
  * CPU Utilization is the percentage of time that the processor has been used
  */
double calcCPUUtilization(Process* processes, int numInstructions)
{
	int totalTime;
	int processTime = 0;

	for(int i = 0; i < numInstructions; i++)
		processTime += processes[i].burst;

	// In this case, the process time is the total time of the system
	totalTime = processTime;

	return (processTime / totalTime) * 100;
}

/**
  * Calculats the average throughput
  * Throughput is the average number of executions completed per time unit (none specified for this project)
  */
double calcThroughput(Process* processes, int numThreads, int numInstructions)
{
	double throughput;
	int numCompletedProcesses;
	double totalTime = 0;

	for(int i = 0; i < numInstructions; i++)
		totalTime += processes[i].burst;

	throughput = (numThreads / totalTime);

	return throughput;
}

/**
  * Calculates the average turnaround time for the process
  * Turnaround time is the time from submission of a process until completion
  */
double calcTurnaroundTime(Process* processes, int numThreads, int numInstructions)
{
	double turnaroundTime;
	int numCompletedTasks = 0;
	int testPID;
	double totalTime = 0;
	
	int* pidList = (int*)malloc(numThreads * sizeof(int));
	int listCount = 0;
	bool isPIDfound = false;
	int numOccurrences = 1;

	for(int i = 0; i < numInstructions; i++)
	{
		testPID = processes[i].pid;
		
		// Check to see if we have already summed the number for this PID
		// Do not want to sum it more than once
		for(int j = 0; j < listCount; j++)
			if(pidList[j] == testPID)
				isPIDfound = true;
		
		if(isPIDfound == false)
		{
			pidList[listCount] = testPID;
			listCount++;

			// Count the number of times this PID occurs
			for(int j = i + 1; j < numInstructions; j++)
				if(processes[j].pid == testPID)
					numOccurrences++;

			// Count the total burst time until the process completes
			for(int j = 0; j < numInstructions; j++)
			{
				if(numOccurrences > 0)
				{
					totalTime += processes[j].burst;
					
					if(processes[j].pid == testPID)
						numOccurrences--;
				}
			}
		}

		isPIDfound = false;
		numOccurrences = 1;
	}

	turnaroundTime = totalTime / numThreads;

	return turnaroundTime;
}

/**
  *
  */
double calcWaitingTime(Process* processes, int numThreads, int numInstructions)
{
	double waitTime;
	double totalTime;

	for(int i = 0; i < numInstructions; i++)
	{

	}

	return waitTime;
}
