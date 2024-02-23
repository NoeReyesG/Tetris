#include "game.h"
#include <random>
#include <ctime>
#include <iostream>


Game::Game()
{
    Grid grid;
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    
}

Block Game::getRandomBlock(){
    if (blocks.empty()){
        blocks = getAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin()+randomIndex);
    return block;
};

vector<Block> Game::getAllBlocks(){
    return {IBlock(), JBlock(), SBlock(), ZBlock(), TBlock(), LBlock(), OBlock()};
};

void Game::draw(){
    grid.draw();
    currentBlock.draw();
}

void Game::handleInput(){
    int keyPressed = GetKeyPressed();

    switch(keyPressed){
        case KEY_LEFT:
            moveBlockLeft();
            break;
        case KEY_RIGHT:
            moveBlockRigth();
            break;
        case KEY_DOWN:
            moveBlockDown();  
            break;
        case KEY_UP:
            rotate();
            break;
    }

}

void Game::moveBlockLeft(){
    if (isSpaceForBlockEmpty(left)){
        currentBlock.move(0, -1);
    }  
    if (isBlockOutside()){
        currentBlock.move(0, 1);
    }    
}
void Game::moveBlockRigth(){
    
    if (isSpaceForBlockEmpty(right)){
        currentBlock.move(0, 1);
    }

    if (isBlockOutside()){
        currentBlock.move(0,-1);
    }
}
void Game::moveBlockDown(){

    if (isSpaceForBlockEmpty(down)){
        currentBlock.move(1, 0);
    }
    else{
        lockBlock();

        if (getRowsCompletes().size() > 0){
            deleteRowsCompletes();    
        }
    }
    
    if (isBlockOutside()){
        currentBlock.move(-1,0);
        lockBlock();
    }
}

void Game::rotate(){
    currentBlock.rotateBlock();
    if (isBlockOutside())
        currentBlock.rotateBlockBackwards();
}

bool Game::isBlockOutside(){
    vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item: tiles){
        if (grid.isCellOutside(item.row, item.column)){
            return true;
        }
    }
    return false;
}

void Game::lockBlock(){

    vector<Position> tiles = currentBlock.getCellPositions();

    for(Position item: tiles){
        
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = getRandomBlock();
}

bool Game::isSpaceForBlockEmpty(checkSpace direction){

    vector<Position> tiles = currentBlock.getCellPositions();
    switch(direction){
        case down:
            for(Position item: tiles){
                if (!grid.isCellEmpty(item.row+1, item.column)){
                    return false;
                }
            }
            return true;
            break;
        case left:
            for(Position item: tiles){
                if (!grid.isCellEmpty(item.row, item.column-1)){
                    return false;
                }
            }
            return true;
            break;
        case right:
            for(Position item: tiles){
                if (!grid.isCellEmpty(item.row, item.column+1)){
                    return false;
                }
            }
            return true;
            break;
    }      
}

void Game::deleteRowsCompletes(){
    vector<int> rowsCompletes = getRowsCompletes();
    for(int item: rowsCompletes){
        for (int col = 0; col < 10; col++){
            grid.grid[item][col] = 0;
        }
    }
    adjustGridAfterDeleteRows(rowsCompletes);
}

void Game::adjustGridAfterDeleteRows(vector<int> rowsDeleted){

    // for(int item: rowsDeleted){
        
    // }
    int first = *(rowsDeleted.begin()); //get the first row that must be eliminated
    std::cout << std::endl;
    // int rows = 10;
    int cols = 20;
    for(int row = first; row > 0; row--){
        for (int col = 0; col < cols; col++){
            
        }
        std::cout <<"Fila: " <<  row << "\n";  
    }
}

vector<int> Game::getRowsCompletes(){
    int rows = 20;
    int cols = 10;
    bool isRowComplete = true;
    vector<int> rowsCompletes = {};
    for(int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            if (grid.grid[row][col] == 0){
                isRowComplete = false;
                break;
            }
        }
        if (isRowComplete){   
            rowsCompletes.push_back(row);
        }
        isRowComplete = true;
    }
    return rowsCompletes;
   
}



