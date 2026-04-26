#include "raylib.h"
#include <string>
#include "string.h"
#include "math.h"
#include "stdbool.h"
#include <vector>

// ************* OBJEKT **************************

class Objekt{
public:
    int x1, x2, y1, y2;
    Objekt(int x1, int y1, int x2, int y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    bool point_is_within(int x,int y){
        return (x > x1 && x < x2 && y > y1 && y < y2);
    }
    void draw(){
        DrawRectangle(x1,y1,x2-x1,y2-y1,BLUE);
    }

};

//****************** FUNKTIONS DEKLARATIONER ******************

void display_int_text(const char* input_text,int var,int x, int y);
void check_inputs();
void draw_rays(int fov, int rays);
void draw_objects();
bool reached_object(float current_x, float current_y);

//****************************PUBLIKA VARIABLER ***************** */
const int screen_x = 800;
const int screen_y = 800;

int player_radius = 20;

int x = 100;
int y = 100; 

float direction = 0;

std::vector<Objekt> list_of_objects;

/****************MAIN*************************** */
int main() 
{
    
    InitWindow(screen_x, screen_y, "Mitt spel");
    SetTargetFPS(60);

    // Skapa objekt
    int border_width = 20;

    list_of_objects.push_back(Objekt(0,0,screen_x,border_width));
    list_of_objects.push_back(Objekt(screen_x-border_width,0,screen_x,screen_y));
    list_of_objects.push_back(Objekt(0,screen_y-border_width,screen_x,screen_y));
    list_of_objects.push_back(Objekt(0,0,border_width,screen_y));
    
    list_of_objects.push_back(Objekt(200,200,300,300));
    

    while (!WindowShouldClose()) 
    { 
        BeginDrawing();
        ClearBackground(RAYWHITE);
        check_inputs();
        display_int_text("direction",direction, 50, 50);
        display_int_text("x",x, 50, 70);
        display_int_text("y",y, 50, 90);
        draw_objects();
        DrawCircle(x,y,player_radius,RED);
        draw_rays(90,90);

        

        
       
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

void check_inputs(){
    if (IsKeyDown(KEY_UP)){
        y += 5*cos(direction);
        x += 5*sin(direction);
    }
    if (IsKeyDown(KEY_DOWN)){
        y -= 5*cos(direction);
        x -= 5*sin(direction);
    }
    if (IsKeyDown(KEY_RIGHT)){
        direction -= PI/50;
    }
    if (IsKeyDown(KEY_LEFT)){
        direction += PI/50;
    }
    if (x > screen_x){
        x = screen_x;
    }
    if (y > screen_y){
        y = screen_y;
    }
    if (x < 0){
        x = 0;
    }
    if (y < 0){
        y = 0;
    }
}
void draw_rays(int fov, int rays){
    for (int i = 0; i < rays; i++){
        float end_x = x;
        float end_y = y;
        while(!reached_object(end_x,end_y) && end_x > 0 && end_x < screen_x && end_y > 0 && end_y < screen_y){
            end_x += 1*sin(direction-(PI*fov/2)/180+ i*((PI*fov/rays)/180));
            end_y += 1*cos(direction-(PI*fov/2)/180+ i*((PI*fov/rays)/180));
        }
        DrawLine(x,y,end_x,end_y,GREEN);
    }
}

bool reached_object(float current_x, float current_y){
    for (Objekt &o: list_of_objects){
        if (o.point_is_within(current_x,current_y)){
            return true;
        }
    }
    return false;
}

void draw_objects(){
    for (Objekt &o : list_of_objects){
        o.draw();
    }
}