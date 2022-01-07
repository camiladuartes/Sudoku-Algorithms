#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <bits/stdc++.h>
#include "../../util/util.h"
using namespace std;

/// Backtracking to solve 9x9 Sudoku
namespace bt{
     bool shouldColor(int grid[9][9], int row, int col, int value){
        for(int i = 0; i <= 8; i++){
            if(grid[row][i] == value)
                return false;
        }
    
        for(int i = 0; i <= 8; i++){
            if(grid[i][col] == value)
                return false;
        }
    
        int startRow = row-row%3, startCol = col-col%3;
    
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(grid[i+startRow][j+startCol] == value)
                    return false;
            }
        }
    
        return true;
    }
    
    bool solveSudoku(int grid[9][9], int row, int col) {
        if(row == 8 && col == 9)
            return true;

        if(col == 9){
            row++;
            col = 0;
        }
    
        if(grid[row][col] > 0)
            return solveSudoku(grid, row, col+1);
    
        for(int i = 0; i <= 8; i++){
            if(shouldColor(grid, row, col, i)){
                grid[row][col] = i;
            
                if(solveSudoku(grid, row, col+1))
                    return true;
            }
            grid[row][col] = 0;
        }

        return false;
    }
}

#endif