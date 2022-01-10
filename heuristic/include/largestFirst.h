#ifndef LARGESTFIRST_H
#define LARGESTFIRST_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include "../../util/util.h"
using namespace std;

/// Largest-First Heuristic to solve 9x9 Sudoku
namespace lf{
    /*!
    * Returns uncolored vertices of a graph ordered by their degrees
    */
    vector<int> UncoloredVerticesOrderedByDegree(map<int, vector<int>> sudokuGraph, vector<int>& colorsList) {
        map<int, int> graphDegrees;
        for(int i = 0; i < sudokuGraph.size(); i++) {
            graphDegrees[i] = sudokuGraph[i].size();
        }
        ut::reverseMapSort(graphDegrees);

        vector<int> orderedByDegree;
        for(auto i : graphDegrees) {
            if(colorsList[i.first] == 0) {
                orderedByDegree.push_back(i.first);
            }
        }

        return orderedByDegree;
    }

    /*!
    * Returns a list of numbers(colors) that can't be assigned to a vertex without
    * breaking the vertex coloring rule 
    */
    vector<int> getForbiddenColors(int vertex, map<int, vector<int>> sudokuGraph, vector<int>& colorsList) {
        vector<int> forbiddenColors;

        for(int i = 0; i < sudokuGraph[vertex].size(); i++) {
            if(colorsList[sudokuGraph[vertex][i]] != 0)
                forbiddenColors.push_back(colorsList[sudokuGraph[vertex][i]]);
        }

        return forbiddenColors;
    }

    /*!
    * Chooses the color for a vertex: the smallest possible number,
    * (considering the colors as numbers)
    */
    int getColor(int vertex, map<int, vector<int>> sudokuGraph, vector<int>& colorsList) {
        vector<int> forbiddenColors = getForbiddenColors(vertex, sudokuGraph, colorsList);

        if(forbiddenColors.size() == 0)
            return 1;

        int greater = 0;
        for(auto forbiddenColor : forbiddenColors) {
            if(forbiddenColor > greater)
                greater = forbiddenColor;
        }

        int color = 1;
        while(true) {
            if(color == greater)
                return (color+1);
            if(!ut::inList(color, forbiddenColors))
                return color;
            color++;
        }
    }

    /*!
    * Runs Largest-First heuristic algorithm
    */
    void largestFirst(map<int, vector<int>> sudokuGraph, vector<int>& colorsList) {
        while(!ut::isColored(colorsList)) {
            int vertex = UncoloredVerticesOrderedByDegree(sudokuGraph, colorsList)[0];
            int color = getColor(vertex, sudokuGraph, colorsList);
            colorsList[vertex] = color;
        }
    }
}

#endif