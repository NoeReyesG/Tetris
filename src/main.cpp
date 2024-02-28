
#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>


double lastUpdateTime = 0;
int score;

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
    InitWindow(500, 620, "Tetris TCS");
    SetTargetFPS(60);
    Font font = LoadFontEx("font/retroGaming.ttf", 64, 0, 0);
    Game game;
    while(WindowShouldClose() == false){
        game.handleInput();
        if (eventTriggered(0.2)){
            game.moveBlockDown();
            score = game.getScore();
        }
        BeginDrawing();
        game.draw();
        ClearBackground(darkBlue);
        score = game.getScore();
        DrawTextEx(font, "Score", {365, 15}, 32, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 32, 2, WHITE);
        if (game.endGame()){
            DrawTextEx(font, "GAME\n\nOVER", {365, 430}, 34, 4, WHITE);
            DrawTextEx(font, "Press R to restart", {330, 500}, 15, 1, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue); //score rectangle

        if (score == 0){
             DrawText(TextFormat("%d", score), 395, 70, 32, WHITE); 
        }
        else{
            DrawText(TextFormat("%d", score), 380, 70, 32, WHITE); 
        }
               
        EndDrawing();       
    }

    CloseWindow();
    return 0;
}