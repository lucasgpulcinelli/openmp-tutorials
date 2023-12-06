#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int threads;
  int steps = 1000000000;
  double step = 1 / (double)steps;
  double result = 0;

  double time = omp_get_wtime();
#pragma omp parallel
  {
    double sum = 0;
    int id = omp_get_thread_num();
    if (id == 0) {
      threads = omp_get_num_threads();
    }

#pragma omp for schedule(static)
    for (int i = 0; i < steps; i++) {
      double x = (i + 0.5) * step;
      sum += 4 / (1 + x * x);
    }

#pragma omp critical
    result += sum * step;
  }

  printf("result: %f\ntook %f seconds\nwith %d threads\n", result,
         omp_get_wtime() - time, threads);
}
