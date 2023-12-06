#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int steps = 1000000000;
  double step = 1 / (double)steps;

  double time = omp_get_wtime();

  double sum = 0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < steps; i++) {
    double x = (i + 0.5) * step;
    sum += 4 / (1 + x * x);
  }

  sum *= step;

  printf("result: %f\ntook %f seconds\n", sum, omp_get_wtime() - time);
}
