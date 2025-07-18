#include "input.h"
#include <stdio.h>
#include <string.h>

cube_move_t input_read_move(void) {
    char buf[8];
    if (!fgets(buf, sizeof(buf), stdin)) return MOVE_INVALID;
    // Remove trailing newline
    buf[strcspn(buf, "\r\n")] = 0;
    return move_parse(buf);
}
