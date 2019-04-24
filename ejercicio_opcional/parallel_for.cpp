/* SumaVectoresC.c
 Suma de dos vectores: v3 = v1 + v2

 Para compilar usar (-lrt: real time library, es posible que no sea necesario usar -lrt):
	gcc  -O2  SumaVectores.c -o SumaVectores -lrt
	gcc  -O2 -S SumaVectores.c -lrt

 Para ejecutar use: SumaVectoresC longitud

*/

/*
  Con 3 pragma
  Memoria dinámica.
  Tamaño del vector 100000000 (Si falla quitamos 0)
  Con float y con double
  Con 1,2,4,8 hebras
  #pragma omp parallel for
  #pragma omp parallel simd for
  #pragma omp simd for

*/

#include <iostream>
#include <cstdlib>	// biblioteca con funciones atoi(), malloc() y free()
#include <cstdio>	// biblioteca donde se encuentra la función printf()
#include <ctime>	// biblioteca donde se encuentra la función clock_gettime()
#include <omp.h>


//#define F
#define D

int main(int argc, char** argv){

  const int TAM = 100000000;

#ifdef F
  float *v1 = new float[TAM];
  float *v2 = new float[TAM];
  float *v3 = new float[TAM];
#endif
#ifdef D
  double *v1 = new double[TAM];
  double *v2 = new double[TAM];
  double *v3 = new double[TAM];
#endif

  int i;
  double t_ini, t_fin, t_total=0;


  //Leer argumento de entrada (nº de hebras a usar)
  if (argc<2){
    printf("Faltan nº de hebras a usar\n");
    exit(-1);
  }

  int threads = atoi(argv[1]);


  omp_set_num_threads(threads);
  //Inicializar vectores
  
  t_ini = omp_get_wtime();
  #pragma omp parallel for
  for(i=0; i<TAM; ++i){
    v1[i] = TAM*0.1+i*0.1; v2[i] = TAM*0.1-i*0.1;
  }
  t_fin = omp_get_wtime();
  
  t_total += t_fin-t_ini;

  #pragma omp parallel for
  for(i=0; i<TAM; ++i)
    v3[i] = v1[i] * v2[i];

  //Imprimir tiempo
  printf("%11.9f\n", t_total);
  return 0;
}
