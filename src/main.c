#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int *arr, int s, int e) {
  int pivot = arr[s];
  int i = s + 1;

  // I don't think this is parallelizable
  for (int j = s + 1; j <= e; j++) {
    if (arr[j] < pivot) {
      swap(arr + i, arr + j);
      i++;
    }
  }

  swap(arr + i - 1, arr + s);
  return i - 1;
}

void quicksort(int *arr, int s, int e) {
  if (s >= e) {
    return;
  }

  int pivot = partition(arr, s, e);

  if (pivot - 1 - s < 500) {
    quicksort(arr, s, pivot - 1);
  } else {
#pragma omp task
    quicksort(arr, s, pivot - 1);
  }

  if (pivot + 1 - e < 500) {
    quicksort(arr, pivot + 1, e);
  } else {
#pragma omp task
    quicksort(arr, pivot + 1, e);
  }
}

int *initarr(uint64_t seed, int size, int mod) {
  srand(seed);
  int *arr = malloc(sizeof(int) * size);

  // Is it possible to parallelize this?
  // In size = 1e8 the initalization time is more than 1/3 of the total time!
  for (int i = 0; i < size; i++) {
    arr[i] = rand() % mod;
  }

  return arr;
}

void printarr(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  printf("\n");
}

int main(void) {
  int size = 1e8;
  double start = omp_get_wtime();
  int *arr = initarr(0, size, RAND_MAX);


#pragma omp parallel
#pragma omp single nowait
  quicksort(arr, 0, size - 1);

  double end = omp_get_wtime();

  printf("%f\n", end - start);
  free(arr);
}
