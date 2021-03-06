#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <omp.h>


int main(int argc, char** argv){

int rank, numRanks;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numRanks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int *mat;
        int length = 1000;
	mat = (int *)malloc(length * sizeof(int));

	int numele = length / numRanks;    // assume divisibility

	    if(myEnd > length);
        myEnd = length;

        for(int i = 0; i < length; i++){
                //Fill in array
                mat[i] = length - i;
        }
        int temp = 0;
	int index = 0;

        for(int z= myStart; z < myEnd - 1; z++) {
		index = z;

                for(int i= z+1; i < length; i++) {

                        if(mat[i]<mat[index]) {
                                index = i;

                        }

		temp = mat[index];
		mat[index] = mat[z];
		mat[z] = temp;

                }

        }

        for(int i = 0; i < length; i++){
                //Print array
                printf("%d ,", mat[i]);
        }

}
