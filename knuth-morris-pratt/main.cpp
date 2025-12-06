#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

int *build_transition_table(char *pattern) {
  int *transition_table = (int *)malloc(strlen(pattern) * sizeof(int));
  memset(transition_table, -1, strlen(pattern) * sizeof(int));
  int pattern_size = strlen(pattern);
  for (int i = 1, j = -1; i < pattern_size; i++) {
    while (j >= 0 && pattern[j + 1] != pattern[i]) {
      j = transition_table[j];
    }
    if (pattern[j + 1] == pattern[i]) {
      j++;
    }
    transition_table[i] = j;
  }
  return transition_table;
}

int *KMP(char *string, char *pattern) {
  int *pattern_indexs = (int *)malloc(sizeof(int) * strlen(string));
  memset(pattern_indexs, -1, strlen(string) * sizeof(int));
  int string_size = strlen(string), patttern_size = strlen(pattern),
      size_pattern_indexs = 0;
  int *transition_table = build_transition_table(pattern);

  for (int i = 0, j = -1; i < string_size; i++) {
    while (j >= 0 && pattern[j + 1] != string[i]) {
      j = transition_table[j];
    }
    if (pattern[j + 1] == string[i]) {
      j++;
    }
    if (j == patttern_size - 1) {
      pattern_indexs[size_pattern_indexs] = i - patttern_size + 1;
      size_pattern_indexs++;
      j = transition_table[j];
    }
  }
  free(transition_table);
  return pattern_indexs;
}

int main(int argc, char *argv[]) {
  char pattern[] = "babaca";
  char string[] = "babacababaebabacaaacabafaebabacallbacasbabbabacaacaefababaeb"
                  "abacafasecabasefabacabelbacaaasef";
  int *pattern_indexs = KMP(string, pattern);
  for (int i = 0; pattern_indexs[i] != -1; i++) {
    cout << pattern_indexs[i] << ",";
  }
  free(pattern_indexs);

  return 0;
}
