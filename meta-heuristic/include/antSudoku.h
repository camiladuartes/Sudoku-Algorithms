#ifndef ANTSUDOKU_H
#define ANTSUDOKU_H

#include <bits/stdc++.h>
#include "../../util/util.h"
#include "valueSet.h"
using namespace std;

#define NUM_ANTS 10
#define NUM_CELLS 81
#define NUM_UNITS 9
#define PHER_0 1

/// Ant colonies heuristic to solve 9x9 Sudoku
namespace ant{
    void set_cell(int ant, int i, const ValueSet &choice);
    
    double rho = 0.9;
    double best_pher = 0, best_evap = 0;
    int best_ant = 0;   // indice da melhor formiga

    vector<ValueSet> best_solution = {};    // solucao final

    // vectors usados para cada solucao
    vector<int> fail_cells = {};
    vector<vector<ValueSet>> ant_solutions = {};
    vector<int> ant_cell = {};
    vector<int> fixed_cells = {};

    // matriz global de feromonios (81x9)
    double **pher = 0;

    uint64_t bitmap = 0;
    mt19937 rand_gen; 
	uniform_real_distribution<double> random_dist = uniform_real_distribution<double>(0.0, 1.0);
    
    /// Inicializa cada formiga em uma posição da sua cópia do puzzle
    void init_ant(vector<ValueSet> puzzle, int start_position){
        ant_solutions.push_back(puzzle);
        ant_cell.push_back(start_position);
        fail_cells.push_back(0);
        fixed_cells.push_back(0);

        // roulette deixa pra depois...
    }

    void update_local_pher(int i, int choice){
        pher[i][choice] = pher[i][choice] * 0.9f + PHER_0*0.1f;
    }

    ///////////////////////
    /// Função do Huw Lloyd
    int row_cell(int row, int cell){
        return row*NUM_UNITS+cell;
    }

    int col_cell(int col, int cell){
        return cell * NUM_UNITS + col;
    }

    int box_cell(int box, int cell){
        int box_col = box%3;
        int box_row = box / 3;
        int box_first = (box_col*3) + box_row*27;

        return box_first + (cell%3) + (cell/3)*9;
    }

    void constrain_cell(int ant, int i){
        if(ant_solutions[ant][i].Empty() || ant_solutions[ant][i].Fixed())
		return;
	
        int i_box = 3*(i/27)+((i%9)/3);
        int i_col = i%NUM_UNITS;
        int i_row = i/NUM_UNITS;

        ValueSet colFixed(NUM_UNITS), rowFixed(NUM_UNITS), boxFixed(NUM_UNITS);
        ValueSet colAll(NUM_UNITS), rowAll(NUM_UNITS), boxAll(NUM_UNITS);

        for(int j = 0; j < NUM_UNITS; j++){
            int k;
            k = box_cell(i_box, j);
            if(k != i){
                if (ant_solutions[ant][k].Fixed() )
                    boxFixed += ant_solutions[ant][k];
                boxAll += ant_solutions[ant][k];
            }
            k = col_cell(i_col, j);
            if(k != i){
                if (ant_solutions[ant][k].Fixed() )
                    colFixed += ant_solutions[ant][k];
                colAll += ant_solutions[ant][k];
            }
            k = row_cell(i_row, j);
            if(k != i){
                if (ant_solutions[ant][k].Fixed() )
                    rowFixed += ant_solutions[ant][k];
                rowAll += ant_solutions[ant][k];
            }
        }

        ValueSet fixedCellsConstraint = ~(rowFixed + colFixed + boxFixed);

        if(fixedCellsConstraint.Fixed()) 
            set_cell(ant, i, fixedCellsConstraint);
        else {
            ant_solutions[ant][i] ^= fixedCellsConstraint;
            if ((ant_solutions[ant][i]-rowAll).Fixed())
                set_cell(ant, i, ant_solutions[ant][i]-rowAll);
            else if ((ant_solutions[ant][i]-colAll).Fixed())
                set_cell(ant, i, ant_solutions[ant][i]-colAll);
            else if ((ant_solutions[ant][i]-boxAll).Fixed())
                set_cell(ant, i, ant_solutions[ant][i]-boxAll);
        }

        if(ant_solutions[ant][i].Empty())
            fail_cells[ant]++;
    }
    ////////////////////////////////////////////

    void set_cell(int ant, int i, const ValueSet &choice){
        if(ant_solutions[ant][i].Fixed()) return;

        ant_solutions[ant][i] = choice;

        int i_box, i_col, i_row;
	    i_box = 3*(i/27)+((i%9)/3);
        i_col = i%NUM_UNITS;
        i_row = i/NUM_UNITS;

        for(int j=0; j<NUM_UNITS; j++){
            int k;
            k = box_cell(i_box, j);
            if(k != i) constrain_cell(ant, k);

            k = col_cell(i_col, j);
            if(k != i) constrain_cell(ant, k);

            k = row_cell(i_row, j);
            if(k != i) constrain_cell(ant, k);
        }
    }

    void step_solution(int ant){
        // vector<ValueSet> sol = ant_solutions[ant];
        int i_cell = ant_cell[ant];

        // recupero posição do tabuleiro que a formiga está agora 
        if(ant_solutions[ant][i_cell].Empty())
            fail_cells[ant]++;
        else if(!ant_solutions[ant][i_cell].Fixed()){
            // escolhendo a cor 0 (ativo bit número 0)
            // 000000001
            ValueSet choice = ValueSet(NUM_UNITS, 1);
            
            // começa o greedy solution
            ValueSet best;
            double max_pher = -1.0;

            for(int j=0; j<NUM_UNITS; j++){
                // vejo se posso escolher o choice pra essa célula
                if(ant_solutions[ant][i_cell].Contains(choice)){
                    // confiro se o feromonio dessa celula é melhor do que o maximo
                    if(pher[i_cell][j] > max_pher){
                        max_pher = pher[i_cell][j];
                        best = choice;
                    }
                }
                // 000000010
                choice <<= 1;
            }
            
            set_cell(ant, i_cell, best);  

            // atualiza feromonio local
            update_local_pher(i_cell, best.Index());
        }
    }

    /// Retorna o número de células que não tem conflitos
    int num_cells_filled(int ant){
        return NUM_CELLS - fail_cells[ant];
    }

    /// Adiciona o feromônio inicial em cada posicao da matriz 81x9
    void init_pher(int num_cells, int num_units){
        pher = new double*[num_cells];
        for(int i = 0; i < num_cells; i++){
            pher[i] = new double[num_units];
            for(int j = 0; j < num_units; j++)
                pher[i][j] = PHER_0;
        }
    }

    double add_pher(int val){
        return NUM_CELLS/(double)(NUM_CELLS-val);
    }
    
    /// Atualiza o feromonio global da melhor solução
    void update_pher(){
        for(int i = 0; i < NUM_CELLS; i++){
            if(best_solution[i].Fixed()){
                pher[i][best_solution[i].Index()] = pher[i][best_solution[i].Index()] * (1.0f-rho) + rho*best_pher;
            }
        }
    }

    void clear_pher(){
        for(int i = 0; i < NUM_CELLS; i++)
		    delete[] pher[i];
        delete[] pher;
    }

    /// Resolve o sudoku com formigas
    vector<ValueSet> solve(vector<ValueSet> sudokuList){
        bool solved = false;
        int aux = 0;

        // criando as formigas
        vector<int> ants = {};
        for(int i=0; i<NUM_ANTS; i++){
            ants.push_back(i);
        }

        // adiciona feromonio inicial
        init_pher(NUM_CELLS, NUM_UNITS);

        while(!solved){
            // pego um valor aleatório para ser a posição inicial da formiga
		    uniform_int_distribution<int> dist(0, 80);

            // inicializo cada formiga em uma célula do sudoku
            for(auto a : ants)
                init_ant(sudokuList, dist(rand_gen));

            // preencho as células uma de cada vez
            for(int i=0; i<sudokuList.size(); i++){
                for(auto a : ants) step_solution(a);
            }  

            int i_best = 0; // indice na melhor formiga
            int best_val = 0; 

            // recupero a melhor formiga, ou seja, a formiga que preencheu mais células 
            for(int i=0; i<ants.size(); i++){
                // minimizando o número de conflitos
                if(num_cells_filled(ants[i]) > best_val){
                    best_val = num_cells_filled(ants[i]);
                    i_best = i;
                }
            }

            // recupera o melhor feromonio para poder atualizar a matriz global
            double new_pher = add_pher(best_val);
            if(new_pher > best_pher){
                best_solution = ant_solutions[i_best];
                best_pher = new_pher;
                best_ant = best_val;
    
                if(best_val == 81){
                    solved = true;
                }
            }

            // atualizo o feromonio
            update_pher();
            best_pher *= (1.0-best_evap);
            aux++;
        }

        clear_pher();
        return best_solution;
    }
}

#endif