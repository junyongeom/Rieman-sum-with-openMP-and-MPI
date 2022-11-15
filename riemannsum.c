#include <mpi.h>
#include <omp.h>
#include <math.h>
#include "riemannsum.h"
#include "util.h"
#include <stdio.h>
double riemannsum(int num_intervals, int mpi_rank, int mpi_world_size,
                  int threads_per_process) {
  double pi = 0;
  double h = 1.0 / (double)num_intervals;

  /*********** with thread ***/
  double my_pi = 0;
  int i;
  omp_set_num_threads(threads_per_process);  
  MPI_Barrier(MPI_COMM_WORLD);

  	my_pi = 0.0;
    #pragma omp parallel shared(my_pi), private(i)
    {      
      int my_id = omp_get_thread_num();
      #pragma omp barrier   
      for(i = mpi_rank * threads_per_process + my_id + 1 ; i <= num_intervals; i += (mpi_world_size * threads_per_process)){
        double x = h * ((double)i - 0.5);
        #pragma omp critical
        my_pi += h * f(x);
      }   
      #pragma omp barrier          
      if(my_id == 0){
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Reduce(&my_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);        
      }
    }
  /*********** with thread end ***/
  return pi;
}