#include <stdio.h>
#include <stdlib.h>
#include "../incl/constants.h"
#include <omp.h>



void get_matrix_paralell(float **m1, float **m2,  int N, int n_threads){
    
    float *new = (float *)malloc(N*N*sizeof(float));
    int i,j = 0;
    for (i = 0; i<N*N; i++){
        new[i] = 0.0;
    }
    int chunk = N/n_threads;
    #pragma omp parallel num_threads(n_threads) firstprivate(*m1, *m2, N)
    {
        #pragma omp for schedule(static, chunk)
        for(i=1; i<N-1; i++){
            for(j=1; j<N-1; j++){
                float a1 = 0.0;
                float a2 = 0.0;
                float a3 = 0.0;
                float a4 = 0.0;  
                a1 = (*m1)[(i-1)*N +j];
                a2 = (*m1)[(i+1)*N + j];
                a3 = (*m1)[i*N + (j-1)];
                a4 = (*m1)[i*N + (j+1)];

        
                new[i*N + j] = 2*(*m1)[i*N + j] - (*m2)[i*N + j] + ((C*C) * ((DT/DD)*(DT/DD)) * (a2+a1+a4+a3 - 4.0*(*m1)[i*N + j]));
            
            }
        }
    }

    for (i=0; i<N*N; i++){
        (*m2)[i] = (*m1)[i];
        (*m1)[i]= new[i];
        
    }
    free(new);
    //return new;
}

float* get_first_matrix_paralell(float **m, int N, int n_threads){

    float *new = (float *)malloc(N*N*sizeof(float));
    int i,j = 0;
    for (i = 0; i<N*N; i++){
        new[i] = 0.0;
    }
    int chunk = N/n_threads;
    #pragma omp parallel for num_threads(n_threads) schedule(dynamic, chunk)
    for(i=1; i<N-1; i++){
        for(j=1; j<N-1; j++){
            float a1 = 0.0;
            float a2 = 0.0;
            float a3 = 0.0;
            float a4 = 0.0;  
            a1 = (*m)[(i-1)*N +j];
            a2 = (*m)[(i+1)*N + j];
            a3 = (*m)[i*N + (j-1)];
            a4 = (*m)[i*N + (j+1)];


            new[i*N + j] = (*m)[i*N + j] + ((C*C) * ((DT*DT)/(DD*DD)) * (a2+a1+a4+a3 - 4.0*(*m)[i*N + j]));
        
        }
    }
    //for (i=0; i<N*N; i++){
    //    (*m)[i]= new[i];
    //}
    return new;
    //return new;
}

float* get_first_matrix(float **m, int N){

    float *new = (float *)malloc(N*N*sizeof(float));
    int i,j = 0;
    for (i = 0; i<N*N; i++){
        new[i] = 0.0;
    }

    for(i=1; i<N-1; i++){
        for(j=1; j<N-1; j++){
            float a1 = 0.0;
            float a2 = 0.0;
            float a3 = 0.0;
            float a4 = 0.0;  
            a1 = (*m)[(i-1)*N +j];
            a2 = (*m)[(i+1)*N + j];
            a3 = (*m)[i*N + (j-1)];
            a4 = (*m)[i*N + (j+1)];


            new[i*N + j] = (*m)[i*N + j] + ((0.5*C*C) * ((DT*DT)/(DD*DD)) * (a2+a1+a4+a3 - 4.0*(*m)[i*N + j]));
        
        }
    }
    //for (i=0; i<N*N; i++){
    //    (*m)[i]= new[i];
    //}
    return new;
    //return new;
}


void get_matrix_sequential(float **m1, float **m2,  int N){
    
    float *new = (float *)malloc(N*N*sizeof(float));
    int i,j = 0;
    for (i = 0; i<N*N; i++){
        new[i] = 0.0;
    }
    for(i=1; i<N-1; i++){
        for(j=1; j<N-1; j++){
            float a1 = 0.0;
            float a2 = 0.0;
            float a3 = 0.0;
            float a4 = 0.0;  
            a1 = (*m1)[(i-1)*N +j];
            a2 = (*m1)[(i+1)*N + j];
            a3 = (*m1)[i*N + (j-1)];
            a4 = (*m1)[i*N + (j+1)];

    
            new[i*N + j] = 2*(*m1)[i*N + j] - (*m2)[i*N + j] + ((C*C) * ((DT/DD)*(DT/DD)) * (a2+a1+a4+a3 - 4.0*(*m1)[i*N + j]));
        
        }
    }
    //print_matrix(new);
    for (i=0; i<N*N; i++){
        (*m2)[i] = (*m1)[i];
        (*m1)[i]= new[i];
        
    }
    free(new);
    //return new;
}

void initialize_matrix(float **matrix, int N){
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

