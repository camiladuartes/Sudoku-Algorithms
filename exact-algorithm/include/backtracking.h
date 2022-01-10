#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <bits/stdc++.h>
#include "../../util/util.h"
using namespace std;

/// Backtracking to solve 9x9 Sudoku
namespace bt{
    /*!
    * Returns which numbers can't be placed in a Sudoku cell
    */
    vector<int> getForbiddenNumbers(vector<int> &list, int x){
        vector<int> returnList;

        int line = floor(x / 9); 
        int count = 0;
        // vertices of the same line
        while (count < 9){
            returnList.push_back(list[line * 9 + count]);
            count += 1;
        }

        // vertices of the same column
        int column = x % 9;
        count = 0;
        while (count < 9){
            returnList.push_back(list[column + 9 * count]);
            count += 1;
        }

        // vertices of the same block
        // first line of each block, first column
        if ((x % 27 == 0) || (x % 27 == 3) || (x % 27 == 6)){
            returnList.push_back(list[x + 10]);
            returnList.push_back(list[x + 11]);
            returnList.push_back(list[x + 19]);
            returnList.push_back(list[x + 20]);
        }

        // first line of each block, second column
        if ((x % 27 == 1) || (x % 27 == 4) || (x % 27 == 7)){
            returnList.push_back(list[x + 8]);
            returnList.push_back(list[x + 10]);
            returnList.push_back(list[x + 17]);
            returnList.push_back(list[x + 19]);
        }

        // first line of each block, thrid column
        if ((x % 27 == 2) || (x % 27 == 5) || (x % 27 == 8)){
            returnList.push_back(list[x + 7]);
            returnList.push_back(list[x + 8]);
            returnList.push_back(list[x + 16]);
            returnList.push_back(list[x + 17]);
        }

        // second line of each block, first column
        if ((x % 27 == 9) || (x % 27 == 12) || (x % 27 == 15)){
            returnList.push_back(list[x - 8]);
            returnList.push_back(list[x - 7]);
            returnList.push_back(list[x + 10]);
            returnList.push_back(list[x + 11]);
        }

        // second line of each block, second column
        if ((x % 27 == 10) || (x % 27 == 13) || (x % 27 == 16)){
            returnList.push_back(list[x - 10]);
            returnList.push_back(list[x - 8]);
            returnList.push_back(list[x + 8]);
            returnList.push_back(list[x + 10]);
        }

        // second line of each block, thrid column
        if ((x % 27 == 11) || (x % 27 == 14) || (x % 27 == 17)){
            returnList.push_back(list[x - 11]);
            returnList.push_back(list[x - 10]);
            returnList.push_back(list[x + 7]);
            returnList.push_back(list[x + 8]);
        }

        // third line of each block, first column
        if ((x % 27 == 18) || (x % 27 == 21) || (x % 27 == 24)){
            returnList.push_back(list[x - 17]);
            returnList.push_back(list[x - 16]);
            returnList.push_back(list[x - 8]);
            returnList.push_back(list[x - 7]);
        }
        
        // third line of each block, second column
        if ((x % 27 == 19) || (x % 27 == 22) || (x % 27 == 25)){
            returnList.push_back(list[x - 19]);
            returnList.push_back(list[x - 17]);
            returnList.push_back(list[x - 10]);
            returnList.push_back(list[x - 8]);
        }

        // third line of each block, thrid column
        if ((x % 27 == 20) || (x % 27 == 23) || (x % 27 == 26)){
            returnList.push_back(list[x - 20]);
            returnList.push_back(list[x - 19]);
            returnList.push_back(list[x - 11]);
            returnList.push_back(list[x - 10]);
        }

        return returnList;
    }

    /*!
    * Returns the answered Sudoku puzzle
    */
    vector<int> solveSudoku(vector<int>& sudokuList){
        map <int, int> attemps;

        for (int i=0; i < ut::emptyCells(sudokuList).size(); i++){
            vector<int> empty = ut::emptyCells(sudokuList);
            attemps[empty[i]] = 0;
        }

        int count = 0, tryPutNumber = 0, validateNumber = 0;
        vector<int> lista_sudoku_celulas_vazias = ut::emptyCells(sudokuList);

        while (count < lista_sudoku_celulas_vazias.size()){
            int index = lista_sudoku_celulas_vazias[count];
            int attempCount = attemps[index] + 1;

            if (attempCount > 9){
                sudokuList[index] = 0;
                attemps[index] = 0;
                count = count - 1;
                tryPutNumber = 1;
                validateNumber = 0;
            } else{
                tryPutNumber = 0;
                validateNumber = 1;
            }

            while (tryPutNumber == 0){
                if (!ut::inList(attempCount, getForbiddenNumbers(sudokuList, index))){
                    sudokuList[index] = attempCount;
                    attemps[index] = attempCount;
                    tryPutNumber = 1;
                    validateNumber = 1;
                } else {
                    if (attempCount == 9){
                        sudokuList[index] = 0;
                        attemps[index] = 0;
                        count = count - 1;
                        tryPutNumber = 1;
                        validateNumber = 0;
                    }
                    attempCount = attempCount + 1;
                }
            }

            if(validateNumber == 1) count = count + 1;
        }

        return sudokuList;
    }
}

#endif