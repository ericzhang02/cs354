////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      NA
// Semester:         CS 354 Lecture 01 Spring 2023
// Instructor:       deppeler
// 
// Author:           Eric Zhang
// Email:            Erzhang2@wisc.edu
// CS Login:         ericz
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

int seconds = 4;
int sigCounter = 0;

void handler_SIGALRM() {
	time_t t;
	int pid = getpid();
	
	//get time
	if (((time_t) -1) == time(&t) ){
	  printf("Error with time\n");
		exit(1);
	}
	//format
	char* CurrentTime = ctime(&t);
	if (CurrentTime == NULL) { 
		printf("Error with ctime\n");
		exit(1);
	}
	//print time
	printf("PID: %i ", pid);
	printf("CURRENT TIME: %s", CurrentTime);
	alarm(seconds); //reset alarm 
}

void handler_SIGUSR1() {
	sigCounter++; 
	printf("SIGUSR1 handled and counted!\n");
}

void handler_SIGINT() {
	printf("\nSIGINT handled\n");
	printf("SIGUSR1 was handled %i times. Exiting now.\n", sigCounter);
	exit(0);
}

int main(int argc, const char * argv[]) {

	alarm(seconds);
	printf("PID and time print every 4 seconds.\nType Ctrl-C to end the program.\n");

	//Register SIGALRM handler
	struct sigaction saALRM;
	memset(&saALRM, 0, sizeof(saALRM));
	saALRM.sa_handler = handler_SIGALRM;
	if (sigaction(SIGALRM, &saALRM, NULL) != 0){
    	printf("Error binding SIGALRM handler \n");
		exit(1);
	}
    
  	//Register SIGUSR1 handler
	struct sigaction saUSR1;
	memset(&saUSR1, 0, sizeof(saUSR1));
	saUSR1.sa_handler = handler_SIGUSR1;
	if (sigaction(SIGUSR1, &saUSR1, NULL) != 0) {
		printf("Error binding SIGUSR1 handler \n"); //bind and check if worked
		exit(1);
	}

	//Register SIGINT handler
	struct sigaction saINT;
	memset(&saINT, 0, sizeof(saINT));
	saINT.sa_handler = handler_SIGINT;
	if (sigaction(SIGINT, &saINT, NULL) != 0) {
		printf("Error binding SIGINT handler \n"); //bind and check if worked
		exit(1);
	}

	//infinite loop
	while (1){}

	return 0;
}