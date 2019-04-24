/* SumaVectoresC.c
 Suma de dos vectores: v3 = v1 + v2

 Para compilar usar (-lrt: real time library, es posible que no sea necesario usar -lrt):
	gcc  -O2  SumaVectores.c -o SumaVectores -lrt
	gcc  -O2 -S SumaVectores.c -lrt

 Para ejecutar use: SumaVectoresC longitud

*/

#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la función printf()
#include <time.h>	// biblioteca donde se encuentra la función clock_gettime()
#include <omp.h>


#define VECTOR_GLOBAL

#ifdef VECTOR_GLOBAL
#define MAX 33554432	//=2^25

double v1[MAX], v2[MAX], v3[MAX];
#endif

void InicializarVectores(int ini, int fin, int tam){
  for(int i=ini; i<fin; ++i){
    v1[i] = N*0.1+i*0.1;
    v2[i] = N*0.1-i*0.1;
  }
}

void SumaVectores(int ini, int fin){
  for(int i=ini; i<fin; ++i)
    v3[i] = v1[i] + v2[i];
}

int main(int argc, char** argv){
  //Leer argumento de entrada (nº de componentes del vector)
  if (argc<2){
    printf("Faltan nº componentes del vector\n");
    exit(-1);
  }
  unsigned int N = atoi(argv[1]);	// Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)

  const int N_ELEM_THREAD = N/4;
  const int INI_0         = 0;
  const int INI_1         = N_ELEM_THREAD;
  const int INI_2         = N_ELEM_THREAD*2;
  const int INI_3         = N_ELEM_THREAD*3;
//  const int INI_4         = N_ELEM_THREAD*4;
//  const int INI_5         = N_ELEM_THREAD*5;
//  const int INI_6         = N_ELEM_THREAD*6;
//  const int INI_7         = N_ELEM_THREAD*7;
//  const int INI_8         = N_ELEM_THREAD*8;
//  const int INI_9         = N_ELEM_THREAD*9;
//  const int INI_10        = N_ELEM_THREAD*10;
//  const int INI_11        = N_ELEM_THREAD*11;


  int i;
  int ini, fin;

  double t_ini, t_fin, t_total;

  printf("Tamaño Vectores:%u (%u B)\n",N, sizeof(unsigned int));

  #ifdef VECTOR_GLOBAL
  if (N>MAX) N=MAX;
  #endif


  //Inicializar vectores
  #pragma omp parallel
  {
    #pragma omp sections
    {
      #pragma omp section
        InicializarVectores(INI_0, INI_0+N_ELEM_THREAD, N);
      #pragma omp section
        InicializarVectores(INI_1, INI_1+N_ELEM_THREAD, N);
      #pragma omp section
        InicializarVectores(INI_2, INI_2+N_ELEM_THREAD, N);
      #pragma omp section
        InicializarVectores(INI_3, N, N);
    }



    t_ini = omp_get_wtime();

    #pragma omp sections
    {
      #pragma omp section
        SumaVectores(INI_0, INI_0+N_ELEM_THREAD);
      #pragma omp section
        SumaVectores(INI_1, INI_1+N_ELEM_THREAD);
      #pragma omp section
        SumaVectores(INI_2, INI_2+N_ELEM_THREAD);
      #pragma omp section
        SumaVectores(INI_3, N);
    }

    t_fin = omp_get_wtime();

  }


  t_total=(t_fin-t_ini);

  //Imprimir resultado de la suma y el tiempo de ejecuci�n
  if (N<12) {
  printf("Tiempo:%11.9f\t / Tamaño Vectores:%u\n",t_total,N);
  for(i=0; i<N; i++)
    printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           i,i,i,v1[i],v2[i],v3[i]);
  }
  else
    printf("Tiempo:%11.9f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           t_total,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);
  return 0;
}
