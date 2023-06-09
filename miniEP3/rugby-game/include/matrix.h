#ifndef MATRIX_H
#define MATRIX_H

#include "position.h"

position_t ** new_position_matrix(size_t height, size_t width, position_t position);

int ** new_int_matrix(size_t height, size_t width, int initial_value);

void free_matrix(size_t height, void **matrix);

#endif