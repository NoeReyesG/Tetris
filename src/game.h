#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "types.cpp"

class Game {
public:
    Game();
    ~Game();
    Grid grid;
    Block getRandomBlock();
    vector<Block> getAllBlocks();

    void handleInput();
    void draw();
    void moveBlockDown();
    bool endGame();
    void calculateScore(int deletedRows);
    int getScore();

    Music music;

private:
    bool isBlockOverlaid(Block rotatedBlock);
    bool isBlockOutside();
    void moveBlockLeft();
    void moveBlockRigth();
    
    void rotate();
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
    Sound rotateSound;
    Sound rowCompleteSound;
};