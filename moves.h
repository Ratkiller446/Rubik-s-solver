#ifndef MOVES_H
#define MOVES_H

#include "cube.h"

// Standard Rubik's cube move notation
// F, B, L, R, U, D, F', B', L', R', U', D', F2, B2, L2, R2, U2, D2

typedef enum {
    MOVE_F, MOVE_F_PRIME, MOVE_F2,
    MOVE_B, MOVE_B_PRIME, MOVE_B2,
    MOVE_L, MOVE_L_PRIME, MOVE_L2,
    MOVE_R, MOVE_R_PRIME, MOVE_R2,
    MOVE_U, MOVE_U_PRIME, MOVE_U2,
    MOVE_D, MOVE_D_PRIME, MOVE_D2,
    MOVE_INVALID
} cube_move_t;

// Move execution
void move_apply(rubiks_cube_t *cube, cube_move_t move);

// Move parsing
cube_move_t move_parse(const char *str);

#endif // MOVES_H
