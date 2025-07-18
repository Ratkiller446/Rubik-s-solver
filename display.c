#include "display.h"
#include <stdio.h>

static const char *face_names[6] = {
    "Front", "Back", "Left", "Right", "Up", "Down"
};

void display_legend(void) {
    printf("Color Legend:\n");
    printf("  %c: White\n", WHITE_COLOR);
    printf("  %c: Red\n", RED_COLOR);
    printf("  %c: Blue\n", BLUE_COLOR);
    printf("  %c: Orange\n", ORANGE_COLOR);
    printf("  %c: Green\n", GREEN_COLOR);
    printf("  %c: Yellow\n", YELLOW_COLOR);
}

void display_face(const char *name, const char face[9]) {
    printf("%s:\n", name);
    for (int row = 0; row < 3; ++row) {
        printf("  ");
        for (int col = 0; col < 3; ++col) {
            printf("%c ", face[row * 3 + col]);
        }
        printf("\n");
    }
    printf("\n");
}

void display_cube(const rubiks_cube_t *cube) {
    for (int f = 0; f < 6; ++f) {
        display_face(face_names[f], cube->faces[f]);
    }
}
