#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "types.cpp"

class Game {
public:
    Game();
    Grid grid;
    Block getRandomBlock();
    vector<Block> getAllBlocks();

    void handleInput();
    void moveBlockLeft();
    void moveBlockRigth();
    void moveBlockDown();
    void rotate();
    bool isBlockOverlaid(Block rotatedBlock);
    bool isBlockOutside();
    void draw();
    bool endGame();
    void calculateScore(int deletedRows);
    int getScore();

private:
    void lockBlock();
    bool isSpaceForBlockEmpty(checkSpace);
    void deleteRowsCompletes();
    void adjustGridAfterDeleteRow(int rowsDeleted);
    
    void restartGame();

    vector<int> getRowsCompletes();
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    int score;
};