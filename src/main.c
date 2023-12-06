#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int threads = 8;

  omp_set_num_threads(threads);

  int steps = 1000000000;
  double step = 1 / (double)steps;
  double result = 0;

  double time = omp_get_wtime();
#pragma omp parallel
  {
    int id = omp_get_thread_num();

    int threads_real = omp_get_num_threads();
    if (id == 0) {
      threads = threads_real;
    }

    double sum = 0;
    for (int i = id * (steps / threads_real);
         i < (steps / threads_real) * (id + 1); i++) {
      double x = (i + 0.5) * step;
      sum += 4 / (1 + x * x);
    }

#pragma omp critical
    result += sum * step;
  }

  printf("result: %f\ntook %f seconds\nwith %d threads\n", result,
         omp_get_wtime() - time, threads);
}
