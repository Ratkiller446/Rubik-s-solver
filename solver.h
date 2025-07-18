#ifndef SOLVER_H
#define SOLVER_H

#include "cube.h"
#include "moves.h"

#define MAX_MOVES 32

// Optional: Solve the cube (not implemented)
void solver_solve(rubiks_cube_t *cube);

extern cube_move_t g_solution_moves[MAX_MOVES];
extern int g_solution_length;
void apply_moves(rubiks_cube_t *cube, const cube_move_t *moves, int move_count);

#endif // SOLVER_H
