#include "cube.h"
#include "display.h"
#include "moves.h"
#include "solver.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SCRAMBLE_MOVES 7

void scramble_cube(rubiks_cube_t *cube, cube_move_t *scramble_seq, int moves) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < moves; ++i) {
        cube_move_t m = (cube_move_t)(rand() % (MOVE_INVALID));
        move_apply(cube, m);
        scramble_seq[i] = m;
    }
}

void print_scramble(const cube_move_t *scramble_seq, int moves) {
    printf("Scramble: ");
    for (int i = 0; i < moves; ++i) {
        switch (scramble_seq[i]) {
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
}

void fun_spinner(const char *msg, int duration_sec) {
    const char spin[] = "|/-\\";
    int spin_len = 4;
    int steps = duration_sec * 10;
    printf("%s ", msg);
    fflush(stdout);
    for (int i = 0; i < steps; ++i) {
        printf("%c\b", spin[i % spin_len]);
        fflush(stdout);
        usleep(100000); // 0.1s
    }
    printf(" \n");
}

int main(void) {
    rubiks_cube_t cube;
    cube_init(&cube);
    cube_move_t scramble_seq[SCRAMBLE_MOVES];

    printf("Rubik's Cube Auto-Solver (POSIX C)\n");
    display_legend();
    printf("\nScrambling cube...\n");
    scramble_cube(&cube, scramble_seq, SCRAMBLE_MOVES);
    print_scramble(scramble_seq, SCRAMBLE_MOVES);
    printf("\nScrambled Cube State:\n");
    display_cube(&cube);

    printf("\nSolving the cube! Enjoy the spinner while you wait...\n");
    fun_spinner("Solving", 2);
    solver_solve(&cube);
    if (g_solution_length > 0) {
        printf("\nApplying solution moves to cube...\n");
        apply_moves(&cube, g_solution_moves, g_solution_length);
        printf("Solution moves: ");
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
    }
    printf("\nSolved Cube State:\n");
    display_cube(&cube);
    display_legend();
    printf("Done!\n");
    return 0;
}
