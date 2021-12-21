#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include "../include/largestFirst.h"
#include "../include/util.h"
using namespace std;

int main() {
    string sudokuString = "153000000000700900000254800006070284405080010009001360074000000030600027862590043";
    vector<int> sudokuList = {};

    cout << "\n>>> Testing developed methods:\n\n";

    ut::convert(sudokuString, sudokuList); //OK!

    cout << "Sudoku puzzle:\n";
    ut::printSudokuList(sudokuList); cout << endl; // OK!

    cout << "Is this Sudoku puzzle fully collored? " << (ut::isColored(sudokuList) ? "Yes" : "No") << "\n\n"; // OK!

    vector<int> test = {0,0,0,1,2,3,0,0,4};
    cout << "Is 2 in list [0,0,0,1,2,3,0,0,4]? " << (ut::inList(2, test)  ? "Yes" : "No") << "\n\n"; // OK!

    map<int, vector<int>> sudokuGraph;
    for(int i = 0; i < 81; i++) {
        sudokuGraph[i] = ut::adjacencyList(i); // OK!
    }
    // printSudokuAdjList(sudokuGraph); // OK!

    vector<int> orderedByDegree = lf::UncoloredVerticesOrderedByDegree(sudokuGraph, sudokuList); // OK!
    cout << "Uncolored vertices ordered by degree: \n[";
    ut::printSudokuList(orderedByDegree);
    cout << "]\n\n";

    vector<int> forbiddenColorsTest = lf::getForbiddenColors(10, sudokuGraph, sudokuList); // OK!
    cout << "Forbidden colors list of position '10': [";
    ut::printSudokuList(forbiddenColorsTest);
    cout << "]\n\n";

    int vertex10Color = lf::getColor(10, sudokuGraph, sudokuList); // OK!
    cout << "Vertex 10 choosed color: " << vertex10Color << "\n";

    cout << "\n>>> End of Tests...\n\n";
    cout << ">>> Largest-First Algorithm result:\n";
    lf::largestFirst(sudokuGraph, sudokuList); // OK!
    ut::printSudokuList(sudokuList);
}