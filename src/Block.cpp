#include "Block.h"
#include "grid.h"
Block::Block()
    : cellSize(30), rotationState(0), rowOffset(0), colOffset(0)
    
{
    colors = getCellColors();
     
}

void Block::draw(){
    vector<Position> tiles = getCellPositions();

    for(Position item: tiles){
        DrawRectangle(item.column*cellSize + 11, item.row*cellSize + 11, cellSize-1, cellSize-1, colors[id] );
    }
}

void Block::move(int rows, int cols){
    rowOffset = rowOffset + rows;
    colOffset = colOffset + cols;
}

vector<Position> Block::getCellPositions(){
     vector<Position> tiles = cells[rotationState];
     vector<Position> movedTiles;

    for(Position item: tiles){
        //DrawRectangle((item.column+colOffset)*cellSize + 1, (item.row+rowOffset)*cellSize + 1, cellSize-1, cellSize-1, colors[id] );
        Position newPos = Position(item.row+rowOffset, item.column+colOffset);
        movedTiles.push_back(newPos);
    }

    return movedTiles;    
}

void Block::rotateBlock(){
    //rotationState = (rotationState < 3) ? rotationState+1: 0;    
    if (rotationState < 3 && id != 4){
        rotationState++;
    }
    else{
        rotationState = 0;
    }
}

void Block::rotateBlockBackwards(){
    if (rotationState == 0 && id != 4){
        rotationState = 3;
    }
    else if (id != 4){
        rotationState --;
    }
}

void Block::drawNextBlock(){
    vector<Position> tiles = getCellPositions();

    if (id == 3 || id == 4){
        for(Position item: tiles){
            DrawRectangle(item.column*cellSize+260, item.row*cellSize +275, cellSize-1, cellSize-1, colors[id] );
        }
    }
    else{
        for(Position item: tiles){
            DrawRectangle(item.column*cellSize+270, item.row*cellSize +265, cellSize-1, cellSize-1, colors[id] );
        }
    }

}


