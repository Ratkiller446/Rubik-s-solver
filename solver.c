#include "solver.h"
#include "moves.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVES 32
#define MAX_DEPTH 20

cube_move_t g_solution_moves[MAX_MOVES];
int g_solution_length = 0;

// Heuristic: number of misplaced stickers (not matching center color)
static int heuristic(const rubiks_cube_t *cube) {
    int misplaced = 0;
    for (int f = 0; f < FACE_COUNT; ++f) {
        char center = cube->faces[f][4];
        for (int i = 0; i < SQUARES_PER_FACE; ++i) {
            if (cube->faces[f][i] != center) misplaced++;
        }
    }
    return misplaced / 8; // scale down for IDA* (tune as needed)
}

// Prune: don't allow same face or opposite move as previous
static int is_prune(cube_move_t prev, cube_move_t curr) {
    if (prev == MOVE_INVALID) return 0;
    // Same face
    if (prev / 3 == curr / 3) return 1;
    // Opposite move (e.g., F and F')
    if ((prev / 3 == curr / 3) && ((prev + curr) % 3 == 1)) return 1;
    return 0;
}

static int ida_search(rubiks_cube_t *cube, int depth, int bound, cube_move_t *moves, int move_count, cube_move_t prev_move) {
    int h = heuristic(cube);
    int f = move_count + h;
    if (f > bound) return f;
    if (cube_is_solved(cube)) {
        memcpy(g_solution_moves, moves, sizeof(cube_move_t) * move_count);
        g_solution_length = move_count;
        return -1; // found
    }
    int min = 1000000;
    for (cube_move_t m = MOVE_F; m < MOVE_INVALID; ++m) {
        if (is_prune(prev_move, m)) continue;
        rubiks_cube_t next;
        cube_copy(&next, cube);
        move_apply(&next, m);
        moves[move_count] = m;
        int t = ida_search(&next, depth + 1, bound, moves, move_count + 1, m);
        if (t == -1) return -1; // found
        if (t < min) min = t;
    }
    return min;
}

void solver_solve(rubiks_cube_t *start) {
    g_solution_length = 0;
    cube_move_t moves[MAX_MOVES];
    int bound = heuristic(start);
    int found = 0;
    printf("[IDA*] Initial heuristic bound: %d\n", bound);
    while (bound <= MAX_DEPTH) {
        int t = ida_search(start, 0, bound, moves, 0, MOVE_INVALID);
        if (t == -1) {
            printf("Solution found (IDA* depth %d): ", g_solution_length);
            for (int i = 0; i < g_solution_length; ++i) {
                switch (g_solution_moves[i]) {
                    case MOVE_F: printf("F "); break;
                    case MOVE_F_PRIME: printf("F' "); break;
                    case MOVE_F2: printf("F2 "); break;
                    case MOVE_B: printf("B "); break;
                    case MOVE_B_PRIME: printf("B' "); break;
                    case MOVE_B2: printf("B2 "); break;
                    case MOVE_L: printf("L "); break;
                    case MOVE_L_PRIME: printf("L' "); break;
                    case MOVE_L2: printf("L2 "); break;
                    case MOVE_R: printf("R "); break;
                    case MOVE_R_PRIME: printf("R' "); break;
                    case MOVE_R2: printf("R2 "); break;
                    case MOVE_U: printf("U "); break;
                    case MOVE_U_PRIME: printf("U' "); break;
                    case MOVE_U2: printf("U2 "); break;
                    case MOVE_D: printf("D "); break;
                    case MOVE_D_PRIME: printf("D' "); break;
                    case MOVE_D2: printf("D2 "); break;
                    default: break;
                }
            }
            printf("\n");
            found = 1;
            break;
        }
        if (t > MAX_DEPTH) break;
        bound = t;
        printf("[IDA*] Increasing bound to %d\n", bound);
    }
    if (!found) {
        printf("No solution found within depth limit (%d).\n", MAX_DEPTH);
        g_solution_length = 0;
    }
}

void apply_moves(rubiks_cube_t *cube, const cube_move_t *moves, int move_count) {
    for (int i = 0; i < move_count; ++i) {
        move_apply(cube, moves[i]);
    }
}
