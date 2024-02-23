#include <raylib.h>
#include "game.h"


double lastUpdateTime = 0;

bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(300, 600, "Tetris TCS");
    SetTargetFPS(60);

   Game game;
    while(WindowShouldClose() == false){
        game.handleInput();

        if (eventTriggered(0.2)){
            game.moveBlockDown();
        }
        
        BeginDrawing();
        game.draw();
        ClearBackground(darkBlue);       
        
        EndDrawing();
        
    }

    CloseWindow();
    return 0;
}