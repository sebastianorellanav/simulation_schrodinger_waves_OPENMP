#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       // for time()
#include "../incl/simulation.h"
#include "../incl/utils.h"

float C = 1.0; // Velocidad de la onda en el medio.
float DT = 0.1; // Intervalo de tiempo con que avanza la simulacion.
float DD = 2.0; // Cambio en la superficie.

__host__ int main(int argc, char *argv[]){

    int N = 0; // Tamano grilla.
    int x = 0; // NTamaño de bloque en x.
    int y = 0; // Tamaño de bloque en y.
    int T = 0; // Numero de pasos.
    const char* file = NULL; // Archivo de salida.

    int count; // Contador de opciones.
    int passcount = 0; // Contador de opciones validas.

    if (argc == 11){
        for( count = 0; count < argc; count++){

            if(strcmp( argv[count], "-N" ) == 0){
                sscanf(argv[count+1],"%d",&N);
                passcount +=1;
            }
            else if(strcmp( argv[count], "-x" ) == 0){
                sscanf(argv[count+1],"%d",&x);
                passcount +=1;
            }
            else if(strcmp( argv[count], "-y" ) == 0){
                sscanf(argv[count+1],"%d",&y);
                passcount +=1;
            }
            else if(strcmp( argv[count], "-f" ) == 0){
                file = argv[count+1];
                passcount +=1;
            }
            else if(strcmp( argv[count], "-T" ) == 0){
                sscanf(argv[count+1],"%d",&T);
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

        // Se asigna la memoria en CPU
        float *matrix_t0 = (float *)malloc(N*N*sizeof(float));
        float *matrix_t1 = (float *)malloc(N*N*sizeof(float));

        // Se inicializa la matriz 
        initialize_matrix(&matrix_t0, N);

        //Se inicializa el tamaño de grilla y de bloque
        dim3 blocksize;
        dim3 gridsize; 
        gridsize.x = N;
        gridsize.y = N;
        blocksize.x = x;
        blocksize.y = y;

        // Se asigna la memoria en GPU
        cudaMalloc((void **) &m_t0, N*N*sizeof(float));
        cudaMalloc((void **) &m_t1, N*N*sizeof(float));

        // Se copia la matriz de cpu a gpu
        cudaMemcpy(m_t0, matrix_t0, N*N*sizeof(float), cudaMemcpyHostToDevice);

        get_first_matrix<<<gridsize, blocksize>>>(float &m_t0, float &m_t1, int N);

        for(i = 0; i < N; i++){
            get_matrix<<<gridsize, blocksize>>>(float &m_t0, float &m_t1, int N);
        }

        cudaMemcpy(matrix_t1, m_t1,  N*N*sizeof(float), cudaMemcpyDeviceToHost);

        save_image(matrix_t1, N, file);


        return 1;
    }
    else{
        printf("¡Hay una o mas opciones invalidas!\n");
        return 404;
    }
}