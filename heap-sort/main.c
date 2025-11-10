#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#define VECSIZ = 5;

int *generateVector(int size) {
  srand(time(NULL));
  int *vector = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;
  }
  return vector;
}

void printVec(int *vector, int size) {
  for (int i = 0; i < size; i++) {
    if (i + 1 < size) {
      printf("%d, ", vector[i]);
    } else {
      printf("%d\n", vector[i]);
    }
  }
}

int left(int i) { return 2 * i + 1; }

int right(int i) { return 2 * i + 2; }

void heapify(int *vector, int size, int dad) {
  int newDad = dad;
  int l = left(dad);
  int r = right(dad);

  if (l < size && vector[l] > vector[newDad]) {
    newDad = l;
  }

  if (r < size && vector[r] > vector[newDad]) {
    newDad = r;
  }

  if (newDad != dad) {
    int swap = vector[dad];
    vector[dad] = vector[newDad];
    vector[newDad] = swap;

    heapify(vector, size, newDad);
  }
}

void build_heap(int *vector, int size) {
  for (int i = (size / 2) - 1; i >= 0; i--) {
    heapify(vector, size, i);
  }
}

void heapSort(int *vector, int size) {
  int swap = 0;

  build_heap(vector, size);

  for (int i = size - 1; i > 0; i--) {
    swap = vector[0];
    vector[0] = vector[i];
    vector[i] = swap;

    heapify(vector, i, 0);
  }
}

int main(int argc, char *argv[]) {
  int size = 5;
  int *vector = generateVector(size);

  printf("Original vector: ");
  printVec(vector, size);

  heapSort(vector, size);

  printf("Sorted vector:   ");
  printVec(vector, size);

  free(vector);
  return 0;
}
