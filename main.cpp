#include "raylib.h"
#include <string>
#include "string.h"
#include "math.h"

void display_int_text(const char* input_text,int var,int x, int y);
void check_inputs(int& x, int& y, float& direction);

int main() 
{
    
    InitWindow(800, 450, "Mitt spel");
    SetTargetFPS(60);
    float direction = 0;
    int x = 100;
    int y = 100;
    
    

    while (!WindowShouldClose()) 
    { 
        BeginDrawing();
        check_inputs(x,y, direction);
        display_int_text("direction",direction, 50, 50);
        display_int_text("x",x, 50, 70);
        display_int_text("y",y, 50, 90);
        DrawCircle(x,y,20,RED);
        

        
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
} 

void display_int_text(const char* input_text,int var, int x, int y){
    char text[32];
    sprintf(text,"%s: %d", input_text,var);
    DrawText(text,x,y,20,RED);
}

void check_inputs(int& x, int& y, float& direction){
    if (IsKeyDown(KEY_UP)){
        y += 10*sin(direction);
        x += 10*cos(direction);
    }
    if (IsKeyDown(KEY_DOWN)){
        y -= 10*sin(direction);
        x -= 10*cos(direction);
    }
    if (IsKeyDown(KEY_RIGHT)){
        direction += PI/10;
    }
    if (IsKeyDown(KEY_LEFT)){
        direction -= PI/10;
    }
    

}