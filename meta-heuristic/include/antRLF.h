#ifndef ANTRLF_H
#define ANTRLF_H

#include <bits/stdc++.h>
#include "../../util/util.h"
using namespace std;

/// Ant colonies heuristic to solve 9x9 Sudoku
namespace ant{
    double rho = 0.9;
    // alpha: peso relativo ao feromonio
    // beta: peso relativo a heuristica
    double alpha = 1, betha = 1; 
    double M[81][81] = {};

    int getBlock(int a){
        int linha = a/9;
        int coluna = a%9;
        int bloco = linha*3+coluna;
        return bloco;
    }

    bool checkAdjacents(int a, int b){
        if(a%9 == b%9) return true; // mesma coluna
        if(a/9 == b/9) return true; // mesma linha
        if(getBlock(a) == getBlock(b)) return true; // mesmo bloco

        return false;
    }

    vector<int> getNeighbors(vector<int> W, int a){
        vector<int> adjacents = {};
        for(auto v : W){
            if(checkAdjacents(v, a)) adjacents.push_back(v);
        }

        return adjacents;
    }   

    vector<int> difference(vector<int> W, vector<int> neighbors, int v){
        // Removo todos os vizinhos
        for(auto neigh : neighbors){
            auto it = find(W.begin(), W.end(), neigh);
            if(it != W.end()) W.erase(it);
        }
        // Removo todos o v
        auto it = find(W.begin(), W.end(), v);
        if(it != W.end()) W.erase(it);

        return W;
    }

    double tal(vector<vector<int>> solution, int v, int c){
        vector<int> V_c = solution[c];
        if(V_c.empty()) return 1;
        
        int sum = 0;
        for(auto x : V_c){
            sum += M[x][v];
        }

        return sum/V_c.size();
    }

    int deg_B(vector<int> B, int v){
        return getNeighbors(B, v).size();
    }

    double calc_prob(int v, vector<vector<int>> solution, int c, vector<int> B, vector<int> W){
        double numerador = pow(tal(solution, v, c), alpha) * pow(deg_B(B, v), betha);
        double denominador = 0;

        for(auto o : W){
            denominador += pow(tal(solution, o, c), alpha) * pow(deg_B(B, o), betha);
        }

        return numerador/denominador;
    }

    int random_pick(vector<int> W, vector<vector<int>> solution, int c, vector<int> B){
        double total_prob = 0;
        vector<double> probs;

        for(auto w : W){
            probs.push_back(calc_prob(w, solution, c, B, W));
            total_prob += probs.back();
        }

        double r = rand()/((double)RAND_MAX)*total_prob;
        for(int p =0; p<probs.size(); p++){
            if(r < probs[p]) return W[p];
            r -= probs[p];
        }

        return W[0];
    }

    // ANT_RLF
    vector<vector<int>> buildSolution(vector<int>& sudokuList){
        int q = 0;
        vector<int> V = ut::emptyCells(sudokuList);

        vector<int> W = V;
        int k = 0;

        vector<vector<int>> solution = {};

        for(int i=0; i<9; i++){
            solution.push_back({});
        }

        for(int i=0; i<sudokuList.size(); i++){
            if(sudokuList[i]) solution[sudokuList[i]-1].push_back(i); 
        }

        while(k < V.size()){
            k++;
            q++;
            vector<int> B = {};
            int v = W[rand()%W.size()];

            // Formiga adiciona um elemento na solução parcial
            solution.push_back({v});

            vector<int> neighbors = getNeighbors(W, v);
            while(!difference(W, neighbors, v).empty()){
                k++;

                for(int i=0; i<neighbors.size(); i++){
                    B.push_back(neighbors[i]);
                }

                // Removo todos os vizinhos
                for(auto neigh : neighbors){
                    auto it = find(W.begin(), W.end(), neigh);
                    if(it != W.end()) W.erase(it);
                }
                // Removo todos o v
                auto it = find(W.begin(), W.end(), v);
                if(it != W.end()) W.erase(it);

                v = random_pick(W, solution, q-1, B);
                neighbors = getNeighbors(W, v);
                solution[q-1].push_back(v);
            }

            for(auto b : B) W.push_back(b);
            for(auto n : neighbors) W.push_back(n);
        }

        return solution;
    }

    // ANTCOL
    vector<vector<int>> antCOL(vector<int>& sudokuList){
        for(int i=0; i<81; i++){
            for(int j=0; j<81; j++){
                M[i][j] = 1;
            }
        }

        int n_colors = 1e9, n_max = 100, n_ants = 100;

        vector<vector<int>> s_solution = {};

        for(int i =1; i<n_max; i++){
            double d_M[81][81] = {0};
            for(int j=1; j<n_ants; j++){
                vector<vector<int>> s = buildSolution(sudokuList); 
                int q = s.size();

                if(q < n_colors){
                    s_solution = s;
                    n_colors = q;
                }
                
                for(auto V : s){  // apenas pelos vértices que tem a mesma cor
                    // checo par por par
                    for(auto v_r : V){
                        for(auto v_s : V){
                            if(!checkAdjacents(v_r, v_s)){
                                d_M[v_r][v_s] = d_M[v_r][v_s]+(1/q);
                            }
                        }
                    }
                }
            }

            for(int v_r = 0; v_r<81; v_r++){
                for(int v_s = 0; v_s<81; v_s++){
                    if(!checkAdjacents(v_r, v_s)){
                        M[v_r][v_s] = rho*M[v_r][v_s] + d_M[v_r][v_s];
                    }
                }
            }
        }

        return s_solution;
    }
}

#endif