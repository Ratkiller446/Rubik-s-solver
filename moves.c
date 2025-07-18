#include "moves.h"
#include <string.h>
#include <stdio.h>

// Helper to rotate a face clockwise
static void rotate_face_clockwise(char face[9]) {
    char tmp[9];
    for (int i = 0; i < 9; ++i) tmp[i] = face[i];
    face[0] = tmp[6]; face[1] = tmp[3]; face[2] = tmp[0];
    face[3] = tmp[7]; face[4] = tmp[4]; face[5] = tmp[1];
    face[6] = tmp[8]; face[7] = tmp[5]; face[8] = tmp[2];
}

// Helper to rotate a face counterclockwise
static void rotate_face_counterclockwise(char face[9]) {
    char tmp[9];
    for (int i = 0; i < 9; ++i) tmp[i] = face[i];
    face[0] = tmp[2]; face[1] = tmp[5]; face[2] = tmp[8];
    face[3] = tmp[1]; face[4] = tmp[4]; face[5] = tmp[7];
    face[6] = tmp[0]; face[7] = tmp[3]; face[8] = tmp[6];
}

// Helper to rotate a face 180 degrees
static void rotate_face_180(char face[9]) {
    char tmp[9];
    for (int i = 0; i < 9; ++i) tmp[i] = face[i];
    face[0] = tmp[8]; face[1] = tmp[7]; face[2] = tmp[6];
    face[3] = tmp[5]; face[4] = tmp[4]; face[5] = tmp[3];
    face[6] = tmp[2]; face[7] = tmp[1]; face[8] = tmp[0];
}

// Helper to rotate a row of 3 elements
static void rotate_row(char *a, char *b, char *c, char *d, int times) {
    char tmp[3];
    for (int t = 0; t < times; ++t) {
        tmp[0] = a[0]; tmp[1] = a[1]; tmp[2] = a[2];
        a[0] = d[0]; a[1] = d[1]; a[2] = d[2];
        d[0] = c[0]; d[1] = c[1]; d[2] = c[2];
        c[0] = b[0]; c[1] = b[1]; c[2] = b[2];
        b[0] = tmp[0]; b[1] = tmp[1]; b[2] = tmp[2];
    }
}

// F face: U->R->D->L
static void rotate_F_edges(rubiks_cube_t *cube, int times) {
    for (int t = 0; t < times; ++t) {
        char tmp[3];
        // Save U 6,7,8
        tmp[0] = cube->faces[UP_FACE][6];
        tmp[1] = cube->faces[UP_FACE][7];
        tmp[2] = cube->faces[UP_FACE][8];
        // U 6,7,8 <- L 8,5,2
        cube->faces[UP_FACE][6] = cube->faces[LEFT_FACE][8];
        cube->faces[UP_FACE][7] = cube->faces[LEFT_FACE][5];
        cube->faces[UP_FACE][8] = cube->faces[LEFT_FACE][2];
        // L 8,5,2 <- D 2,1,0
        cube->faces[LEFT_FACE][8] = cube->faces[DOWN_FACE][2];
        cube->faces[LEFT_FACE][5] = cube->faces[DOWN_FACE][1];
        cube->faces[LEFT_FACE][2] = cube->faces[DOWN_FACE][0];
        // D 2,1,0 <- R 0,3,6
        cube->faces[DOWN_FACE][2] = cube->faces[RIGHT_FACE][0];
        cube->faces[DOWN_FACE][1] = cube->faces[RIGHT_FACE][3];
        cube->faces[DOWN_FACE][0] = cube->faces[RIGHT_FACE][6];
        // R 0,3,6 <- tmp
        cube->faces[RIGHT_FACE][0] = tmp[0];
        cube->faces[RIGHT_FACE][3] = tmp[1];
        cube->faces[RIGHT_FACE][6] = tmp[2];
    }
}
// B face: U 2,1,0 -> R 8,5,2 -> D 6,7,8 -> L 0,3,6
static void rotate_B_edges(rubiks_cube_t *cube, int times) {
    for (int t = 0; t < times; ++t) {
        char tmp[3];
        tmp[0] = cube->faces[UP_FACE][2];
        tmp[1] = cube->faces[UP_FACE][1];
        tmp[2] = cube->faces[UP_FACE][0];
        cube->faces[UP_FACE][2] = cube->faces[LEFT_FACE][0];
        cube->faces[UP_FACE][1] = cube->faces[LEFT_FACE][3];
        cube->faces[UP_FACE][0] = cube->faces[LEFT_FACE][6];
        cube->faces[LEFT_FACE][0] = cube->faces[DOWN_FACE][6];
        cube->faces[LEFT_FACE][3] = cube->faces[DOWN_FACE][7];
        cube->faces[LEFT_FACE][6] = cube->faces[DOWN_FACE][8];
        cube->faces[DOWN_FACE][6] = cube->faces[RIGHT_FACE][8];
        cube->faces[DOWN_FACE][7] = cube->faces[RIGHT_FACE][5];
        cube->faces[DOWN_FACE][8] = cube->faces[RIGHT_FACE][2];
        cube->faces[RIGHT_FACE][8] = tmp[0];
        cube->faces[RIGHT_FACE][5] = tmp[1];
        cube->faces[RIGHT_FACE][2] = tmp[2];
    }
}
// L face: U 0,3,6 -> B 8,5,2 -> D 0,3,6 -> F 0,3,6
static void rotate_L_edges(rubiks_cube_t *cube, int times) {
    for (int t = 0; t < times; ++t) {
        char tmp[3];
        tmp[0] = cube->faces[UP_FACE][0];
        tmp[1] = cube->faces[UP_FACE][3];
        tmp[2] = cube->faces[UP_FACE][6];
        cube->faces[UP_FACE][0] = cube->faces[BACK_FACE][8];
        cube->faces[UP_FACE][3] = cube->faces[BACK_FACE][5];
        cube->faces[UP_FACE][6] = cube->faces[BACK_FACE][2];
        cube->faces[BACK_FACE][8] = cube->faces[DOWN_FACE][0];
        cube->faces[BACK_FACE][5] = cube->faces[DOWN_FACE][3];
        cube->faces[BACK_FACE][2] = cube->faces[DOWN_FACE][6];
        cube->faces[DOWN_FACE][0] = cube->faces[FRONT_FACE][0];
        cube->faces[DOWN_FACE][3] = cube->faces[FRONT_FACE][3];
        cube->faces[DOWN_FACE][6] = cube->faces[FRONT_FACE][6];
        cube->faces[FRONT_FACE][0] = tmp[0];
        cube->faces[FRONT_FACE][3] = tmp[1];
        cube->faces[FRONT_FACE][6] = tmp[2];
    }
}
// R face: U 8,5,2 -> F 8,5,2 -> D 8,5,2 -> B 0,3,6
static void rotate_R_edges(rubiks_cube_t *cube, int times) {
    for (int t = 0; t < times; ++t) {
        char tmp[3];
        tmp[0] = cube->faces[UP_FACE][8];
        tmp[1] = cube->faces[UP_FACE][5];
        tmp[2] = cube->faces[UP_FACE][2];
        cube->faces[UP_FACE][8] = cube->faces[FRONT_FACE][8];
        cube->faces[UP_FACE][5] = cube->faces[FRONT_FACE][5];
        cube->faces[UP_FACE][2] = cube->faces[FRONT_FACE][2];
        cube->faces[FRONT_FACE][8] = cube->faces[DOWN_FACE][8];
        cube->faces[FRONT_FACE][5] = cube->faces[DOWN_FACE][5];
        cube->faces[FRONT_FACE][2] = cube->faces[DOWN_FACE][2];
        cube->faces[DOWN_FACE][8] = cube->faces[BACK_FACE][0];
        cube->faces[DOWN_FACE][5] = cube->faces[BACK_FACE][3];
        cube->faces[DOWN_FACE][2] = cube->faces[BACK_FACE][6];
        cube->faces[BACK_FACE][0] = tmp[0];
        cube->faces[BACK_FACE][3] = tmp[1];
        cube->faces[BACK_FACE][6] = tmp[2];
    }
}
// U face: B 2,1,0 -> R 2,1,0 -> F 2,1,0 -> L 2,1,0
static void rotate_U_edges(rubiks_cube_t *cube, int times) {
    for (int t = 0; t < times; ++t) {
        char tmp[3];
        tmp[0] = cube->faces[BACK_FACE][2];
        tmp[1] = cube->faces[BACK_FACE][1];
        tmp[2] = cube->faces[BACK_FACE][0];
        cube->faces[BACK_FACE][2] = cube->faces[RIGHT_FACE][2];
        cube->faces[BACK_FACE][1] = cube->faces[RIGHT_FACE][1];
        cube->faces[BACK_FACE][0] = cube->faces[RIGHT_FACE][0];
        cube->faces[RIGHT_FACE][2] = cube->faces[FRONT_FACE][2];
        cube->faces[RIGHT_FACE][1] = cube->faces[FRONT_FACE][1];
        cube->faces[RIGHT_FACE][0] = cube->faces[FRONT_FACE][0];
        cube->faces[FRONT_FACE][2] = cube->faces[LEFT_FACE][2];
        cube->faces[FRONT_FACE][1] = cube->faces[LEFT_FACE][1];
        cube->faces[FRONT_FACE][0] = cube->faces[LEFT_FACE][0];
        cube->faces[LEFT_FACE][2] = tmp[0];
        cube->faces[LEFT_FACE][1] = tmp[1];
        cube->faces[LEFT_FACE][0] = tmp[2];
    }
}
// D face: F 6,7,8 -> R 6,7,8 -> B 6,7,8 -> L 6,7,8
static void rotate_D_edges(rubiks_cube_t *cube, int times) {
    for (int t = 0; t < times; ++t) {
        char tmp[3];
        tmp[0] = cube->faces[FRONT_FACE][6];
        tmp[1] = cube->faces[FRONT_FACE][7];
        tmp[2] = cube->faces[FRONT_FACE][8];
        cube->faces[FRONT_FACE][6] = cube->faces[RIGHT_FACE][6];
        cube->faces[FRONT_FACE][7] = cube->faces[RIGHT_FACE][7];
        cube->faces[FRONT_FACE][8] = cube->faces[RIGHT_FACE][8];
        cube->faces[RIGHT_FACE][6] = cube->faces[BACK_FACE][6];
        cube->faces[RIGHT_FACE][7] = cube->faces[BACK_FACE][7];
        cube->faces[RIGHT_FACE][8] = cube->faces[BACK_FACE][8];
        cube->faces[BACK_FACE][6] = cube->faces[LEFT_FACE][6];
        cube->faces[BACK_FACE][7] = cube->faces[LEFT_FACE][7];
        cube->faces[BACK_FACE][8] = cube->faces[LEFT_FACE][8];
        cube->faces[LEFT_FACE][6] = tmp[0];
        cube->faces[LEFT_FACE][7] = tmp[1];
        cube->faces[LEFT_FACE][8] = tmp[2];
    }
}

void move_apply(rubiks_cube_t *cube, cube_move_t move) {
    switch (move) {
        case MOVE_F: rotate_face_clockwise(cube->faces[FRONT_FACE]); rotate_F_edges(cube, 1); break;
        case MOVE_F_PRIME: rotate_face_counterclockwise(cube->faces[FRONT_FACE]); rotate_F_edges(cube, 3); break;
        case MOVE_F2: rotate_face_180(cube->faces[FRONT_FACE]); rotate_F_edges(cube, 2); break;
        case MOVE_B: rotate_face_clockwise(cube->faces[BACK_FACE]); rotate_B_edges(cube, 1); break;
        case MOVE_B_PRIME: rotate_face_counterclockwise(cube->faces[BACK_FACE]); rotate_B_edges(cube, 3); break;
        case MOVE_B2: rotate_face_180(cube->faces[BACK_FACE]); rotate_B_edges(cube, 2); break;
        case MOVE_L: rotate_face_clockwise(cube->faces[LEFT_FACE]); rotate_L_edges(cube, 1); break;
        case MOVE_L_PRIME: rotate_face_counterclockwise(cube->faces[LEFT_FACE]); rotate_L_edges(cube, 3); break;
        case MOVE_L2: rotate_face_180(cube->faces[LEFT_FACE]); rotate_L_edges(cube, 2); break;
        case MOVE_R: rotate_face_clockwise(cube->faces[RIGHT_FACE]); rotate_R_edges(cube, 1); break;
        case MOVE_R_PRIME: rotate_face_counterclockwise(cube->faces[RIGHT_FACE]); rotate_R_edges(cube, 3); break;
        case MOVE_R2: rotate_face_180(cube->faces[RIGHT_FACE]); rotate_R_edges(cube, 2); break;
        case MOVE_U: rotate_face_clockwise(cube->faces[UP_FACE]); rotate_U_edges(cube, 1); break;
        case MOVE_U_PRIME: rotate_face_counterclockwise(cube->faces[UP_FACE]); rotate_U_edges(cube, 3); break;
        case MOVE_U2: rotate_face_180(cube->faces[UP_FACE]); rotate_U_edges(cube, 2); break;
        case MOVE_D: rotate_face_clockwise(cube->faces[DOWN_FACE]); rotate_D_edges(cube, 1); break;
        case MOVE_D_PRIME: rotate_face_counterclockwise(cube->faces[DOWN_FACE]); rotate_D_edges(cube, 3); break;
        case MOVE_D2: rotate_face_180(cube->faces[DOWN_FACE]); rotate_D_edges(cube, 2); break;
        default: break;
    }
}

cube_move_t move_parse(const char *str) {
    if (!str) return MOVE_INVALID;
    if (strcmp(str, "F") == 0) return MOVE_F;
    if (strcmp(str, "F'") == 0) return MOVE_F_PRIME;
    if (strcmp(str, "F2") == 0) return MOVE_F2;
    if (strcmp(str, "B") == 0) return MOVE_B;
    if (strcmp(str, "B'") == 0) return MOVE_B_PRIME;
    if (strcmp(str, "B2") == 0) return MOVE_B2;
    if (strcmp(str, "L") == 0) return MOVE_L;
    if (strcmp(str, "L'") == 0) return MOVE_L_PRIME;
    if (strcmp(str, "L2") == 0) return MOVE_L2;
    if (strcmp(str, "R") == 0) return MOVE_R;
    if (strcmp(str, "R'") == 0) return MOVE_R_PRIME;
    if (strcmp(str, "R2") == 0) return MOVE_R2;
    if (strcmp(str, "U") == 0) return MOVE_U;
    if (strcmp(str, "U'") == 0) return MOVE_U_PRIME;
    if (strcmp(str, "U2") == 0) return MOVE_U2;
    if (strcmp(str, "D") == 0) return MOVE_D;
    if (strcmp(str, "D'") == 0) return MOVE_D_PRIME;
    if (strcmp(str, "D2") == 0) return MOVE_D2;
    return MOVE_INVALID;
}
