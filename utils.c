#include "utils.h"
#include <stdio.h>
#include "cube.h"
#include <string.h>

void print_error(error_code_t code) {
    switch (code) {
        case ERR_OK:
            break;
        case ERR_INVALID_INPUT:
            fprintf(stderr, "Error: Invalid input.\n");
            break;
        case ERR_MEMORY:
            fprintf(stderr, "Error: Memory allocation failed.\n");
            break;
        case ERR_UNKNOWN:
        default:
            fprintf(stderr, "Error: Unknown error.\n");
            break;
    }
}

void cube_copy(rubiks_cube_t *dest, const rubiks_cube_t *src) {
    memcpy(dest->faces, src->faces, sizeof(src->faces));
    dest->move_count = src->move_count;
    dest->is_solved = src->is_solved;
}

bool cube_equals(const rubiks_cube_t *a, const rubiks_cube_t *b) {
    return memcmp(a->faces, b->faces, sizeof(a->faces)) == 0;
}
