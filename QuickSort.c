#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"


static int partition(int fpivot, int spivot, int *mat){
                int pivot = mat[spivot];
//		printf("Second pivot: %d",mat[spivot]);
                int i = fpivot-1;

                for(int z= fpivot; z<=spivot-1; z++) {
                        if(mat[z]<= pivot) {
                                i++;
                                int temp = mat[i];
                                mat[i]=mat[z];
                                mat[z]=temp;
                        }
                }
        int temp = mat[i+1];
        mat[i+1]= mat[spivot];
        mat[spivot]= temp;

        return i+1;
        }

static void quickSort(int *mat, int fpivot, int spivot){

                if(fpivot<spivot){

                       int pIndex = partition(fpivot, spivot, mat);
//			printf("\n pIndex: %d \n",pIndex);
                       // if(rank==0){
                                quickSort(mat, fpivot, pIndex-1);
                        //} //else if(rank == 1){
                                quickSort(mat, pIndex+1, spivot);
                        //}
                }
        }


int main(int argc, char** argv){


	int rank, numRanks;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &numRanks);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        int *mat;
        int length = 100000;
        mat = (int*) malloc(length* sizeof(int));
        int n = length -1;


        for(int i = 0; i < length; i++){
                //Fill in array
                mat[i] = length - i;
        }

	int numele = length/numRanks ;
	int myStart = rank*numele;
	int myEnd = myStart + numele-1;
	int *mymat;
        mymat = (int*) malloc(numele* sizeof(int));

	if(myEnd>length){
	myEnd = length;
	}
	double starttime = MPI_Wtime();
	MPI_Scatter(mat,numele,MPI_INT,mymat,numele,MPI_INT,0,MPI_COMM_WORLD);
	quickSort(mat,myStart+1,myEnd);
	MPI_Gather(mymat,numele,MPI_INT,mat,numele,MPI_INT,0,MPI_COMM_WORLD);
	//Quicksort
	quickSort(mat,0,n-1);
	double endtime = MPI_Wtime();
	double total = endtime-starttime;
	printf("Time: %f", total);
	if(rank==0){
	for(int i = 0; i < length ; i++){
                //Print out array
                printf("%d ,", mat[i]);
	}

        }
MPI_Finalize();
	}

