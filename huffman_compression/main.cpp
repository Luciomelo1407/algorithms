#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int frequency;
  uint8_t symble;
  node *right;
  node *left;
} node;

typedef struct min_p_queue {
  node *nodes[256];
  int size;
} min_p_queue;

min_p_queue *create_queue() {
  min_p_queue *queue = (min_p_queue *)malloc(sizeof(min_p_queue));
  queue->size = 0;
  return queue;
}

int get_dad_index(int i) { return (i - 1) / 2; }

void insert(min_p_queue *queue, int frequency, uint8_t symble, node *left,
            node *right) {
  node *new_node = (node *)malloc(sizeof(node));
  int actual_index = queue->size;
  int dad_index = get_dad_index(actual_index);
  new_node->right = right;
  new_node->left = left;
  new_node->symble = symble;
  new_node->frequency = frequency;
  queue->nodes[actual_index] = new_node;
  node *swap;

  while (actual_index > 0 && (queue->nodes[actual_index]->frequency <
                              queue->nodes[dad_index]->frequency)) {

    swap = queue->nodes[dad_index];
    queue->nodes[dad_index] = queue->nodes[actual_index];
    queue->nodes[actual_index] = swap;

    actual_index = dad_index;
    dad_index = get_dad_index(actual_index);
  }
  queue->size++;
}

void histogram_calc(int hist[], uint8_t *input, int input_len) {

  for (int i = 0; i < input_len; i++) {
    hist[input[i]]++;
  }
}

int left(int i) { return 2 * i + 1; }

int right(int i) { return 2 * i + 2; }

void heapify(node **vector, int size, int dad) {
  int newDad = dad;
  int l = left(dad);
  int r = right(dad);

  if (l < size && vector[l]->frequency < vector[newDad]->frequency) {
    newDad = l;
  }

  if (r < size && vector[r]->frequency < vector[newDad]->frequency) {
    newDad = r;
  }

  if (newDad != dad) {
    node *swap = vector[dad];
    vector[dad] = vector[newDad];
    vector[newDad] = swap;

    heapify(vector, size, newDad);
  }
}

node *extract_min(min_p_queue *queue) {
  node *root = queue->nodes[0];
  queue->nodes[0] = queue->nodes[queue->size - 1];
  queue->size--;
  if (queue->size > 1) {

    heapify(queue->nodes, queue->size, 0);
  }
  return root;
}

node *create_tree(int *histogram, int histogram_len) {
  min_p_queue *queue = create_queue();

  for (int i = 0; i < histogram_len; i++) {
    if (histogram[i]) {
      insert(queue, histogram[i], i, NULL, NULL);
    }
  }

  while (queue->size > 1) {
    node *x = extract_min(queue);
    node *y = extract_min(queue);
    insert(queue, x->frequency + y->frequency, 0, x, y);
  }
  node *root = extract_min(queue);
  free(queue);
  return root;
}

void create_table(node *root, char *table[], char *path, int level) {
  if (root == NULL)
    return;

  if (root->left == NULL && root->right == NULL && level == 0) {
    table[root->symble] = strdup("0");
    return;
  }

  if (root->left == NULL && root->right == NULL) {
    path[level] = '\0';
    table[root->symble] = strdup(path);
    return;
  }

  if (root->left) {
    path[level] = '0';
    create_table(root->left, table, path, level + 1);
  }

  if (root->right) {
    path[level] = '1';
    create_table(root->right, table, path, level + 1);
  }
}

void delete_tree(node *root) {
  if (root == NULL)
    return;
  delete_tree(root->left);
  delete_tree(root->right);
  free(root);
}

void compactar(char *compressed, uint8_t *input, int input_len, char *table) {
  for (int i = 0; i < input_len; i++) {
  }
}

void anexar_bit(uint8_t *compressed, int *bit_pos, char *codigo_huffman) {

  for (int i = 0; codigo_huffman[i] != '\0'; i++) {

    if (codigo_huffman[i] == '1') {

      compressed[*bit_pos / 8] |= (1 << (7 - (*bit_pos % 8)));
    }

    (*bit_pos)++;
  }
}

int huffman_compression_aux(uint8_t *compressed, uint8_t *input, int input_len,
                            char *table[]) {
  int bit_pos = 0;
  for (int i = 0; i < input_len; i++) {
    anexar_bit(compressed, &bit_pos, table[input[i]]);
  }
  return bit_pos;
}

int huffman_compression(uint8_t *compressed, uint8_t *input, int input_len) {
  int histogram[256] = {0};
  histogram_calc(histogram, input, input_len);

  node *huffman_tree = create_tree(histogram, 256);

  char *table[256] = {NULL};
  char path[256];
  create_table(huffman_tree, table, path, 0);

  int bit_pos = huffman_compression_aux(compressed, input, input_len, table);

  int compressed_size = (bit_pos + 7) / 8;
  delete_tree(huffman_tree);
  for (int i = 0; i < 256; i++) {
    if (table[i]) {
      free(table[i]);
    }
  }
  return compressed_size;
}

int main(int argc, char *argv[]) {
  uint8_t input[] = {0xFF, 0xFF, 0xFA, 0xFE, 0xEE, 0xAA, 0xFF, 0xFF, 0xFF};
  int input_len = 9;
  uint8_t compressed[18] = {0};

  int compressed_size = huffman_compression(compressed, input, input_len);

  for (int i = 0; i < compressed_size; i++) {
    printf("%02X", compressed[i]);
  }

  return 0;
}
