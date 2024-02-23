#pragma once // is it the same that the wrapper #ifndef #def .... #endif?

#include <vector>
using std::vector;
#include <raylib.h>

class Grid {
public:
    Grid();

    void initialize();
    void print();
    void draw();
    bool isCellOutside(int, int);
    void drawL();
    bool isCellEmpty(int row, int column);
    int grid[20][10];

private:
    
    int rows;
    int cols;
    int cellSize;
    vector<Color> colors1;
};