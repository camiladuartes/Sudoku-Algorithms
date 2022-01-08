#include <bits/stdc++.h>
#include "../../util/util.h"
#include "../include/backtracking.h"
using namespace std;

int main(){
    int tam = 100000;
    string sudoku[tam] = {""};
    string solution[tam] = {""};

    for(int i=0; i<tam; i++){
        cin >> sudoku[i] >> solution[i];
    }
    
    int hits = 0, count = 0;
    auto start = chrono::high_resolution_clock::now();

    for(int i=1; i<tam; i++){
        cout << "Solving Sudoku " << i << endl;

        vector<int> sudokuList = {};
        vector<int> solutionList = {};
        string sudokuString = sudoku[i];
        string solutionString = solution[i];

        ut::convert(sudokuString, sudokuList);
        ut::convert(solutionString, solutionList);

        // ut::printSudokuList(sudokuList);
        // cout << endl;

        ut::printSudokuList(bt::solveSudoku(sudokuList));    
        cout << endl;

        if (sudokuList == solutionList) hits++;
        count++;
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "Quantidade de sudokus resolvidos: " << count << endl;
    cout << "Quantidade de sudokus resolvidos corretamente: " << hits << endl;
    cout << "Tempo decorrido para fim de processamento: " << (chrono::duration_cast<std::chrono::milliseconds>(end-start).count())/1000 << " s" << endl;

}