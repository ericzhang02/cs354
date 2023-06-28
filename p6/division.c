////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

int divisionCounter = 0;

void handler_SIGINT() {
	printf("Total number of operations completed successfully: %i\n", divisionCounter);
	printf("The program will be terminated.\n");
	exit(0);
}

void handler_SIGFPE() {
	printf("Error: a division by 0 operation was attempted.\n");
	printf("Total number of operations completed successfully: %i\n", divisionCounter);
	printf("The program will be terminated.\n");
	exit(0);
}

int main(){

	//Register SIGINT handler
	struct sigaction saINT;
    memset(&saINT, 0, sizeof(saINT));
    saINT.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &saINT, NULL) != 0) {
        exit(1);
    }

    //Register SIGFPE handler
	struct sigaction saFPE;
    memset(&saFPE, 0, sizeof(saFPE));
    saFPE.sa_handler = handler_SIGFPE;
    if (sigaction(SIGFPE, &saFPE, NULL) != 0) {
        printf("Error binding SIGFPE handler \n");
        exit(1);
    }

    //declaring strs
	char dividendStr[50];
	char divisorStr[50];

	while(1) {
		
		//get user input
		printf("Enter first integer: ");
		if (fgets(dividendStr, 50, stdin) == NULL) { //use fgets and check ret value
			printf("fgets error\n");
			exit(1);
		}
        //get second user input
		printf("Enter second integer: ");
		if (fgets( divisorStr, 50, stdin) == NULL) { //use fgets and check ret value
			printf("fgets error\n");
			exit(1);
		}

		//get input as integers
		int dividend = atoi(dividendStr); 	
		int divisor = atoi(divisorStr); 
	
		//calculations
		int quotient = dividend / divisor;
		int remainder = dividend % divisor; 
		
		divisionCounter++;		

		printf("%i / %i is %i with a remainder of %i\n", dividend, divisor, quotient, remainder);
	}
}