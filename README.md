# Algorithms for NP-Hard Sudoku problem using Graph Coloring

In this project, an **heuristic** and an **exact algorithm** using backtracking were implemented to solve the Sudoku problem.

For the heuristic algorithm, the Largest-First heuristic models the game on a graph and uses the Graph Coloring Problem to solve it, using the decreasing order of vertices by degree for graph coloring, iterating between them and coloring with the smallest available color.

## Compilation (with CMake):
1. `mkdir build`
2. `cd build`
3. `cmake -G "Unix Makefiles" ..`
4. `make`

## Running Main containing some tests:
- `./sudokuLFMain < path_to_database` to excute approximation algorithm;
- `./sudokuSkiena < path_to_database` to excute Skiena exact algorithm;

## Students:
- Camila Duarte
- Ranna Raabe
