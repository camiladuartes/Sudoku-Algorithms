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

        // Guardo em uma lista as posi????es do grid que s??o 0, e mapeio todas as posi????es para 0
        for (int i=0; i < ut::emptyCells(sudokuList).size(); i++){
            vector<int> empty = ut::emptyCells(sudokuList);
            attemps[empty[i]] = 0;
        }

        // Crio uma lista com as posi????es vazias (0) do grid
        int count = 0, tryPutNumber = 0, validateNumber = 0;
        vector<int> sudokuListEmptyCells = ut::emptyCells(sudokuList);

        // sudokuList = 497200000100400005000016098620300040300900000001072600002005870000600004530097061
        // sudokuListEmptyCells = 4 5 6 7 8 10 11 13 14 15 16...
        // attemps = {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {10, 0} ...

        // Para cada posi????o vazia do grid, tenta colorir com o pr??ximo valor dispon??vel
        while (count < sudokuListEmptyCells.size()){
            // Para cada posi????o vazia no grid, tento colorir com o pr??ximo valor dispon??vel (sempre somando mais um)
            int index = sudokuListEmptyCells[count];
            // Valor (cor) que estou tentando colorir (come??a sendo 0+1 = 1)
            int attempCount = attemps[index] + 1;

            // Caso a tentativa seja maior do que 9, significa que estou tentando adicionar um n??mero inv??lido
            if (attempCount > 9){
                sudokuList[index] = 0;
                attemps[index] = 0;
                count -= 1;

                // Significa que o n??mero n??o ?? v??lido para aquela c??lula
                tryPutNumber = 1;
                validateNumber = 0;
            } else{
                // Significa que o n??mero ?? v??lido para aquela c??lula
                tryPutNumber = 0;
                validateNumber = 1;
            }

            // Enquanto o n??mero for v??lido para aquela c??lula, confiro se o n??mero que estou tentando colocar est?? na linha, coluna ou grid
            while (tryPutNumber == 0){
                // Checa se n??o ?? verdade que o valor est?? na lista dos n??meros proibidos
                if (!ut::inList(attempCount, getForbiddenNumbers(sudokuList, index))){
                    // Caso ele seja poss??vel colorir a c??lula com o n??mero, coloro e atualizo o map
                    sudokuList[index] = attempCount;
                    attemps[index] = attempCount;

                    // Significa que j?? adicionei o n??mero que deveria
                    tryPutNumber = 1;
                    validateNumber = 1;
                } else {
                // Caso o valor atual j?? esteja na lista (linha, coluna ou grid), tento adicionar o pr??ximo valor dispon??vel
                    if (attempCount == 9){
                        // Caso j?? esteja na nona tentativa, significa que j?? foi adicionado todos os valores poss??veis para aquela c??lula
                        sudokuList[index] = 0;
                        attemps[index] = 0;
                        count -= 1;

                        // Significa que o n??mero n??o era v??lido para a posi????o
                        tryPutNumber = 1;
                        validateNumber = 0;
                    }
                    // Atualizo minha tentativa com o pr??ximo n??mero dispon??vel
                    attempCount += 1;
                }
            }

            // Se o n??mero for v??lido, incremento o count para avan??ar para o pr??ximo indice vazio da minha lista e repetir todo o processo
            if(validateNumber == 1) count += 1;
        }

        return sudokuList;
    }
}

#endif