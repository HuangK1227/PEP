#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>

using std::string;
using std::ostream;
using std::vector;
using std::set;
using std::map;
using std::unique_ptr;
using namespace std;

// TODO: Your Sudoku class goes here:
class Sudoku : public Searchable{

/*public:
       
    int sizeOfBoard;
    vector < vector < set<int> > > squareArray;

    Sudoku(int sizeOfBoard): sizeOfBoard(sizeOfBoard), squareArray(sizeOfBoard){
        for(int i = 1; i<sizeOfBoard; i++){
            vector< set<int> > row;
            for(int i = 1; i<sizeOfBoard; i++){
                set<int> number = {1,2,3,4,5,6,7,8,9};
                for(int i = 1; i<sizeOfBoard; i++){
                    number.insert(i);
                }
                row.push_back(number);
            }
            squareArray.push_back(row);
        }
    }

    int getSquare(int row, int col) const {
        if(squareArray[row][col].size() == 1){
            int number = *squareArray[row][col].begin();
            return number;
        }else{
            return -1;
        }
    }*/

private:
	int sizeOfBoard;
	vector<vector< set<int> > > squareArray;
	set<int> number = {1, 2, 3, 4, 5, 6, 7, 8, 9};


public:
	Sudoku(const int sizeOfBoard):
	sizeOfBoard(sizeOfBoard){

        for (int i = 0; i < sizeOfBoard; i++){
            vector<set<int> > row;
            for (int j = 0; j < sizeOfBoard; j++) {
                row.push_back(number); 
            }
            squareArray.push_back(row); 
        }
   	}


	int getSquare(int row, int col) const{			
        if(squareArray[row][col].size() == 1){
			return *squareArray[row][col].begin();
		}else{
		    return -1;
		}
	}

    bool setSquare(int row, int col, int value){
		bool result = true;
	    printf("inserting cell[%d][%d] -> %d\n", row, col, value);
    	set<int> newSet = {value};
    	squareArray[row][col] = newSet;
        bool changing = true;
        while (changing == true){
            changing = false;
            for (int row = 0; row < sizeOfBoard; ++row) {
                for (int col = 0; col < sizeOfBoard; ++col) {
                    int squareArraysizeOfBoard = sqrt(sizeOfBoard);
                    int rowStart = row - row % squareArraysizeOfBoard;
                    int colStart = col - col % squareArraysizeOfBoard;

                    if (squareArray[row][col].size() == 1) {
                        int value = *squareArray[row][col].begin();

                        for (int i = 0; i < sizeOfBoard; ++i) {
                            if (squareArray[i][col].find(value) != squareArray[i][col].end() && i != row) { 
                                squareArray[i][col].erase(value);
                                changing = true;
                                if (squareArray[i][col].size() == 0) {
                                    result = false;
                                    break;
                                }
                            }
                            if (squareArray[row][i].find(value) != squareArray[row][i].end() && i != col) {
                                squareArray[row][i].erase(value);
                                changing = true;
                                if (squareArray[row][i].size() == 0) {
                                    result = false;
                                    break;
                                }
                            }
                        }
                        for (int rowSq = rowStart; rowSq < (rowStart + squareArraysizeOfBoard); ++rowSq) {
                            for (int colSq = colStart; colSq < (colStart + squareArraysizeOfBoard); ++colSq) {
                                if (squareArray[rowSq][colSq].find(value) != squareArray[rowSq][colSq].end() && rowSq != row && colSq != col) { 
                                    squareArray[rowSq][colSq].erase(value);
                                    changing = true;
                                    if (squareArray[rowSq][colSq].size() == 0) {
                                        result = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }else if (squareArray[row][col].size() == 2) {
                        for (int i = 0; i < sizeOfBoard; ++i) {
                            if (squareArray[row][col] == squareArray[row][i] && i != col) { 
                                for (int j = 0; j < sizeOfBoard && j != col && j != i; ++j) {
                                    for (int k : squareArray[row][col]) {
                                        if (squareArray[row][j].find(k) != squareArray[row][j].end()) {
                                            squareArray[row][j].erase(k);
                                            changing = true;
                                            if (squareArray[row][j].size() == 0) {
                                                result = false;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                             if (squareArray[row][col] == squareArray[i][col] && i != row) { 
                                for (int j = 0; j < sizeOfBoard && j != row && j != i; ++j) {
                                    for (int k : squareArray[row][col]) {
                                        if (squareArray[j][col].find(k) != squareArray[j][col].end()) {
                                            squareArray[j][col].erase(k);
                                            changing = true;
                                            if (squareArray[j][col].size() == 0) {
                                                result = false;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return result;
    }

	virtual bool isSolution() const override{
    	for (int i = 0; i < sizeOfBoard; i++){
			for (int j = 0; j < sizeOfBoard; j++){
				if(getSquare(i, j) == -1){ 
	    			return false;
                }
        	}
		}
		return true;
	}
		
	virtual void write(ostream & o) const override{
		for (int i = 0; i < sizeOfBoard; i++){
			for (int j = 0; j < sizeOfBoard; j++){
				if (squareArray[i][j].size() == 1){
					o << getSquare(i, j) << " ";
				}else {
					o << "  ";
				}
			}
			o << endl;
		}
	}

	virtual vector<unique_ptr<Searchable> > successors() const override{
		vector <unique_ptr<Searchable> > hyp;
			for (int i = 0; i < sizeOfBoard; ++i) {
                for (int j = 0; j < sizeOfBoard; ++j) {
                    if (squareArray[i][j].size() > 1) {
                        for(int a : squareArray[i][j]) {
                            Sudoku * board = new Sudoku(*this);
                            if (board->setSquare(i,j,a)) {
                                hyp.emplace_back(board);
                            }else{
                                delete board;
                            }
                        }
                        return hyp;
                    }
                }
            }
        return hyp;
	}

    virtual int heuristicValue() const override{
        int countNumber = 0;
        for(int i = 0; i< sizeOfBoard; ++i){
            for(int j = 0; j < sizeOfBoard; ++j){
                if(squareArray[i][j].size() > 1){
                    ++countNumber;
                }
            }
        }
        return countNumber;
    }
};



#endif
