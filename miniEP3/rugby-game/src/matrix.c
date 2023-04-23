#include <stdlib.h>
#include "position.h"

position_t ** new_position_matrix(size_t height, size_t width, position_t position) {
  position_t **matrix = malloc(height * sizeof(position_t*));

  for (size_t i = 0; i < height; i++) {
    matrix[i] = malloc(width * sizeof(position_t));

    for (size_t j = 0; j < width; j++) {
      matrix[i][j] = position;
    }
  }

  return matrix;
}

int ** new_int_matrix(size_t height, size_t width, int initial_value) {
  int **matrix = malloc(height * sizeof(int*));

  for (size_t i = 0; i < height; i++) {
    matrix[i] = malloc(width * sizeof(int));

    for (size_t j = 0; j < width; j++) {
      matrix[i][j] = initial_value;
    }
  }

  return matrix;
}

void free_matrix(size_t height, void **matrix) {
  for (size_t i = 0; i < height; i++)
    free(matrix[i]);

  free(matrix);
}