# Rubik's Cube Auto-Solver (POSIX C)

## Overview
This project is a fully automatic Rubik's Cube solver written in C, using only POSIX standard libraries. It scrambles a 3x3 cube, displays the scramble and cube state, then solves it using the efficient IDA* (Iterative Deepening A*) algorithm. The solution moves and the solved cube state are shown, with clear ASCII output for all faces.

## Features
- **Automatic scramble and solve**: No user input required.
- **Clear ASCII display**: Each face is labeled and shown as a 3x3 grid.
- **Color legend**: Easy mapping from letters to colors.
- **IDA* algorithm**: Fast, memory-efficient, and finds short solutions.
- **Fun spinner animation** while solving.
- **No memory leaks or crashes** (Valgrind-checked).

## Build Instructions

1. **Navigate to the project directory:**
   ```sh
   cd Rubik-s-solver
   ```
2. **Build (always clean first):**
   ```sh
   make clean && make
   ```


## Example Output
```
Rubik's Cube Auto-Solver (POSIX C)
Color Legend:
  A: White
  B: Red
  C: Blue
  D: Orange
  E: Green
  F: Yellow

Scrambling cube...
Scramble: D L' F R' R L2 D'

Scrambled Cube State:
Front:
  E F F
  E A A
  C C C
Back:
  B B D
  B B D
  E B B
Left:
  F C C
  F C C
  C C F
Right:
  D D D
  E D D
  E A A
Up:
  B E E
  B E E
  B A A
Down:
  D F F
  D F F
  A A A

Solving the cube! Enjoy the spinner while you wait...
Solving
[IDA*] Initial heuristic bound: 3
[IDA*] Increasing bound to 4
[IDA*] Increasing bound to 5
Solution found (IDA* depth 5): D L2 F' L D'

Applying solution moves to cube...
Solution moves: D L2 F' L D'

Solved Cube State:
Front:
  A A A
  A A A
  A A A
Back:
  B B B
  B B B
  B B B
Left:
  C C C
  C C C
  C C C
Right:
  D D D
  D D D
  D D D
Up:
  E E E
  E E E
  E E E
Down:
  F F F
  F F F
  F F F
Color Legend:
  A: White
  B: Red
  C: Blue
  D: Orange
  E: Green
  F: Yellow
Done!
```

## Algorithm
- **IDA\\*** (Iterative Deepening A*):
  - Uses a simple heuristic (misplaced stickers) to guide the search.
  - Prunes redundant moves for speed.
  - Finds short solutions efficiently for 3x3 cubes.

## Credits
- Written by Janne Rovio.
- Uses only POSIX C and standard libraries.
- Inspired by classic cube solvers and the IDA* algorithm.

---

## License
BSD-2 Clause (Janne Rovio)
