#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "../incl/simulation.h"
#include "../incl/utils.h"

float C = 1.0; // Velocidad de la onda en el medio.
float DT = 0.1; // Intervalo de tiempo con que avanza la simulacion.
float DD = 2.0; // Cambio en la superficie.

int main(int argc, char *argv[]){

    int N = 0; // Tamano grilla.
    int H = 0; // Numero de hebras.
    int T = 0; // Numero de pasos.
    int t = 0; // Iteracion de salida.
    const char* file = NULL; // Archivo de salida.

    int count; // Contador de opciones.
    int passcount = 0; // Contador de opciones validas.

    if (argc == 11){
        for( count = 0; count < argc; count++){

            if(strcmp( argv[count], "-N" ) == 0){
                sscanf(argv[count+1],"%d",&N);
                passcount +=1;
            }
            else if(strcmp( argv[count], "-T" ) == 0){
                sscanf(argv[count+1],"%d",&T);
                passcount +=1;
            }
            else if(strcmp( argv[count], "-H" ) == 0){
                sscanf(argv[count+1],"%d",&H);
                passcount +=1;
            }
            else if(strcmp( argv[count], "-f" ) == 0){
                file = argv[count+1];
                passcount +=1;
            }
            else if(strcmp( argv[count], "-t" ) == 0){
                sscanf(argv[count+1],"%d",&t);
                passcount +=1;
            }
        }
    }
    else{
        printf("¡No se han ingresado todas las opciones!.\n");
        return 404;
    }
    if(passcount == 5){    
        int i = 0;
        int j = 0;
        float *matrix = (float *)malloc(N*N*sizeof(float));
        
        // PARALELO
        initialize_matrix(&matrix, N);
        #pragma omp paralel num_threads(H)
        {
            for(i = 0; i < T; i++){
                get_matrix_paralel(&matrix, N);
            }
        }
        print_matrix(&matrix, N); //matriz creada de forma paralela

        save_image(matrix, N, file);

        return 1;
    }
    else{
        printf("¡Hay una o mas opciones invalidas!\n");
        return 404;
    }
}