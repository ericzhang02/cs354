//Eric Zhang 
//erzhang2@wisc.edu
#include <stdio.h>

int arr2D[128][8]; 

int main(int argc, const char * argv[]){
	for(int iteration = 0; iteration< 100; iteration++){
		for(int row = 0; row< 128; row+=64){
			for(int col = 0; col < 8; col++){
				arr2D[row][col] = iteration + row + col;
			}
		}
	}
    return 0;
}