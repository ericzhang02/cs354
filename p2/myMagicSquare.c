///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////

// add your own File Header information here (as provided in p2A or Commenting guide

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    printf("Enter magic square's size (odd integer >=3)\n");
    int size;
    scanf("%d", &size);
    if (size < 3){
        printf("Magic square size must be >= 3.\n");
                exit(1);
    }
    if (size % 2 == 0){
        printf("Magic square size must be odd.\n");
                exit(1);
    }
    return size;
}

/* TODO:
 * Makes a magic square of size n using the
 * Siamese magic square algorithm or alternate from assignment
 * or another valid alorithm that produces a magic square.
 *
 * n is the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n) {
    MagicSquare* square = (MagicSquare*) malloc(sizeof(MagicSquare));
    square->size = n;
    square->magic_square = (int**) malloc(sizeof(int*)*n);
    if (square->magic_square == NULL){
                printf("not enough memory\n");
                exit(1);
        }
    for (int i = 0; i < n; i++){
        *((square->magic_square)+i) = malloc(n*sizeof(int));
        if (*((square->magic_square)+i) == NULL){
                        printf("not enough memory\n");
                        exit(1);
                }
    }
    //enter 0 for all entrees
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            *(*(square->magic_square+row)+col) = 0;
        }
    }
    //starting position
    int currentRow = 0;
    int currentCol = n / 2;
    //counts from 1 to n*n+1 and places digits as needed
    for (int currentNum = 1; currentNum < n * n + 1; currentNum++){
        //if current box is empty then input number
        *(*(square->magic_square+currentRow)+currentCol) = currentNum;
        int rowBefore = currentRow;
        int colBefore = currentCol;
        //move current box up and to the right
        currentRow--;
        currentCol++;
        //if row was at bottom, move to top
        if(currentRow < 0){
            currentRow = n-1;
        }
        //if col was at most right, move to most left
        if (currentCol > n-1){
            currentCol = 0;
        }
        //if up and to right is taken, move back down and left and go down once more
        if (*(*(square->magic_square+currentRow)+currentCol) != 0){
            currentRow = rowBefore+1;
            currentCol = colBefore;
            //if at bottom, go to top
            if (currentRow > n-1){
                currentRow = 0;
            }
        }
    }
    return square;
}

/* TODO:
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *fptr;
    fptr = fopen(filename, "w");
    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }
    //print rows
    fprintf(fptr, "%i\n", magic_square->size);
    for (int i = 0; i < magic_square->size; i++){
        for (int j = 0; j < magic_square->size; j++){
            fprintf(fptr, "%i", *(*(magic_square->magic_square+i)+j));
            //print comma if not last element in line
            if (j != magic_square->size-1){
                fprintf(fptr,",");
            }
        }
        fprintf(fptr,"\n");
    }
    //close file
    fclose(fptr);
}


/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 *
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
    // TODO: Check input arguments to get output filename
        if (argc!=2){
                printf("Invalid number of CLAs\n");
                exit(1);
        }
    char *filename = *(argv+1);
    // TODO: Get magic square's size from user
    int size = getSize();

    // TODO: Generate the magic square by correctly interpreting
    //       the algorithm(s) in the write-up or by writing or your own.
    //       You must confirm that your program produces a
    //       Magic Sqare as described in the linked Wikipedia page.
    MagicSquare* square = generateMagicSquare(size);

    // TODO: Output the magic square
    fileOutputMagicSquare(square, filename);
    //free memory
    for (int i = size-1; i > -1; i--){
        free(*(square->magic_square+i));
        *(square->magic_square+i) = NULL;
    }
    free((square->magic_square));
    free(square);
    return 0;
}