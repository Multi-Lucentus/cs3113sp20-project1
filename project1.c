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
char** split(char* string, char splitChar);


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
	strcpy(firstLine, readline(fd));

	// TEST OUTPUT
	dprintf(STDERR, "First Line: %s\n", firstLine);
	dprintf(STDERR, "Second Line: %s\n", secondLine);

	// Parse through the two lines to get the data
	numProcesses = atoi(firstLine);
	
	char** strArray = split(secondLine, ' ');
	numThreads = atoi(strArray[0]);
	numInstructions = atoi(strArray[1]);


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
	}


	// Calculate information about the processes and output
	

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
  *
  */
char** split(char* string, char splitChar)
{
	char** stringArray;
	int numSplits;

	// First, iterate through the string and count the number of occurrences
	// of the character to split on
	for(int i = 0; i < strlen(string); i++)
		if(string[i] == splitChar)
			numSplits++;

	stringArray = (char**)malloc(numSplits * sizeof(char*));
	for(int i = 0; i < numSplits; i++)
		stringArray[i] = (char*)malloc(BUF_SIZE * sizeof(char));

	for(int i = 0; i < numSplits; i++)
	{
		// Get the string
		for(int j = 0; j < strlen(string); j++)
		{
		}
	}

}		
