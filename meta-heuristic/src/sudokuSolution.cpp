#include <bits/stdc++.h>
#include "../include/antSudoku.h"
#include "../include/valueSet.h"
#include "../../util/util.h"
using namespace std;

vector<ValueSet> convert_VS(vector<int> sudokuList){
    vector<ValueSet> ans = {};

    for(int i : sudokuList){
        if(i == 0){
            // 1000000000
            // 0111111111
            ans.push_back(ValueSet(9, (1 << 9)-1));
        } else{
            ans.push_back(ValueSet(9, (1 << (i-1))));
        }
    }
    return ans;
}

string convert_string(vector<ValueSet> sudokuVS){
    string ans = "";

    for(auto i : sudokuVS){
        ans += to_string(i.Index());
    }
    return ans;
}

int main() {
    int tam = 10;
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
        
        vector<ValueSet> sudoku_VS = convert_VS(sudokuList);
        vector<ValueSet> solution_VS = ant::solve(sudoku_VS);
        string solution_string = convert_string(solution_VS);

        cout << endl;
        if (solution_string == solutionString) hits++;
        count++;
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "Quantidade de sudokus resolvidos: " << count << endl;
    cout << "Quantidade de sudokus resolvidos corretamente: " << hits << endl;
    cout << "Tempo decorrido para fim de processamento: " << (chrono::duration_cast<std::chrono::milliseconds>(end-start).count())/1000 << " s" << endl;

    /////////////////////////////////////

    // auto start = chrono::high_resolution_clock::now();
    // cout << "Solving Sudoku" << endl;

    // vector<int> sudokuList = {};    
    // string sudokuString = "153000000000700900000254800006070284405080010009001360074000000030600027862590043";
    // ut::convert(sudokuString, sudokuList);

    // vector<ValueSet> sudoku_VS = convert_VS(sudokuList);
    // vector<ValueSet> solution = ant::solve(sudoku_VS);

    // string solutionString = convert_string(solution);

    // auto end = chrono::high_resolution_clock::now();
    // cout << "Tempo decorrido para fim de processamento: " << (chrono::duration_cast<std::chrono::milliseconds>(end-start).count())/1000 << " s" << endl;
}

