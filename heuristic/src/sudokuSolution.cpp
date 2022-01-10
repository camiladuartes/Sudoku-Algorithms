#include <bits/stdc++.h>
#include "../include/largestFirst.h"
#include "../../util/util.h"
using namespace std;

// Quantidade de sudokus resolvidos: 100000
// Quantidade de sudokus resolvidos corretamente: 217
// Tempo decorrido para fim de processamento: 866 s

int main() {
    int tam = 500000;
    string sudoku[tam] = {""};
    string solution[tam] = {""};

    for(int i=0; i<tam; i++){
        cin >> sudoku[i] >> solution[i];
    }
    
    int hits = 0, count = 0;
    auto start = chrono::high_resolution_clock::now();

    for(int i=0; i<tam; i++){
        cout << "Solving Sudoku " << i << endl;

        vector<int> sudokuList = {};
        vector<int> solutionList = {};
        string sudokuString = sudoku[i];
        string solutionString = solution[i];

        ut::convert(sudokuString, sudokuList);
        ut::convert(solutionString, solutionList);
        vector<int> test = {0,0,0,1,2,3,0,0,4};

        map<int, vector<int>> sudokuGraph;
        for(int i = 0; i < 81; i++)
            sudokuGraph[i] = ut::adjacencyList(i);

        vector<int> orderedByDegree = lf::UncoloredVerticesOrderedByDegree(sudokuGraph, sudokuList);
        vector<int> forbiddenColorsTest = lf::getForbiddenColors(10, sudokuGraph, sudokuList);
        int vertex10Color = lf::getColor(10, sudokuGraph, sudokuList); 

        lf::largestFirst(sudokuGraph, sudokuList);
        cout << endl;

        if (sudokuList == solutionList) hits++;
        count++;
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "Quantidade de sudokus resolvidos: " << count << endl;
    cout << "Quantidade de sudokus resolvidos corretamente: " << hits << endl;
    cout << "Tempo decorrido para fim de processamento: " << (chrono::duration_cast<std::chrono::milliseconds>(end-start).count())/1000 << " s" << endl;
}