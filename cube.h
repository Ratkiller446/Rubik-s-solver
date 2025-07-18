#ifndef CUBE_H
#define CUBE_H

#include <stdbool.h>

#define CUBE_SIZE 3
#define FACE_COUNT 6
#define SQUARES_PER_FACE 9

// Color definitions
#define WHITE_COLOR  'A'
#define RED_COLOR    'B'
#define BLUE_COLOR   'C'
#define ORANGE_COLOR 'D'
#define GREEN_COLOR  'E'
#define YELLOW_COLOR 'F'

// Face indices
#define FRONT_FACE 0
#define BACK_FACE  1
#define LEFT_FACE  2
#define RIGHT_FACE 3
#define UP_FACE    4
#define DOWN_FACE  5

typedef struct {
    char faces[FACE_COUNT][SQUARES_PER_FACE]; // A-F for colors
    int move_count;
    bool is_solved;
} rubiks_cube_t;

// Cube operations
void cube_init(rubiks_cube_t *cube);
void cube_reset(rubiks_cube_t *cube);
bool cube_is_solved(const rubiks_cube_t *cube);

#endif // CUBE_H
