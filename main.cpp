#include "raylib.h"

class Linje {
public:
    int start_x, start_y, end_x, end_y;

    Linje() : start_x(0), start_y(0), end_x(0), end_y(0) {}
    Linje(int start_x, int start_y, int end_x, int end_y) {
        this->start_x = start_x;
        this->start_y = start_y;
        this->end_x = end_x;
        this->end_y = end_y;
    }
    void draw_line(){
        DrawLine(start_x,start_y,end_x,end_y,GREEN);
    }
};


int main() 
{
    InitWindow(800, 450, "Mitt spel");
    SetTargetFPS(60);
    int i = 0;
    Linje lista[100];

    for (int i = 0; i < 100; i++)
    {
        Linje l(i,30,i,200);
        lista[i] = l;
    }

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        if (IsKeyDown(KEY_SPACE)){
            for (int i = 0; i < 100; i++){
            lista[i].draw_line();
            }
        }
       
        ClearBackground(RAYWHITE);
        DrawText("Hej Raylib!", 300, 200, 30, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}