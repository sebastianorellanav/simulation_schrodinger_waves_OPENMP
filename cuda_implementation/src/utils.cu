#include <stdio.h>
#include <stdlib.h>
#include "../incl/constants.h"

__host__ void save_image(float *m, int N,const char* f){
    FILE *out = fopen(f, "w");
    fwrite(m, sizeof(float), N*N, out);
    fclose(out);
}

__host__ void print_matrix(float **matrix, int N){
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