#include <math.h>
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

uint64_t powMod(uint64_t a, uint64_t b, uint64_t mod, uint64_t **buf) {
  if (b == 0) {
    return 1;
  }

  uint64_t size = pow(2, floor(log2(b)));
  *buf = malloc(sizeof(uint64_t) * size);
  int buf_it = 0;

  uint64_t bi = 1;
  uint64_t ai = a;

  (*buf)[buf_it++] = a;

  while (bi != size) {
    ai = (ai * ai) % mod;
    (*buf)[buf_it++] = ai;
    bi *= 2;
  }

  while (bi != b) {
    uint64_t pot = floor(log2(b - bi));
    ai = (ai * (*buf)[pot]) % mod;
    bi += pow(2, pot);
  }

  return ai;
}

uint64_t a = 0x5DEECE66D;
uint64_t c = 11;
uint64_t m = (uint64_t)1 << 48;
uint64_t last_random = 0;
#pragma omp threadprivate(last_random)

void setSeed(uint64_t seed) { last_random = seed; }

uint64_t getRandom() {
  last_random = (last_random * a + c) % m;
  return last_random;
}

int *initarr(uint64_t seed, int size, int mod) {
  int *arr = malloc(sizeof(int) * size);
  setSeed(seed);

#pragma omp parallel copyin(last_random)
  {
    int id = omp_get_thread_num();
    int threads = omp_get_num_threads();

    for (int i = 0; i < id + 1; i++) {
      arr[id] = getRandom() % mod;
    }

#pragma omp barrier
#pragma omp single
    {
      uint64_t *exponents;
      a = powMod(a, threads, m, &exponents);

      for (int i = 0; i < log2(threads); i++) {
        c = (c * (exponents[i] + 1)) % m;
      }

      free(exponents);
    }

    for (int i = id + threads; i < size; i += threads) {
      arr[i] = getRandom() % mod;
    }
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
