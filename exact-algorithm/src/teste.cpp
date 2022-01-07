#include <bits/stdc++.h>
#include "../../util/util.h"
#include "../include/backtracking.h"
using namespace std;

int main(){
    // 306508400520000000087000031003010080900863005050090600130000250000000074005206300
    // string sudokuString = "153000000000700900000254800006070284405080010009001360074000000030600027862590043";
    string sudokuString = "306508400520000000087000031003010080900863005050090600130000250000000074005206300";
    vector<int> sudokuList = {};
    int grid[9][9] = {};

    ut::convert(sudokuString, sudokuList);
    ut::printSudokuList(sudokuList);
    cout << endl;

    ut::convertMatrix(sudokuList, grid);
    ut::printMatrix(sudokuList, grid);
    cout << endl;
   
   if(bt::solveSudoku(grid, 0, 0))
        ut::print(grid);
    else cout << "Sem solução" << endl;
    
    // convert
    // for(int i = 0; i < sudokuString.size(); i++) {
    //     sudokuList.push_back(sudokuString[i]-'0');
    // }

    // print sudoku
    // for(int i = 0; i < sudokuList.size(); i++) {
    //     cout << sudokuList[i] << " ";
    //     if((i+1) % 9 == 0)
    //         cout << endl;
    // }

    // cout << endl;

    // adding in a grid
    // 153000000 000700900 000254800 006070284 405080010 009001360 074000000 030600027 862590043    
    // int j = 0, count = 0; 
    // for(int i = 0; i < sudokuList.size(); i++) {
    //     count++;
    //     grid[j][i] = sudokuList[i];

    //     if(count == 9){
    //         j++;
    //         count = 0;
    //     }
    // }

    // for(int i = 0; i < 9; i++) {
    //     for(int j = 0; j < 9; j++) {
    //         cout << "i = " << i << " j = " << j << " -> " << grid[i][j] << endl;
    //         // cout << grid[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // int j = 0, count = 0;

    // for(int i = 0; i < sudokuList.size(); i++) {
    //     count++;
    //     cout << grid[j][i] << " ";
    //     if(count == 9){
    //         j++;
    //         count = 0;
    //         cout << endl;
    //     }
    // }

}