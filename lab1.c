#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10
#define C 1.0
#define DT 0.1
#define DD 2.0


void print_matrix(float **matrix){
    int i= 0;
    int j = 0;
    for(i = 0; i<N; i++){
        for(j=0; j<N; j++){
            printf(" %.3f ", (*matrix)[i*N + j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void get_matrix_paralel(float **m){
    
    float *new = (float *)malloc(N*N*sizeof(float));
    int i,j = 0;
    for (i = 0; i<N*N; i++){
        new[i] = 0.0;
    }
    #pragma omp for schedule(static, 1)
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


            new[i*N + j] = (*m)[i*N + j] + (((C*C)/2.0) * ((DT/DD)*(DT/DD)) * (a2+a1+a4+a3 - 4.0*(*m)[i*N + j]));
        
        }
    }
    for (i=0; i<N*N; i++){
        (*m)[i]= new[i];
    }
    free(new);
    //return new;
}


void get_matrix_sequential(float **m){
    
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


            new[i*N + j] = (*m)[i*N + j] + (((C*C)/2.0) * ((DT/DD)*(DT/DD)) * (a2+a1+a4+a3 - 4.0*(*m)[i*N + j]));
        
        }
    }
    //print_matrix(new);
    for (i=0; i<N*N; i++){
        (*m)[i]= new[i];
    }
    free(new);
    //return new;
}

void initialize_matrix(float **matrix){
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


int main(){
    int i = 0;
    int j = 0;
    float *matrix = (float *)malloc(N*N*sizeof(float));
    
    // PARALELO
    initialize_matrix(&matrix);
    int iter = 100;
    #pragma omp paralel num_threads(N)
    {
        for(i = 0; i < iter; i++){
            get_matrix_paralel(&matrix);
        }
    }
    print_matrix(&matrix); //matriz creada de forma paralela


    // SECUENCIAL
    initialize_matrix(&matrix);
    for(i = 0; i < iter; i++){
        get_matrix_sequential(&matrix);
    }
    print_matrix(&matrix); //matriz creada de forma secuencial
    
}