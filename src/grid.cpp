#include "grid.h"
#include "colors.h"
#include <iostream>
using std::cout;
using std::endl;

Grid::Grid()
    :rows(20), cols(10), cellSize(30)
    {
        initialize();
        colors1 = getCellColors();
    }

void Grid::initialize(){
    for (int row = 0; row < rows; row++){
        for (int column = 0; column < cols; column++){
            grid[row][column] = 0;
        }
        
    }
}

void Grid::print(){

    for (int row = 0; row < rows; row++){
        for (int column = 0; column < cols; column++){
            cout << grid[row][column] << " ";
        }
        cout << endl;
    }

}


void Grid::draw(){

     for (int row = 0; row < rows; row++){
        for (int column = 0; column < cols; column++){
            int cellValue = grid[row][column];
            DrawRectangle(column*cellSize+1, row*cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);
        }
     }

}

bool Grid::isCellOutside(int row, int col){
    if (row >=0  && row < rows && col >= 0 && col < cols){
        return false;
    }
    return true;
}
void Grid::drawL(){
    
}

bool Grid::isCellEmpty(int row, int column){
    bool isEmpty = grid[row][column] == 0 ? true: false;
    return isEmpty; 
}