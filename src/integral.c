#include <omp.h>
#include <stdio.h>

int main() {
  int threads;
  int steps = 1e9;
  double step = 1 / (double)steps;

  double time = omp_get_wtime();

  double sum = 0;

#pragma omp parallel
  {

#pragma omp master
    { threads = omp_get_num_threads(); }

#pragma omp for reduction(+ : sum) nowait
    for (int i = 0; i < steps; i++) {
      double x = (i + 0.5) * step;
      sum += 4 / (1 + x * x);
    }
  }

  sum *= step;

  printf("result: %f\ntook %f seconds\nwith %d threads\n", sum,
         omp_get_wtime() - time, threads);
}
