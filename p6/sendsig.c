////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
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
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){

	//check number of CLAs
	if(argc != 3) {
		printf("Usage: sendsig <signal type> <pid>\n");
		exit(1);
	}

	//if -i then send SIGUSR1 signal
	if(strcmp(argv[1], "-i") == 0) {
		if (kill(atoi(argv[2]), SIGINT)) {
			printf("SIGINT signal invalid\n");
			exit(1);
		}
	}

	//if -u then send SIGUSR1 signal
	if(strcmp(argv[1], "-u") == 0) {
		if (kill(atoi(argv[2]), SIGUSR1)) {
			printf("SIGUSR1 signal invalid\n");
			exit(1);
		}
    }
}