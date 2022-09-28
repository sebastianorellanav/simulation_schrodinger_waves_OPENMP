#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "../incl/simulation.h"
#include "../incl/utils.h"

int N = 256;
float C = 1.0;
float DT = 0.1;
float DD = 2.0;
int iter = 1000;

int main(){
    int i = 0;
    int j = 0;
    float *matrix = (float *)malloc(N*N*sizeof(float));
    
    // PARALELO
    initialize_matrix(&matrix);
    #pragma omp paralel num_threads(N)
    {
        for(i = 0; i < iter; i++){
            get_matrix_paralel(&matrix);
        }
    }
    print_matrix(&matrix); //matriz creada de forma paralela

    save_image(matrix);


    // SECUENCIAL
    //initialize_matrix(&matrix);
    //for(i = 0; i < iter; i++){
    //    get_matrix_sequential(&matrix);
    //}
    //print_matrix(&matrix); //matriz creada de forma secuencial
    
}