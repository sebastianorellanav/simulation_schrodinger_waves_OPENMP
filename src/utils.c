#include <stdio.h>
#include <stdlib.h>
#include "../incl/constants.h"

void save_image(float *m){
    FILE *f = fopen("ejemplo.raw", "w");
    fwrite(m, sizeof(float), N*N, f);
    fclose(f);
}

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