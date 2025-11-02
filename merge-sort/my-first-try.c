#include <stdio.h>

void printVec(int* vector, int size){
  for(int i = 0; i<size;i++ ){
    if(i+1<size){
      printf("%d, ",vector[i]);
    }else{
      printf("%d\n",vector[i]);
    }
  }
}







int main(int argc, char *argv[])
{
  int vector[3] = {2,5,6};
  

  return 0;
}

// int* mergeSort(int* vector, int size ){
//   printVec(vector,size);
//   if(size>1){

//     int middle = size/2;
//     
//     if(size%2){
//       mergeSort(vector,middle);
//       mergeSort(vector+middle, middle+1);
//     }else{
//       mergeSort(vector,middle);
//       mergeSort(vector+middle, middle);
//     }
//   }
//   
//   return vector;
// }


