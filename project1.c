#include <stdlib.h>
#include <stdio.h>
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

int countContextSwitches(Process *process);
double calcCPUUtilization(Process *process);
double calcThroughput(Process *process);
double calcTurnaroundTime(Process *process);
double calcWaitTime(Process *process);
double calcResponseTime(Process *process);


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
	int numNonvolContextSwitches;
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
	{
		filename = "STDIN";
	}
	else if(argc == 2)
	{
		filename = argv[1];
	}
	else
	{
		// Print error to STDERR		
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
	char* firstLine;
	char* secondLine;
	char* data1, data2;

	strcpy(firstLine, readline(fd));
	strcpy(firstLine, readline(fd));

	// TEST OUTPUT
	dprintf(STDERR, "First Line: %s\n", firstLine);
	dprintf(STDERR, "Second Line: %s\n", secondLine);

	// Parse through the two lines to get the data
	numProcesses = atoi(firstLine);
	
	// Separate the second line at the space to get the two numbers
	bool isFirst = true;
	for(int i = 0; i < BUF_SIZE; i++)
	{
		if(isFirst == true)
		{
			if(secondLine[i] == ' ')
			{
				isFirst = false;
				
			}
		}
		else
		{

			if(secondLine[i] = '\0')
				break;
		}
	}

	// Read through the file and add information to the Process array
	processes = (Process*)malloc(numInstructions * sizeof(Process));
	
	char* line;
	for(int i = 0; i < numInstructions; i++)
	{
		// Get the line
		line = readline(fd);

		// Parse the data
		

		// Update the data inside the processes array
		processes[i].pid;
		processes[i].burst;
		processes[i].priority;
	}

	// Calculate information about the processes and output
	cpuUtil = calcCPUUtilization(processes);
	throughput = calcThroughput(processes);
	turnAroundTime = calcTurnaroundTime(processes);
	waitTime = calcWaitTime(processes);
	responseTime = calcResponseTime(processes);	

	// Output
	
	// Voluntary context switches
	printf("%d\n", numContextSwitches);

	// Non-voluntary context switches
	printf("%d\n", numNonvolContextSwitches);

	// CPU Utilization
	printf("%.2f\n", cpuUtil);

	// Average Throughput
	printf("%.2f\n", throughput);

	// Average Turnaround Time
	printf("%.2f\n", turnAroundTime);

	// Average Wait Time
	printf("%.2f\n", waitTime);

	// Average Response Time
	printf("%.2f\n", responseTime);

	exit(EXIT_SUCCESS);
}


// Function Declarations

/**
  * Reads a line from the file pointed to by the file descriptor
  * Returns the string obtained from that file
  * TODO: May have to add a line number parameter
  */
char* readline(int fd)
{
	char *buffer = malloc(BUF_SIZE * sizeof(char));
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
			break;
		}
	}

	return buffer;
}


/**
  *
  */
double calcCPUUtilization(Process *process)
{
	double cpuUtil;



	return cpuUtil;
}


/**
  * 
  */
double calcThroughput(Process *process)
{
	double throughput;


	return throughput;
}


/**
  *
  */
double calcTurnaroundTime(Process *process)
{
	double turnaroundTime;


	return turnaroundTime;
}


/**
  *
  */
double calcWaitTime(Process *process)
{
	double waitTime;

	return waitTime;
}


/**
  *
  */
double calcResponseTime(Process *process)
{
	double responseTime;


	return responseTime;
}
