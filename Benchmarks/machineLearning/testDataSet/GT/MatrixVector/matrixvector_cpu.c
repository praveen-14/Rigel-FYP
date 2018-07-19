
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int i,j;

  int N = atoi(argv[1]);
  float *b  = (float *)malloc(sizeof(float)*N);
  float *c = (float *)malloc(sizeof(float)*N);
  float A[N][N];
  memset(A, 0, N * N * sizeof(float));



	// computes A*b
  double startTime = omp_get_wtime();
	#pragma omp parallel for
      for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
          A[i][j] = i*N+j*N;
          b[i] = i*N;
        }
      }

	#pragma omp parallel for
  for (int k = 0; k < N; k++){
	   for (int i=0; i<N; i++) {
		     c[i]=0;
		    for (int j=0;j<N;j++) {
			       c[i]=c[i]+A[i][j]*b[j]*k + sin(k)*exp(k)/(k + 1.) + sin(j)*exp(j)/(j + 1.);
		       }
      }
	}
  printf("%f\n",omp_get_wtime()-startTime );
return 0;
}