#include <stdio.h>
#define EXIT_SUCCESS 0;

int binary_search(int* vector,int element, int begin, int end){
  int middle = (begin + end)/2;
  if(begin < end){
    if(element == vector[middle]){
      return middle;
    }
    if(element < vector[middle]){
      return binary_search(vector, element, 0, middle);
    }
    if(element > vector[middle]){
      return binary_search(vector, element, middle+1, end);
    }
  }
  return -1;
}

int main(int argc, char *argv[])
{
  int vector[15] = {0, 1, 1, 2, 5, 6, 8, 9, 10, 50, 58, 60, 63, 65, 99};
  printf("%d",binary_search(vector, 6, 0, 14));
  return EXIT_SUCCESS;
}

