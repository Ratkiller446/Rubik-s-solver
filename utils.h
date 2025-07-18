#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "cube.h"
// Error codes
typedef enum {
    ERR_OK = 0,
    ERR_INVALID_INPUT,
    ERR_MEMORY,
    ERR_UNKNOWN
} error_code_t;

// Utility functions
void print_error(error_code_t code);

// Cube state utilities
void cube_copy(rubiks_cube_t *dest, const rubiks_cube_t *src);
bool cube_equals(const rubiks_cube_t *a, const rubiks_cube_t *b);

#endif // UTILS_H
