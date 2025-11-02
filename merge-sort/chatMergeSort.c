#include <stdio.h>
#include <stdlib.h>

void printVector(int vector[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d%s", vector[i], (i + 1 < size) ? ", " : "\n");
  }
}

void merge(int vector[], int first, int middle, int last) {
  int leftLen = middle - first + 1;
  int rightLen = last - middle;

  int left[leftLen], right[rightLen];

  for (int i = 0; i < leftLen; i++)
    left[i] = vector[first + i];
  for (int j = 0; j < rightLen; j++)
    right[j] = vector[middle + 1 + j];

  int i = 0, j = 0, k = first;

  while (i < leftLen && j < rightLen) {
    if (left[i] <= right[j])
      vector[k++] = left[i++];
    else
      vector[k++] = right[j++];
  }
  while (i < leftLen)
    vector[k++] = left[i++];
  while (j < rightLen)
    vector[k++] = right[j++];
}

void mergeSort(int vector[], int first, int last) {
  if (first < last) {
    int middle = first + (last - first) / 2;
    mergeSort(vector, first, middle);
    mergeSort(vector, middle + 1, last);
    merge(vector, first, middle, last);
  }
}

int main(void) {
  int vector[3] = {5, 6, 2};
  printVector(vector, 3);
  mergeSort(vector, 0, 2);
  printVector(vector, 3);
  return EXIT_SUCCESS;
}
