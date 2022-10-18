
#ifndef SIMULATION_H
#define SIMULATION_H

void get_matrix_paralell(float **m1, float **m2,  int N, int num_threads);
void initialize_matrix(float **matrix, int N);
float* get_first_matrix_paralell(float **m, int N, int num_threads);
void get_matrix_sequential(float **m1, float **m2,  int N);
float* get_first_matrix(float **m, int N);

#endif