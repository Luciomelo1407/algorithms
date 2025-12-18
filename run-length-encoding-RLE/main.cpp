
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>

int rle(uint8_t *target, uint8_t target_len, uint8_t *compressed) {

  uint8_t caracter = target[0];
  uint8_t counter = 1;
  int cursor = 0;

  for (int i = 1; i < target_len; i++) {
    if (target[i] == caracter) {
      counter++;
    } else {
      compressed[cursor++] = counter;
      compressed[cursor++] = caracter;
      caracter = target[i];
      counter = 1;
    }
  }

  // último grupo
  compressed[cursor++] = counter;
  compressed[cursor++] = caracter;

  return cursor;
}

int main() {
  uint8_t input[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  int input_len = 9;
  uint8_t compressed[18];

  int compressed_len = rle(input, input_len, compressed);

  for (int i = 0; i < compressed_len; i++) {
    printf("%02X ", compressed[i]);
  }

  std::cout << "\n"
            << "compress ratio:"
            << (double)compressed_len * 100 / (double)input_len;
}
