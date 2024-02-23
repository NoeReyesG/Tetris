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
    bool isBlockOutside();
    void draw();

private:
    void lockBlock();
    bool isSpaceForBlockEmpty(checkSpace);
    void deleteRowsCompletes();
    void adjustGridAfterDeleteRows(vector<int> rowsDeleted);
    vector<int> getRowsCompletes();
    int getRowPositionToLock();
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};