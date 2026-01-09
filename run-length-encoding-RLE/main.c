#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int rle(uint8_t *target, int target_len, uint8_t *compressed) {
  if (target_len == 0)
    return 0;

  uint8_t caracter = target[0];

  int counter = 1;
  int cursor = 0;

  for (int i = 1; i < target_len; i++) {
    if (target[i] == caracter && counter < 255) {
      counter++;
    } else {
      compressed[cursor++] = (uint8_t)counter;
      compressed[cursor++] = caracter;
      caracter = target[i];
      counter = 1;
    }
  }
  compressed[cursor++] = (uint8_t)counter;
  compressed[cursor++] = caracter;

  return cursor;
}

void println(char *texto) { printf("%s\n", texto); }

void printVector(uint8_t *input, int input_len) {
  for (int j = 0; j < input_len; j++) {
    printf("%02X ", input[j]);
  }
  println("");
}

void writeVecInFile(FILE *out, uint8_t *input, int input_len) {

  for (int j = 0; j < input_len; j++) {
    fprintf(out, "%02X", input[j]);
  }
  fprintf(out, "\n");
}

void writeRLELabel(FILE *out, int pos, float compressRatio) {
  fprintf(out, "%d->RLE(%0.2f%%)=", pos, compressRatio);
}

int main(int argc, char *argv[]) {

  FILE *file_in;
  file_in = fopen(argv[1], "r");
  if (!file_in) {
    println("Erro ao tentar abrir o arquivo de input");
    return -1;
  }

  FILE *file_out;
  file_out = fopen(argv[2], "w+");

  uint8_t *input = (uint8_t *)malloc(sizeof(uint8_t) * 10000);
  int input_len = 0;
  int total_input = 0;

  int rleOutputLen = 0;
  uint8_t *rleOutput = (uint8_t *)malloc(sizeof(uint8_t) * 10000 * 2);

  float compressRatio = 0;

  fscanf(file_in, "%d", &total_input);
  for (int i = 0; i < total_input; i++) {
    fscanf(file_in, "%d", &input_len);
    for (int j = 0; j < input_len; j++) {
      fscanf(file_in, "%hhX", &input[j]);
    }

    // printVector(input, input_len);

    rleOutputLen = rle(input, input_len, rleOutput);

    compressRatio = (float)rleOutputLen * 100.0 / (float)input_len;

    writeRLELabel(file_out, i, compressRatio);
    writeVecInFile(file_out, rleOutput, rleOutputLen);
  }

  return EXIT_SUCCESS;
}
