#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(int argc, char** argv){

	int *mat;
	int length = 1000;
	int lengthCopy = 1000;
	int start;

	mat = (int *)malloc(length * sizeof(int));

	for(int i = 0; i < length; i++){
		//Fill in array
		mat[i] = length - i;
	}

	
	for(int j=0; j<length-1; j++){
		#pragma omp parallel for default(none),shared(mat,start,length)
		for(int i=start; i < length-1; i++) {

			if(mat[i+1]<mat[i]) {
				int temp = mat[i];
				mat[i] = mat[i+1];
				mat[i+1] = temp;

			}

		}

	}

	for(int i = 0; i < length; i++){
                //Print out array
                printf("%d ,", mat[i]);
        }

}
