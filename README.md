# Algorithms for NP-Hard Sudoku problem using Graph Coloring

In this project, an **heuristic** and an **exact algorithm** using backtracking were implemented to solve the Sudoku problem.

For the heuristic algorithm, the Largest-First heuristic models the game on a graph and uses the Graph Coloring Problem to solve it, using the decreasing order of vertices by degree for graph coloring, iterating between them and coloring with the smallest available color.
## Compilation and Running
1. `cd exact-algorithm/src/` or `cd heuristic/src/`
2. `g++ sudokuSolution.cpp`
3. `./a.out < path_to_database`

## Students:
- Camila Duarte
- Ranna Raabe
