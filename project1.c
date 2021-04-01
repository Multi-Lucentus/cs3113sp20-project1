#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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


	// Read the first two lines to 

	// Read through the file and add information to the Process array
	processes = (Process*)malloc(numProcesses * sizeof(Process));

	

	// Calculate information about the processes and output
	

	// Output
	

	exit(EXIT_SUCCESS);
}


// Function Declarations

/**
  * Reads a line from the file pointed to by the file descriptor
  * Returns the string obtained from that file
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
