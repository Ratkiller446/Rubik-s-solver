#include "cube.h"
#include <string.h>

void cube_init(rubiks_cube_t *cube) {
    // Initialize each face with its color
    char colors[FACE_COUNT] = {WHITE_COLOR, RED_COLOR, BLUE_COLOR, ORANGE_COLOR, GREEN_COLOR, YELLOW_COLOR};
    for (int f = 0; f < FACE_COUNT; ++f) {
        for (int i = 0; i < SQUARES_PER_FACE; ++i) {
            cube->faces[f][i] = colors[f];
        }
    }
    cube->move_count = 0;
    cube->is_solved = true;
}

void cube_reset(rubiks_cube_t *cube) {
    cube_init(cube);
}

bool cube_is_solved(const rubiks_cube_t *cube) {
    for (int f = 0; f < FACE_COUNT; ++f) {
        char color = cube->faces[f][0];
        for (int i = 1; i < SQUARES_PER_FACE; ++i) {
            if (cube->faces[f][i] != color) {
                return false;
            }
        }
    }
    return true;
}
