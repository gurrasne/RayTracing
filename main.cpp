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
void render_rays();

//****************************PUBLIKA VARIABLER ***************** */
const int screen_x = 800;
const int screen_y = 800;

int player_radius = 20;

int x = 100;
int y = 100; 

float direction = 0;

int fov = 90;
int amount_of_rays = 800;

std::vector<Objekt> list_of_objects;

std::vector<float> leght_of_rays;

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
        render_rays();
        draw_rays(fov,amount_of_rays);

        

        
       
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
    leght_of_rays.clear();
    for (int i = 0; i < rays; i++){
        float end_x = x;
        float end_y = y;
        while(!reached_object(end_x,end_y) && end_x > 0 && end_x < screen_x && end_y > 0 && end_y < screen_y){
            end_x += 1*sin(direction-(PI*fov/2)/180+ i*((PI*fov/rays)/180));
            end_y += 1*cos(direction-(PI*fov/2)/180+ i*((PI*fov/rays)/180));
        }
        float dist = sqrt((abs(x-end_x))*(abs(x-end_x))+(abs(y-end_y))*(abs(y-end_y)));
        leght_of_rays.push_back(dist);
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

void render_rays(){
    int i = 0;
    int max_dist = (int)sqrt(screen_x*screen_x+screen_y*screen_y);
    //int line_len = screen_y-f;
    
    for (float &f: leght_of_rays){
        int blueval = 255 - f/max_dist*150;
        
        Color c = CLITERAL(Color){0,0,blueval,255};
        
        DrawLine(i,0,i,f/2,BLACK);
        DrawLine(i,f/2,i,screen_y-f/2,c);
        DrawLine(i,screen_y-f/2,i,screen_y,BLACK);
        i++;
    }
}