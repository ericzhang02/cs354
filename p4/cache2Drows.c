//Eric Zhang 
//erzhang2@wisc.edu
#include <stdio.h>

int arr2D[3000][500];

int main(int argc, const char * argv[]) {
    for (int row = 0; row < 3000; row++){
        for (int col = 0; col < 500; col++){
            arr2D[row][col] = row + col;
        }
    }
  return 0;
}