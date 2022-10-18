#include <stdio.h>
#include <stdlib.h>
#include "../incl/constants.h"



__global__ void get_matrix(float **m1, float **m2,  int N){
    
    extern __shared__ float new[];
    int j = blockDim.x * blockIdx.x + threadIdx.x;
    int i = blockDim.y * blockIdx.y + threadIdx.y;

    new[i*N + j] = 0.0;

    float a1 = 0.0;
    float a2 = 0.0;
    float a3 = 0.0;
    float a4 = 0.0;  
    a1 = (*m1)[(i-1)*N +j];
    a2 = (*m1)[(i+1)*N + j];
    a3 = (*m1)[i*N + (j-1)];
    a4 = (*m1)[i*N + (j+1)];

    if(i > 0 && i < N-1 && j > 0 && j < N-1){
        new[i*N + j] = 2*(*m1)[i*N + j] - (*m2)[i*N + j] + ((C*C) * ((DT/DD)*(DT/DD)) * (a2+a1+a4+a3 - 4.0*(*m1)[i*N + j]));
    
    }

    (*m2)[i*N + j] = (*m1)[i*N + j];
    (*m1)[i*N + j] = new[i*N + j];

    cudaFree(new);
    //return new;
}

__global__ void get_first_matrix(float **m_t0, float **m_t1, int N){

    
    int j = blockDim.x * blockIdx.x + threadIdx.x;
    int i = blockDim.y * blockIdx.y + threadIdx.y;
    (*m_t1)[i*N +] = 0.0;

    float a1 = 0.0;
    float a2 = 0.0;
    float a3 = 0.0;
    float a4 = 0.0;  
    a1 = (*m)[(i-1)*N +j];
    a2 = (*m)[(i+1)*N + j];
    a3 = (*m)[i*N + (j-1)];
    a4 = (*m)[i*N + (j+1)];

    if(i > 0 && i < N-1 && j > 0 && j < N-1){
        (*m_t1)[i*N + j] = (*m)[i*N + j] + ((C*C) * ((DT*DT)/(DD*DD)) * (a2+a1+a4+a3 - 4.0*(*m)[i*N + j]));
    }
}



__host__ void initialize_matrix(float **matrix, int N){
    int i= 0;
    int j = 0;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if((i > 0.4*N && i <0.6*N) && (j > 0.4*N && j < 0.6*N)){
                (*matrix)[i*N + j] = 20.0;
            }
            else{
                (*matrix)[i*N + j] = 0.0;
            }
        }
    }
}

