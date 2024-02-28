#pragma once

#include "colors.h"
#include <vector>
using std::vector;

#include <map>
using std::map;

#include "position.h"

class Block {
public:
    Block();
    int id;
    map<int, vector<Position>> cells;
    void draw();
    void move(int, int);
    void rotateBlock();
    void rotateBlockBackwards();
    void drawNextBlock();
    vector<Position> getCellPositions();

private:
    int cellSize;
    int rotationState;
    vector<Color> colors;
    int rowOffset;
    int colOffset;
};