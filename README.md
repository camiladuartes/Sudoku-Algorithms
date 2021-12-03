# Heuristic for NP-Hard Sudoku problem using Graph Coloring

In this work, the Largest-First heuristic was implemented to solve the Sudoku problem.

This heuristic models the game on a graph and uses the Graph Coloring Problem to solve it, using the decreasing order of vertices by degree for graph coloring, iterating between them and coloring with the smallest available color.

## Student:

Camila Duarte.

## Compilation (with CMake):
1. `mkdir build`
2. `cd build`
3. `cmake -G "Unix Makefiles" ..`
4. `make`

## Running the driver containing the tests with `assert`:
1. `./sudokuLFMain`
