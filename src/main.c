#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int threads = 8;
  double *results = malloc(sizeof(double) * threads);

  omp_set_num_threads(threads);

  int steps = 1000000000;
  double step = 1 / (double)steps;

  double time = omp_get_wtime();
#pragma omp parallel
  {
    int id = omp_get_thread_num();

    int threads_real = omp_get_num_threads();
    if (id == 0) {
      threads = threads_real;
    }

    double result = 0;
    for (int i = id * (steps / threads_real);
         i < (steps / threads_real) * (id + 1); i++) {
      double x = (i + 0.5) * step;
      result += 4 / (1 + x * x);
    }

    results[id] = result;
  }

  double final = 0;
  for (int i = 0; i < threads; i++) {
    final += results[i];
  }
  final *= step;

  printf("result: %f\ntook %f seconds\nwith %d threads\n", final, omp_get_wtime() - time, threads);

  free(results);
}
