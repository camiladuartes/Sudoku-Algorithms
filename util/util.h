#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <set>
using namespace std;
#define N 9

/// Useful functions for Largest-First Heuristic to solve 9x9 Sudoku
namespace ut{
    /*!
    * Receivs a string of digits 0-9 and transforms it into a
    * list of elements which are the characters of this string.
    */
    void convert(string str, vector<int> &list) {
        for(int i = 0; i < str.size(); i++) {
            list.push_back(str[i]-'0');
        }
    }

    /*!
    * Prints a list in a Sudoku format
    */
    void printSudokuList(vector<int> list) {
        for(int i = 0; i < list.size(); i++) {
            cout << list[i] << " ";
            if((i+1) % 9 == 0)
                cout << endl;
        }
    }

    /*!
    * Checks if a value is an element of some list
    */
    bool inList(int x, vector<int> list) {
        for(int digit : list) {
            if(x == digit)
                return true;
        }
        return false;
    }

    /*!
    * Checks if a graph it is fully colored (digits <-> colors)
    */
    bool isColored(vector<int> list) {
        int colored = 0;
        for(int digit : list) {
            if(digit != 0)
                colored++;
        }
        if(colored == list.size()) return true;
        return false;
    }

    /*!
    * In order to solve Sudoku using the Largest-First heuristic, it is necessary
    * modeling the game on a graph. (it is gonna always be the same)
    */
    vector<int> adjacencyList(int x) {
        int list[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
                        21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                        41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,
                        61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};
        vector<int> adjList;

        int line = floor(x / 9);
        int count = 0;
        // vertices of the same line
        while(count < 9) {
            if(x != list[line * 9 + count])
                adjList.push_back(list[line * 9 + count]);
            count++;
        }

        // vertices of the same column
        int column = x % 9;
        count = 0;
        while(count < 9) {
            if(x != list[column + 9 * count])
                adjList.push_back(list[column + 9 * count]);
            count++;
        }

        // vertices of the same block
        // first line of each block, first column
        if((x % 27 == 0) or (x % 27 == 3) or (x % 27 == 6)) {
            adjList.push_back(list[x + 10]);
            adjList.push_back(list[x + 11]);
            adjList.push_back(list[x + 19]);
            adjList.push_back(list[x + 20]);
        }

        // first line of each block, second column
        if((x % 27 == 1) or (x % 27 == 4) or (x % 27 == 7)) {
            adjList.push_back(list[x + 8]);
            adjList.push_back(list[x + 10]);
            adjList.push_back(list[x + 17]);
            adjList.push_back(list[x + 19]);
        }

        // first line of each block, thrid column
        if((x % 27 == 2) or (x % 27 == 5) or (x % 27 == 8)) {
            adjList.push_back(list[x + 7]);
            adjList.push_back(list[x + 8]);
            adjList.push_back(list[x + 16]);
            adjList.push_back(list[x + 17]);
        }

        // second line of each block, first column
        if((x % 27 == 9) or (x % 27 == 12) or (x % 27 == 15)) {
            adjList.push_back(list[x - 8]);
            adjList.push_back(list[x - 7]);
            adjList.push_back(list[x + 10]);
            adjList.push_back(list[x + 11]);
        }

        // second line of each block, second column
        if((x % 27 == 10) or (x % 27 == 13) or (x % 27 == 16)) {
            adjList.push_back(list[x - 10]);
            adjList.push_back(list[x - 8]);
            adjList.push_back(list[x + 8]);
            adjList.push_back(list[x + 10]);
        }

        // second line of each block, thrid column
        if((x % 27 == 11) or (x % 27 == 14) or (x % 27 == 17)) {
            adjList.push_back(list[x - 11]);
            adjList.push_back(list[x - 10]);
            adjList.push_back(list[x + 7]);
            adjList.push_back(list[x + 8]);
        }

        // third line of each block, first column
        if((x % 27 == 18) or (x % 27 == 21) or (x % 27 == 24)) {
            adjList.push_back(list[x - 17]);
            adjList.push_back(list[x - 16]);
            adjList.push_back(list[x - 8]);
            adjList.push_back(list[x - 7]);
        }
        
        // third line of each block, second column
        if((x % 27 == 19) or (x % 27 == 22) or (x % 27 == 25)) {
            adjList.push_back(list[x - 19]);
            adjList.push_back(list[x - 17]);
            adjList.push_back(list[x - 10]);
            adjList.push_back(list[x - 8]);
        }

        // third line of each block, thrid column
        if((x % 27 == 20) or (x % 27 == 23) or (x % 27 == 26)) {
            adjList.push_back(list[x - 20]);
            adjList.push_back(list[x - 19]);
            adjList.push_back(list[x - 11]);
            adjList.push_back(list[x - 10]);
        }

        return adjList;
    }

    /*!
    * Prints the adjacency lists of a graph
    */
    void printSudokuAdjList(map<int, vector<int>> sudokuGraph) {
        cout << "\n{\n";
        for(auto it = sudokuGraph.begin(); it != sudokuGraph.end(); ++it){
            cout << it->first << ": [";
            for (auto i: it->second)
                cout << i << ", ";
            cout << "]\n";
        }
        cout << "}\n";
    }

    /*!
    * The next two functions will be used to sort a map by decreasing order
    */
    /// Comparison function for sorting the set by decreasing order of its pair's second value
    struct comp {
        // Comparator function
        bool operator()(const pair<int, int>& l, const pair<int, int>& r) const {
            if (l.second != r.second) {
                return l.second > r.second;
            }
            return l.first > r.first;
        }
    };
    
    /// Function to sort the map according to value
    void reverseMapSort(map<int, int>& M) {
        // Declare set of pairs and insert pairs according to the comparator function comp()
        set<pair<int, int>, comp> S(M.begin(), M.end());
    }

    /*!
    * Convert the Sudoku vector in a matrix 9x9
    */
    void convertMatrix(vector<int>& list, int grid[9][9]){
        // 004300209 005009001 070060043 006002087 190007400 050083000 600000105 003508690 042910300
        int j = 0, count = 0; 
        for(int i = 0; i < list.size(); i++) {
            count++;
            grid[j][i] = list[i];

            if(count == 9){
                j++;
                count = 0;
            }
        }
    }

    /*!
    * Print the Sudoku vector in a matrix 9x9
    */
    void printMatrix(vector<int>& list, int grid[9][9]){
        int j = 0, count = 0;

        for(int i = 0; i < list.size(); i++) {
            count++;
            cout << grid[j][i] << " ";
            if(count == 9){
                j++;
                count = 0;
                cout << endl;
            }
        }
    }

    void print(int arr[N][N]){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << arr[i][j] << " ";
            cout << endl;
        }
    }
}

#endif