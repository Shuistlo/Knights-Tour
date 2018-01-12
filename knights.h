#ifndef KNIGHTS_H
#define KNIGHTS_H

#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cstdint>

// Do not add any extra #includes without asking on the KEATS discussion forum

using std::pair;
using std::make_pair;
using std::vector;

typedef vector<pair<int,int> > Path;

/** Helper function: adds two pairs of ints */
pair<int,int> operator+(const pair<int,int> & a, const pair<int,int> & b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

// TODO - your code goes here

bool const isLegal(const pair<int,int> &currLoc, const int dim, const vector<pair<int,int>> path){
    if(std::find(path.begin(), path.end(), currLoc) == path.end()) { return false; }
    return !(currLoc.first < 0 || currLoc.first >=dim || currLoc.second < 0 || currLoc.second > dim);
}

vector<pair<int,int>> moves(const pair<int,int> & currLoc){
    vector<pair<int,int>> operations{make_pair(1,-2), make_pair(2,-1), make_pair(2,1),make_pair(1,2),make_pair(-1,2),make_pair(-2,1),make_pair(-2,-1),make_pair(-1,-2)};
    vector<pair<int,int>> moves(8);
    std::transform(operations.begin(), operations.end(), moves, [&currLoc](const pair<int,int> cL){
        return cL+currLoc;
    });
    return moves;
}

vector<pair<int,int>> legal_moves(const int dim, const vector<pair<int,int>> path, const pair<int,int> &currLoc){
    vector<pair<int,int>> allMoves = moves(currLoc);
    vector<pair<int,int>> legalsOnly;
    std::transform(allMoves.begin(), allMoves.end(), legalsOnly, [&currLoc, dim, path](const pair<int,int> cL){
        if(isLegal(currLoc, dim, path)){
                   return cL;
        }
    });
    return legalsOnly;
}

pair<Path,bool> first_tour(const int dim, Path path) {
    if(path.size() == dim*dim){
        return make_pair(path, true);
    }
    Path emptyPath;
    vector<pair<int,int>> moves = legal_moves(dim,path,path[path.size()-1]);
    if(moves.size() == 0){
        return make_pair(emptyPath, false);
    }
    else {
        for(int i = 0; i < moves.size(); i++){
            path.push_back(moves[i]);
            pair<Path,bool> possibleTour = first_tour(dim,path);
            if(possibleTour.second==true){
                return possibleTour;
            }else{
                path.pop_back();
            }
        }
    return make_pair(emptyPath,false);
    }
}

// Do not edit below this line

#endif
