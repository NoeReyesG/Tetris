
#include "game.h"
#include <random>
#include <ctime>
#include <iostream>
#include <string>


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
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue); //Rectangle for next block
    currentBlock.draw();
    nextBlock.drawNextBlock();
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
    if (endGame() && keyPressed == KEY_R){
        restartGame();
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
    bool blockOverlaid = isBlockOverlaid(currentBlock);
    
    if (isBlockOutside() || blockOverlaid)
        currentBlock.rotateBlockBackwards();
}

bool Game::isBlockOverlaid(Block rotatedBlock){

    vector<Position> tiles = rotatedBlock.getCellPositions();
    for (Position item: tiles){
        if (grid.grid[item.row][item.column] != 0) return true;
    }
    return false;
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
    //If Game doesn't end, then send a new Block to the game.
    if(!endGame()){
        currentBlock = nextBlock;
        nextBlock = getRandomBlock();
    }
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
        case left:
            for(Position item: tiles){
                if (!grid.isCellEmpty(item.row, item.column-1)){
                    return false;
                }
            }
            return true;
        case right:
            for(Position item: tiles){
                if (!grid.isCellEmpty(item.row, item.column+1)){
                    return false;
                }
            }
            return true;
    }
    return true; //Control never reaches here, but I add this line to avoid a compiler warning      
}

void Game::deleteRowsCompletes(){
    vector<int> rowsCompletes = getRowsCompletes();
    for(int row: rowsCompletes){
        for (int col = 0; col < 10; col++){
            grid.grid[row][col] = 0;
        }
        adjustGridAfterDeleteRow(row);
    }
    calculateScore(rowsCompletes.size());
}

void Game::adjustGridAfterDeleteRow(int rowDeleted){

    int cols = 10;
    for(int row = rowDeleted; row > 0; row--){
        for (int col = 0; col < cols; col++){
            grid.grid[row][col] = grid.grid[row-1][col];
        } 
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


bool Game::endGame(){
    
    for(int i = 3; i < 8; i++){ //row where block emerge.
        //if (currentBlock.id != 3){ 
            if (grid.grid[0][i] != 0){ //|| grid.grid[1][i]){
                return true;
            }
        //}
        // else{
        //     if (grid.grid[0][i] != 0){
        //         return true;
        //     } 
        // }

    }
    return false;
}

void Game::calculateScore(int deletedRows){
    switch(deletedRows){
        case 1:
            score += 100; 
            break;
        case 2:
            score += 220;
            break;
        case 3:
            score += 390;
            break;
        case 4:
            score += 600;
        break;

    }
}


int Game::getScore(){
    return score; 
}

void Game::restartGame(){
    grid.initialize();
    score = 0;
}

