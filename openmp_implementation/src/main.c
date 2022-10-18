#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       // for time()
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
        float *matrix_t0 = (float *)malloc(N*N*sizeof(float));
        float *matrix_t1 = (float *)malloc(N*N*sizeof(float));
        double time_spent = 0.0;


        //Secuencial
        clock_t begin = clock();
        initialize_matrix(&matrix_t0, N);
        matrix_t1 = get_first_matrix(&matrix_t0, N);
        for(i = 0; i < T; i++){
            get_matrix_sequential(&matrix_t1, &matrix_t0, N);
        }
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Tiempo secuencial: %f segundos\n\n", time_spent);
        save_image(matrix_t1, N, "secuencial.raw");
        
        free(matrix_t0);
        free(matrix_t1);
        matrix_t0 = (float *)malloc(N*N*sizeof(float));
        matrix_t1 = (float *)malloc(N*N*sizeof(float));


        // PARALELO
        double start;
        double finish;
        start = omp_get_wtime();
        initialize_matrix(&matrix_t0, N);
        matrix_t1 = get_first_matrix_paralell(&matrix_t0, N, H);
            for(i = 0; i < T; i++){
                get_matrix_paralell(&matrix_t1, &matrix_t0, N, H);
            }
        
        finish = omp_get_wtime();
        printf("Tiempo paralelo: %f sec.\n", finish-start);
        //print_matrix(&matrix, N); //matriz creada de forma paralela
        save_image(matrix_t1, N, file);

        return 1;
    }
    else{
        printf("¡Hay una o mas opciones invalidas!\n");
        return 404;
    }
}