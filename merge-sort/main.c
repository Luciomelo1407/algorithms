#include <stdio.h>

void printVec(int* vector, int size){
  for(int i = 0; i < size;i++ ){
    if(i+1<size){
      printf("%d, ",vector[i]);
    }else{
      printf("%d\n",vector[i]);
    }
  }
}

void merge(int* vector, int begin, int middle, int end){

  int left_len = middle - begin + 1;
  int right_len =   end - middle;

  int left[left_len];
  int right[right_len];

  for (int i = 0; i < left_len; i++){
    left[i] = vector[begin + i];
  }
  for(int i = 0; i < right_len; i++){
    right[i] = vector[middle + i + 1];
  }
  int i = 0;
  int j = 0;
  
  for(int k = begin; k <= end; k++){
    if(j >= left_len) {
      vector[k] = right[i];
      i++;
    } 
    else if (i >= right_len) {
      vector[k] = left[j];
      j++;
    }
    else if (left[j] <= right[i]) {
      vector[k] = left[j];
      j++;
    }
    else {
      vector[k] = right[i];
      i++;
    }
  }
}

void mergeSort(int* vector, int begin, int end){
  if(begin < end){
    int middle = (begin+end)/2;
    mergeSort(vector,begin, middle);
    mergeSort(vector, middle+1,end);
    merge(vector,begin,middle,end);
  }
}

int main(int argc, char *argv[])
{
  int vector[15] = {99,58,50,60,65,63,8,9,10,1,5,2,6,1,0};
  printVec(vector,15);
  mergeSort(vector,0,14);
  printVec(vector,15);
  return 0;
}
